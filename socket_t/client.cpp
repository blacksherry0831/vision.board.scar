#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include "time.h"
 
#define MYPORT  8899
#define BUFFER_SIZE 1024

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif


int igniter_status = FALSE;
int fire_on = FALSE;
int fire_off = TRUE;
int send_flag = 0;

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
      send_flag = 0;
      printf("##############igniter_client connect successfully!\n");
   }
 
   int flag = fcntl(*_sock_cli, F_GETFL, 0);
   fcntl(*_sock_cli, F_SETFL, flag | O_NONBLOCK);//修改当前的flag标志为非阻塞

   return 0;

}

int main()
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
    for (int i=0; i<6;i++)
    {
      cmd_fire[6] += cmd_fire[i];
    }

    unsigned char cmd_stop[7] = {0};
    cmd_stop[0] = 0x55;
    cmd_stop[1] = 0xAA;
    cmd_stop[2] = 0x00;
    cmd_stop[3] = 0x00;
    cmd_stop[4] = 0x00;
    cmd_stop[5] = 0x00;
    for (int i=0; i<6;i++)
    {
      cmd_stop[6] += cmd_stop[i];
    }


    unsigned char heart_beat[7] = {0};
    heart_beat[0] = 0x55;
    heart_beat[1] = 0xAA;
    heart_beat[2] = 0x00;
    heart_beat[3] = 0x00;
    heart_beat[4] = 0x00;
    heart_beat[5] = 0x02;
    heart_beat[6] = 0x01;

    init_socket_client(&sock_cli);
    
 
    while(1)
    {
	if(time(NULL) - last_recv_time > 10)
	{
		printf("#########igniter_client timeout!!!!!!!!! wait for reconnect!!\n");
		printf("#########igniter_client recv_time %d\n",(int)(time(NULL) - last_recv_time));
		close(sock_cli);
		sock_cli = -1;
		init_socket_client(&sock_cli);
		last_recv_time = time(NULL);
	}

        /*把可读文件描述符的集合清空*/
        FD_ZERO(&rfds);
        /*把标准输入的文件描述符加入到集合中*/
        FD_SET(0, &rfds);
        maxfd = 0;
        /*把当前连接的文件描述符加入到集合中*/
        FD_SET(sock_cli, &rfds);
        /*找出文件描述符集合中最大的文件描述符*/   
        if(maxfd < sock_cli)
            maxfd = sock_cli;
        /*设置超时时间*/
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        /*等待聊天*/
        retval = select(maxfd+1, &rfds, NULL, NULL, &tv);

        if(retval == -1)
        {
            printf("select出错，客户端程序退出\n");
	    close(sock_cli);
   	    init_socket_client(&sock_cli);
            continue;
        }
        else if(retval == 0)
        {
//	   if(send_flag==0)
//		printf("retval = 0\n");
            
           if(fire_on)
	   {
	       int ret = send(sock_cli, cmd_fire, sizeof(cmd_fire),0); //发送“点火”信号

		if(ret < 0)
		{
			printf("#########igniter_client socket send error!\n");
			close(sock_cli);
			init_socket_client(&sock_cli);
			continue;
		}

		//last_send_time = time(NULL);
		igniter_status = TRUE;
		fire_on = FALSE;  //不建议连续发
		printf("#########igniter_client socket fire_on\n");
	    }

	    if(fire_off)
	    {
		if(igniter_status)  //点火器处于点火状态
		{
			int ret = send(sock_cli, cmd_stop, sizeof(cmd_stop),0); //发送“熄火”信号

			if(ret < 0)
			{
				printf("#########igniter_client socket send error!\n");
				close(sock_cli);
				init_socket_client(&sock_cli);
				continue;
			}
		}

		//last_send_time = time(NULL);
		igniter_status = FALSE;
		fire_off = FALSE;  //不建议连续发
		printf("#########igniter_client socket fire_off\n");
	    }

           if( time(NULL) - last_send_time > 3)  //每3秒发一次心跳包
	   {
		int ret = send(sock_cli, heart_beat, sizeof(heart_beat),0); //发送“熄火”信号

		if(ret < 0)
		{
		   printf("#########igniter_client socket send error!\n");
		   close(sock_cli);
		   init_socket_client(&sock_cli);
                   continue;
		}

		last_send_time = time(NULL);
		printf("#########igniter_client socket heart_beat\n");
	    }

        }
        else
        {
            /*服务器发来了消息*/
            if(FD_ISSET(sock_cli,&rfds))
            {
                unsigned char recvbuf[BUFFER_SIZE];
                int ret = recv(sock_cli, recvbuf, sizeof(recvbuf),0);
                for(int i = 0;i < 7;i++)
                {
                   printf("%X,",recvbuf[i]);
                }
                printf("\n");
                memset(recvbuf, 0, sizeof(recvbuf));

		if(ret < 0)
		{
			 printf("#########igniter_client recv error!\n");
			 close(sock_cli);
			 init_socket_client(&sock_cli);
			 continue;
		 }

		 last_recv_time = time(NULL);
            }

            /*用户输入信息了,开始处理信息并发送*/
            if(FD_ISSET(0, &rfds))
            {
                char sendbuf[BUFFER_SIZE];
                fgets(sendbuf, sizeof(sendbuf), stdin);
//                send(sock_cli, sendbuf, strlen(sendbuf),0); //发送

                if(0 == strcmp(sendbuf,"1\n"))
                {
                  fire_off = 0;
                  fire_on=1;
                  printf("cmd_fire\n");
                }

                if(0 == strcmp(sendbuf,"2\n"))
                {
		  fire_on=0;
                  fire_off=1;
                  printf("cmd_stop\n");
                }

		if(0 == strcmp(sendbuf,"0\n"))
                {
                  printf("exit\n");
                  break; 
                }

                memset(sendbuf, 0, sizeof(sendbuf));
            }
        }
      }
 
    close(sock_cli);
    return 0;
}

