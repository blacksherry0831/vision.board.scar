/*
 * flame_monitor.c
 *
 *  Created on: 2020年3月17日
 *      Author: yjkj909
 */

#include "flame_monitor.h"

extern  MsgQueueFlame gFlameCmdQueue;

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
	//fire_on = FALSE;
	//fire_off = TRUE;
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

	while(IsRun())
	{
		if (connect(*_sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		{
			perror("connect error\n");
			sleep_1ms_yield();
		}
		else
		{
			printf("##############igniter_client connect successfully!  sock_cli:%d\n",*_sock_cli);
			break;
		}

		gFlameCmdQueue.release_queue_flame();

	}

	//int flag = fcntl(*_sock_cli, F_GETFL, 0);
	//fcntl(*_sock_cli, F_SETFL, flag | O_NONBLOCK);//修改当前的flag标志为非阻塞

	return 0;
}

//socket关闭重连
int reconnect_socket_client(int* _sock_cli)
{
	printf("#########igniter_client reconnect ..........\n");
	close(*_sock_cli);
	*_sock_cli = -1;
	init_socket_client(_sock_cli);

	usleep(5000);
	gFlameCmdQueue.clear_queue_flame();  //清空队列
	gFlameCmdQueue.snd_queue_flame(1,0);  //向队列中塞入点火命令，刷新点火器状态

	printf("#########igniter_client reconnect sucessfully!!!!!!!!\n");

	return 0;
}

//检查socket_clinet是否处于连接状态 若不处于则重连 （无用）
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

//发心跳包命令
int SendFlameHearbeat(const int sock_cli,time_t* last_send_time,int* cnt = NULL)
{

	unsigned char heart_beat[7] = {0};
	heart_beat[0] = 0x55;
	heart_beat[1] = 0xAA;
	heart_beat[2] = 0x00;
	heart_beat[3] = 0x00;
	heart_beat[4] = 0x00;
	heart_beat[5] = 0x02;
	heart_beat[6] = 0x01;

	int ret = 0;

	if( time(NULL) - *last_send_time > 1)  //每1秒发一次心跳包
	{
		ret = send(sock_cli, heart_beat, sizeof(heart_beat),0); //发送“心跳包”信号

		if(ret < 0)
		{
			printf("#########igniter_client socket send error!\n");
			close(sock_cli);
			//init_socket_client(&sock_cli);

			return -1;
		}

		*last_send_time = time(NULL);
		printf("#########igniter_client socket heart_beat\n");

		if(cnt != NULL)
		{
			(*cnt)++;
		}

	}


	return ret;
}

//发送点火/熄火命令
int SendFlameCmd(const int sock_cli,const int _on,const int _off)
{
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

	int ret = 0;

	//点火
	if(_on)
	{
		ret = send(sock_cli, cmd_fire, sizeof(cmd_fire),0); //发送“点火”信号

		if(ret < 0)
		{
			printf("#########igniter_client socket send error!\n");
			close(sock_cli);
			//init_socket_client(&sock_cli);

			return -1;
		}

		//last_send_time = time(NULL);
		igniter_status = TRUE;
		fire_on = FALSE;  //不建议连续发
		printf("#########igniter_client socket fire_on\n");
	}

	//熄火
	if(_off)
	{
		if(igniter_status)  //点火器处于点火状态
		{
			ret = send(sock_cli, cmd_stop, sizeof(cmd_stop),0); //发送“熄火”信号

			if(ret < 0)
			{
				printf("#########igniter_client socket send error!\n");
				close(sock_cli);
				//init_socket_client(&sock_cli);

				return -1;
			}
		}

		//last_send_time = time(NULL);
		igniter_status = FALSE;
		fire_off = FALSE;  //不建议连续发
		printf("#########igniter_client socket fire_off\n");
	}

	return ret;
}

//从队列中取出命令，并socket发送点火/熄火命令
int SendFlameQueue(const int sock_cli,int* cnt = NULL)
{
	int on,off;

	const int  result_t=gFlameCmdQueue.rcv_queue_flame(&on,&off);  //从队列中取出命令

	if(result_t==1){
		SendFlameCmd(sock_cli,on,off);  //socket发送点火/熄火命令

		if(cnt != NULL)
		{
			(*cnt)++;
		}

	}else {

	}

	return 0;
}

//创建与点火器-stm32交互的socket客户端线程-起始函数 -- select
void *iginter_client(void* _pdata)
{
	int sock_cli;
	fd_set rfds;
	struct timeval tv;
	int retval, maxfd;
	time_t last_send_time = time(NULL);  //上一次发心跳包命令的时间
	time_t last_recv_time = time(NULL);  //上一次接收服务器消息的时间

	init_socket_client(&sock_cli);

	tv.tv_sec = 0;
	tv.tv_usec = 1000;

	while(IsRun())
	{
		if(!flame_monitor_flag){  //火焰监测标志是否开启
			sleep_1_ms();
			continue;
		}

		//check_socket_client(&sock_cli); //检查socket_clinet是否处于连接状态 若不处于则重连 （无用）

		//长时间未接收到服务器消息（表明socket断开）
		if(time(NULL) - last_recv_time > 2)
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

		retval = select(maxfd+1, &rfds, NULL, NULL, &tv);  //看描述符号中是否有可用的

		if(retval < 0)
		{
			PRINTF_DBG_EX("#########igniter_client select出错，客户端程序退出\n");
			close(sock_cli);
			init_socket_client(&sock_cli);
			continue;
		}
		else if(retval == 0)
		{
			//服务器没有信息到来，waiting...
			SendFlameQueue(sock_cli);
			SendFlameHearbeat(sock_cli,&last_send_time);

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

		//sched_yield();
	}

	close(sock_cli);
	return 0;
}

//创建与点火器-stm32交互的socket客户端线程-起始函数 -- poll
void *iginter_client_poll(void* _pdata)
{
	int sock_cli;
	time_t last_send_time = time(NULL);
	time_t last_recv_time = time(NULL);

	init_socket_client(&sock_cli);

	 struct pollfd fds[2];
	 const int pollfd_sz=1;
	 const int timeout_msecs = 1;
	 int ret;

	while(IsRun())
	{
		if(!flame_monitor_flag){  //火焰监测标志是否开启
			sleep_1_ms();
			continue;
		}

		//长时间未接收到服务器消息（表明socket断开）
		if(time(NULL) - last_recv_time > 2)
		{
			printf("#########igniter_client timeout!!!!!!!!! wait for reconnect!!\n");
			printf("#########igniter_client recv_time %d\n",time(NULL) - last_recv_time);
			reconnect_socket_client(&sock_cli);
			last_recv_time = time(NULL);
			last_send_time = time(NULL);
		}

		 fds[0].fd = sock_cli;
		 fds[0].events = POLLIN;
		 fds[0].revents=0;

		 ret = poll(fds, pollfd_sz, timeout_msecs);

		if(ret < 0)  //poll出错
		{
			printf("#########igniter_client select出错，socket重连...\n");
			reconnect_socket_client(&sock_cli);
			continue;
		}
		else if(ret == 0)
		{
			//服务器没有信息到来，waiting...
			SendFlameQueue(sock_cli);
			SendFlameHearbeat(sock_cli,&last_send_time);

		}
		else if(ret>0)
		{
			/* An event on one of the fds has occurred. */
			for (int i=0; i<pollfd_sz; i++) {

				//服务器有消息传来
				if(fds[i].revents & POLLIN)
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
						 printf("#########igniter_client recv error!\n");
						 close(sock_cli);
						 //init_socket_client(&sock_cli);
						 continue;
					 }

					 printf("#########igniter_client recv sucess!\n");
					 last_recv_time = time(NULL);
				 }
			 }

		}else{

			assert(0);

		}
	}

	close(sock_cli);
	return 0;
}

