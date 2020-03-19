/*
 * flame_monitor.c
 *
 *  Created on: 2020��3��17��
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

static int flame_monitor_flag = FALSE;  //�Ƿ���Ҫ������
static double threshold_area = 0.5;  //���������ֵ
static double threshold_difference = 0.5;  //��������ֵ
static int i = 0;  //���л�����ļ���
static double last_flame = 0;  //��һ�λ������
static double current_flame = 0;  //���λ������
static int igniter_status = FALSE;  //������Ƿ��ڵ��״̬
static int fire_on = FALSE;  //�Ƿ���Ҫ������
static int fire_off = FALSE;  //�Ƿ���Ҫ������

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

//��ʼ��socket_clinet
int init_socket_client(int* _sock_cli)
{
	//����sockfd-�½��׽���
	*_sock_cli = socket(AF_INET,SOCK_STREAM, 0);
	//����sockaddr
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(MYPORT);  //�������˿�
	servaddr.sin_addr.s_addr = inet_addr("192.168.100.188");  //������ip

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
	//fcntl(*_sock_cli, F_SETFL, flag | O_NONBLOCK);//�޸ĵ�ǰ��flag��־Ϊ������

	return 0;
}

//���socket_clinet�Ƿ�������״̬ ��������������
void check_socket_client(int* _sock_cli)
{
	if(*_sock_cli < 0)  //�׽�����Ч
	{
		init_socket_client(_sock_cli);
	}

	do {
		struct tcp_info info;
		int len=sizeof(info);
		getsockopt(*_sock_cli, IPPROTO_TCP, TCP_INFO, &info, (socklen_t *)&len);
		if((info.tcpi_state==TCP_ESTABLISHED))  //socket������
		{
			printf("igniter_client check successfully!\n");
			break;
		}
		else //δ����
		{
			init_socket_client(_sock_cli);
		}
	} while(IsRun());
}

//����������-stm32������socket�ͻ����߳�-��ʼ����

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
		check_socket_client(&sock_cli); //���socket_clinet�Ƿ�������״̬ ��������������

		FD_ZERO(&rfds);  //�ѿɶ��ļ��������ļ������
		FD_SET(0, &rfds);  //�ѱ�׼������ļ����������뵽������
		maxfd = 0;
		FD_SET(sock_cli, &rfds);  //�ѵ�ǰ���ӵ�socket���������뵽������
		if(maxfd < sock_cli)  //�ҳ��ļ������������������ļ�������
			maxfd = sock_cli;
		tv.tv_sec = 5;  //���ó�ʱʱ��Ϊ5��
		tv.tv_usec = 0;
		retval = select(maxfd+1, &rfds, NULL, NULL, &tv);  //�������������Ƿ��п��õ�

		if(retval == -1)
		{
			printf("igniter_client select�������ͻ��˳����˳�\n");
			init_socket_client(&sock_cli);
			continue;
		}
		else if(retval == 0)
		{
			//�ͻ���û���κ�������Ϣ�����ҷ�����Ҳû����Ϣ������waiting...

			if(fire_on)
			{
				send(sock_cli, cmd_fire, sizeof(cmd_fire),0); //���͡�����ź�
				igniter_status = TRUE;
				fire_on = FALSE;  //������������
				printf("fire_on\n");
			}

			if(fire_off)
			{
				if(igniter_status == TRUE)  //��������ڵ��״̬
					send(sock_cli, cmd_stop, sizeof(cmd_stop),0); //���͡�����ź�

				igniter_status = FALSE;
				fire_off = FALSE;  //������������
				printf("fire_off\n");
			}

		}
		else
		{
			//��������������Ϣ
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

//����������-stm32������socket�ͻ����߳�
pthread_t connect_to_igniter()
{
	pthread_t _thread_tid;

	if( pthread_create(&_thread_tid, NULL,iginter_client, NULL) ){
			PRINTF_DBG_EX(" Create iginter_client thread error!\n");
			exit(0);
	}

 return _thread_tid;
}