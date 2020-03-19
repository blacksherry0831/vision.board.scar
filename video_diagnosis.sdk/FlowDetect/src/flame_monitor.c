/*
 * flame_monitor.c
 *
 *  Created on: 2020年3月17日
 *      Author: yjkj909
 */

#include "flame_monitor.h"

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define MYPORT  8899
#define BUFFER_SIZE 1024

static int flame_monitor_flag = FALSE;  //是否需要火焰检测
static double threshold_area = 0.5;  //火焰面积阈值
static double threshold_difference = 0.5;  //火焰差分阈值
static int i = 0;  //自有火焰起的计数
static double last_flame = 0;  //上一次火焰面积
static double current_flame = 0;  //本次火焰面积
static int igniter_status = FALSE;  //点火器是否处于点火状态
static int fire_on = FALSE;  //是否需要点火操作
static int fire_off = FALSE;  //是否需要灭火操作

void init_fire()
{
	i = 0;
	last_flame = 0;
	current_flame = 0;
	igniter_status = FALSE;
	fire_on = FALSE;
	fire_off = FALSE;
}

void set_flame_monitor_flag(int _v)
{
	flame_monitor_flag = _v;
}

int get_flame_monitor_flag()
{
	return flame_monitor_flag;
}

void set_thresholde_area(double _v)
{
	threshold_area = _v;
}

double get_thresholde_area()
{
	return threshold_area;
}

void set_thresholde_difference(double _v)
{
	threshold_difference = _v;
}

double get_thresholde_difference()
{
	return threshold_difference;
}

void set_last_flame(double _v)
{
	last_flame = _v;
}

double get_last_flame()
{
	return last_flame;
}

void set_current_flame(double _v)
{
	current_flame = _v;
}

double get_current_flame()
{
	return current_flame;
}

void set_igniter_status(int _v)
{
	igniter_status = _v;
}

int get_igniter_status()
{
	return igniter_status;
}

void set_fire_on(int _v)
{
	fire_on = _v;
}

int get_fire_on()
{
	return fire_on;
}

void set_fire_off(int _v)
{
	fire_off = _v;
}

int get_fire_off()
{
	return fire_off;
}

//初始化socket_clinet
int init_socket_client(int* _sock_cli)
{
	//定义sockfd-新建套接字
	*_sock_cli = socket(AF_INET,SOCK_STREAM, 0);
	//定义sockaddr
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(MYPORT);  //服务器端口
	servaddr.sin_addr.s_addr = inet_addr("192.168.100.188");  //服务器ip

	if (connect(*_sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("connect error\n");

		return -1;
	}
	else
	{
		printf("igniter_client connect successfully!\n");
	}

	//flag = fcntl(*_sock_cli, F_GETFL, 0);
	//fcntl(*_sock_cli, F_SETFL, flag | O_NONBLOCK);//修改当前的flag标志为非阻塞

	return 0;
}

//检查socket_clinet是否处于连接状态 若不处于则重连
void check_socket_client(int* _sock_cli)
{
	if(*_sock_cli < 0)  //套接字无效
	{
		init_socket_client(_sock_cli);
	}

	do {
		struct tcp_info info;
		int len=sizeof(info);
		getsockopt(*_sock_cli, IPPROTO_TCP, TCP_INFO, &info, (socklen_t *)&len);
		if((info.tcpi_state==TCP_ESTABLISHED))  //socket已连接
		{
			printf("igniter_client check successfully!\n");
			break;
		}
		else //未连接
		{
			init_socket_client(_sock_cli);
		}
	} while(IsRun());
}

//创建与点火器-stm32交互的socket客户端线程-起始函数

void *iginter_client(void* _pdata)
{
	int sock_cli;
	fd_set rfds;
	struct timeval tv;
	int retval, maxfd;

	unsigned char cmd_fire[7] = {0};
	cmd_fire[0] = 0x55;
	cmd_fire[1] = 0xAA;
	cmd_fire[2] = 0x00;
	cmd_fire[3] = 0x00;
	cmd_fire[4] = 0x00;
	cmd_fire[5] = 0x01;
	cmd_fire[6] = 0x00;

	unsigned char cmd_stop[7] = {0};
	cmd_stop[0] = 0x55;
	cmd_stop[1] = 0xAA;
	cmd_stop[2] = 0x00;
	cmd_stop[3] = 0x00;
	cmd_stop[4] = 0x00;
	cmd_stop[5] = 0x00;
	cmd_stop[6] = 0xFF;

	init_socket_client(&sock_cli);

	while(IsRun())
	{
		check_socket_client(&sock_cli); //检查socket_clinet是否处于连接状态 若不处于则重连

		FD_ZERO(&rfds);  //把可读文件描述符的集合清空
		FD_SET(0, &rfds);  //把标准输入的文件描述符加入到集合中
		maxfd = 0;
		FD_SET(sock_cli, &rfds);  //把当前连接的socket描述符加入到集合中
		if(maxfd < sock_cli)  //找出文件描述符集合中最大的文件描述符
			maxfd = sock_cli;
		tv.tv_sec = 5;  //设置超时时间为5秒
		tv.tv_usec = 0;
		retval = select(maxfd+1, &rfds, NULL, NULL, &tv);  //看描述符号中是否有可用的

		if(retval == -1)
		{
			printf("igniter_client select出错，客户端程序退出\n");
			init_socket_client(&sock_cli);
			continue;
		}
		else if(retval == 0)
		{
			//客户端没有任何输入信息，并且服务器也没有信息到来，waiting...

			if(fire_on)
			{
				send(sock_cli, cmd_fire, sizeof(cmd_fire),0); //发送“点火”信号
				igniter_status = TRUE;
				fire_on = FALSE;  //不建议连续发
				printf("fire_on\n");
			}

			if(fire_off)
			{
				if(igniter_status == TRUE)  //点火器处于点火状态
					send(sock_cli, cmd_stop, sizeof(cmd_stop),0); //发送“点火”信号

				igniter_status = FALSE;
				fire_off = FALSE;  //不建议连续发
				printf("fire_off\n");
			}

		}
		else
		{
			//服务器发来了消息
			 if(FD_ISSET(sock_cli,&rfds))
			 {
				 unsigned char recvbuf[BUFFER_SIZE];
				 recv(sock_cli, recvbuf, sizeof(recvbuf),0);
				 /**
				 for(int i = 0;i < 7;i++)
				 {
					 printf("%X,",recvbuf[i]);
				 }
				 printf("\n");
				 **/
				 memset(recvbuf, 0, sizeof(recvbuf));
			 }
		}
	}

	close(sock_cli);
	return 0;
}

//创建与点火器-stm32交互的socket客户端线程
pthread_t connect_to_igniter()
{
	pthread_t _thread_tid;

	if( pthread_create(&_thread_tid, NULL,iginter_client, NULL) ){
			PRINTF_DBG_EX(" Create iginter_client thread error!\n");
			exit(0);
	}

 return _thread_tid;
}