//初始化BSD套接字
int init_bsd_socket(int* _socket_fd)
{
	struct sockaddr_in stSockAddr;
	int Res;

	PRINTF_DBG_EX("#########igniter_client_bsd connecting ............\n");

	*_socket_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);  //创建套接字
	if (-1 == *_socket_fd)
	{
	  perror("cannot create socket");
	  return -1;
	}

	memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
	stSockAddr.sin_family = AF_INET;  //协议族
	stSockAddr.sin_port = htons(8899);  //端口号
	Res = inet_pton(AF_INET, "192.168.100.188", &stSockAddr.sin_addr);   //将十进制的ip地址转化为用于网络传输的数值格式
	if (0 > Res)
	{
	  perror("error: first parameter is not a valid address family");
	  close(*_socket_fd);
	  return -1;
	}
	else if (0 == Res)
	{
	  perror("char string (second parameter does not contain valid ipaddress");
	  close(*_socket_fd);
	  return -1;
	}

	if (-1 == connect(*_socket_fd, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))  //套接字连接
	{
	  perror("connect failed");
	  close(*_socket_fd);
	  return -1;
	}

	// 设置接收的超时时间为 5秒
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 500000;
	setsockopt(*_socket_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
	setsockopt(*_socket_fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

	PRINTF_DBG_EX("#########igniter_client_bsd connect sucessfully!!\n");

	return *_socket_fd;
}

//BSD套接字断开重连
int reconnect_bsd_socket(int* _socket_fd,int* cnt)
{
	close(*_socket_fd);
	*_socket_fd = -1;
	*cnt = 0;
	return init_bsd_socket(_socket_fd);
}

//创建与点火器-stm32交互的socket客户端线程-起始函数 -- 伯克利套接字
void *iginter_client_bsd(void* _pdata)
{
	int SocketFD;
	time_t last_send_time = time(NULL);
	time_t last_recv_time = time(NULL);
	int send_recv_cnt = 0;

	//初始化BSD套接字
	init_bsd_socket(&SocketFD);

	/* perform read write operations ... */

	while(IsRun())
	{
		if(!flame_monitor_flag){  //火焰监测标志是否开启
			sleep_1_ms();
			continue;
		}

		//长时间未接收到服务器消息（表明socket断开）
		if(time(NULL) - last_recv_time > 2)
		{
			PRINTF_DBG_EX("#########igniter_client timeout!!!!!!!!! wait for reconnect!!\n");
			PRINTF_DBG_EX("#########igniter_client recv_time %d\n",time(NULL) - last_recv_time);
			reconnect_bsd_socket(&SocketFD,&send_recv_cnt);
			last_recv_time = time(NULL);
		}

		//检查是否需要发新命令或心跳包
		SendFlameQueue(SocketFD,&send_recv_cnt);
		SendFlameHearbeat(SocketFD,&last_send_time,&send_recv_cnt);

		if(send_recv_cnt > 0)
		{
			unsigned char recvbuf[BUFFER_SIZE];
			if(readn(SocketFD,recvbuf, 7) != 7)  //socket断开时易堵塞！！！bug
			{
				PRINTF_DBG_EX("#########igniter_client recv error!\n");
				//reconnect_bsd_socket(&SocketFD,&send_recv_cnt);
			}
			else
			{
				memset(recvbuf, 0, sizeof(recvbuf));
				PRINTF_DBG_EX("#########igniter_client recv sucess!\n");
				last_recv_time = time(NULL);
				send_recv_cnt--;
			}
		}
		else
		{
			sleep_1_ms();
		}
	}

	shutdown(SocketFD, SHUT_RDWR);

	close(SocketFD);

}


//创建与点火器-stm32交互的socket客户端线程
pthread_t connect_to_igniter()
{
	pthread_t _thread_tid;

	if( pthread_create(&_thread_tid, NULL,iginter_client_poll, NULL) ){
			PRINTF_DBG_EX(" Create iginter_client thread error!\n");
			exit(0);
	}

 return _thread_tid;
}
