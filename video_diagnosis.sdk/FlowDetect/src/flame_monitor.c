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
static double threshold_area = 500;  //火焰面积阈值
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
	fire_off = TRUE;
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

int get_cnt_i()
{
	return i;
}

void inc_cnt_i()
{
	i++;
}

//判断是否满足差分阈值
int is_up_to_thresholde_difference()
{
	if((abs(current_flame - last_flame) * 1.0) / ((current_flame + last_flame)*1.0) <= threshold_difference)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
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

	while(1)
	{
		if (connect(*_sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		{
			perror("connect error\n");
		}
		else
		{
			PRINTF_DBG_EX("##############igniter_client connect successfully!  sock_cli:%d\n",*_sock_cli);
			break;
		}
	}

	int flag = fcntl(*_sock_cli, F_GETFL, 0);
	fcntl(*_sock_cli, F_SETFL, flag | O_NONBLOCK);//修改当前的flag标志为非阻塞

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
			//PRINTF_DBG_EX("igniter_client check successfully! sock_cli:%d\n",*_sock_cli);
			break;
		}
		else //未连接
		{
			close(*_sock_cli);

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
	time_t last_send_time = time(NULL);
	time_t last_recv_time = time(NULL);

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

	unsigned char heart_beat[7] = {0};
	heart_beat[0] = 0x55;
	heart_beat[1] = 0xAA;
	heart_beat[2] = 0x00;
	heart_beat[3] = 0x00;
	heart_beat[4] = 0x00;
	heart_beat[5] = 0x02;
	heart_beat[6] = 0x01;

	init_socket_client(&sock_cli);

	while(IsRun())
	{
		if(!flame_monitor_flag) continue;

		//check_socket_client(&sock_cli); //检查socket_clinet是否处于连接状态 若不处于则重连
		if(time(NULL) - last_recv_time > 10)
		{
			PRINTF_DBG_EX("#########igniter_client timeout!!!!!!!!! wait for reconnect!!\n");
			PRINTF_DBG_EX("#########igniter_client recv_time %d\n",time(NULL) - last_recv_time);
			close(sock_cli);
			sock_cli = -1;
			init_socket_client(&sock_cli);
			last_recv_time = time(NULL);
		}

		FD_ZERO(&rfds);  //把可读文件描述符的集合清空
		maxfd = 0;
		FD_SET(sock_cli, &rfds);  //把当前连接的socket描述符加入到集合中
		if(maxfd < sock_cli)  //找出文件描述符集合中最大的文件描述符
			maxfd = sock_cli;
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		retval = select(maxfd+1, &rfds, NULL, NULL, &tv);  //看描述符号中是否有可用的

		if(retval < 0)
		{
			PRINTF_DBG_EX("#########igniter_client select出错，客户端程序退出\n");
			close(sock_cli);
			//init_socket_client(&sock_cli);
			continue;
		}
		else if(retval == 0)
		{
			//客户端没有任何输入信息，并且服务器也没有信息到来，waiting...

			if(fire_on)
			{
				int ret = send(sock_cli, cmd_fire, sizeof(cmd_fire),0); //发送“点火”信号

				if(ret < 0)
				{
					PRINTF_DBG_EX("#########igniter_client socket send error!\n");
					close(sock_cli);
					//init_socket_client(&sock_cli);
					continue;
				}

				//last_send_time = time(NULL);
				igniter_status = TRUE;
				fire_on = FALSE;  //不建议连续发
				PRINTF_DBG_EX("#########igniter_client socket fire_on\n");
			}

			if(fire_off)
			{
				if(igniter_status)  //点火器处于点火状态
				{
					int ret = send(sock_cli, cmd_stop, sizeof(cmd_stop),0); //发送“熄火”信号

					if(ret < 0)
					{
						PRINTF_DBG_EX("#########igniter_client socket send error!\n");
						close(sock_cli);
						//init_socket_client(&sock_cli);
						continue;
					}
				}

				//last_send_time = time(NULL);
				igniter_status = FALSE;
				fire_off = FALSE;  //不建议连续发
				PRINTF_DBG_EX("#########igniter_client socket fire_off\n");
			}

			if( time(NULL) - last_send_time > 3)  //每3秒发一次心跳包
			{
				int ret = send(sock_cli, heart_beat, sizeof(heart_beat),0); //发送“心跳包”信号

				if(ret < 0)
				{
					PRINTF_DBG_EX("#########igniter_client socket send error!\n");
					close(sock_cli);
					//init_socket_client(&sock_cli);
				}

				last_send_time = time(NULL);
				PRINTF_DBG_EX("#########igniter_client socket heart_beat\n");
			}

		}
		else
		{
			//服务器发来了消息
			 if(FD_ISSET(sock_cli,&rfds))
			 {
				 unsigned char recvbuf[BUFFER_SIZE];
				 int ret=recv(sock_cli, recvbuf, sizeof(recvbuf),0);
				 /**
				 for(int i = 0;i < 7;i++)
				 {
					 PRINTF_DBG_EX("%X,",recvbuf[i]);
				 }
				 PRINTF_DBG_EX("\n");
				 **/
				 memset(recvbuf, 0, sizeof(recvbuf));

				 if(ret <= 0)
				 {
					 PRINTF_DBG_EX("#########igniter_client recv error!\n");
					 close(sock_cli);
					 //init_socket_client(&sock_cli);
					 continue;
				 }

				 PRINTF_DBG_EX("#########igniter_client recv sucess!\n");
				 last_recv_time = time(NULL);
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
