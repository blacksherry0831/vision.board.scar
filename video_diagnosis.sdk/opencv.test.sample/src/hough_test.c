#define _BSD_SOURCE
#define _GNU_SOURCE
#define _XOPEN_SOURCE 500
#include <assert.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include<sched.h>
#include<netinet/in.h>
#include <netinet/ip.h>
#include <sys/syscall.h>

#include <sys/socket.h>
#include <linux/netlink.h>
#include <sys/mman.h>
#include <pthread.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/shm.h>

#include "opencv2/opencv.hpp"

//#include "opencv2/core/types_c.h"

#include <iostream>


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

#define MYPORT  8899
#define BUFFER_SIZE 1024

static void help()
{
    cout << "\nThis program demonstrates line finding with the Hough transform.\n"
            "Usage:\n"
            "./houghlines <image_name>, Default is pic1.png\n" << endl;
}

int opencv_test(int argc, char** argv)
{
    const char* filename = argc >= 2 ? argv[1] : "pic1.png";

    Mat src = imread(filename, 0);
    if(src.empty())
    {
        help();
        cout << "can not open " << filename << endl;
        return -1;
    }

    Mat dst, cdst;
    Canny(src, dst, 50, 200, 3);  //canny边缘检测
    cvtColor(dst, cdst, COLOR_GRAY2BGR);  //GRAY2BGR

    cv::imwrite("canny.png",dst);
    cv::imwrite("gray.png",cdst);

#if 0
    vector<Vec2f> lines;
    HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );

    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
    }
#else
    vector<Vec4i> lines;
    HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
    }
#endif

    cv::imwrite("xx.png",cdst);

    return 0;
}

int main(int argc, char** argv)
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

	//定义sockfd
	sock_cli = socket(AF_INET,SOCK_STREAM, 0);
	//定义sockaddr_in
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(MYPORT);  //服务器端口
	servaddr.sin_addr.s_addr = inet_addr("192.168.0.202");  ///服务器ip

	//连接服务器，成功返回0，错误返回-1
	if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("connect error\n");
	    exit(1);
	}
	else
	{
		printf("connect successfully\n");

	    while(1){
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
	        tv.tv_sec = 5;
	        tv.tv_usec = 0;
	        /*等待聊天*/
	        retval = select(maxfd+1, &rfds, NULL, NULL, &tv);

	        if(retval == -1)
	        {
	            printf("select出错，客户端程序退出\n");
	            break;
	        }
	        else if(retval == 0)
	        {
	            printf("客户端没有任何输入信息，并且服务器也没有信息到来，waiting...\n");
	            continue;
	        }
	        else
	        {
	            /*服务器发来了消息*/
	            if(FD_ISSET(sock_cli,&rfds))
	            {
	                unsigned char recvbuf[BUFFER_SIZE];
	                int len = recv(sock_cli, recvbuf, sizeof(recvbuf),0);
	                for(int i = 0;i < 7;i++)
	                {
	                   printf("%X,",recvbuf[i]);
	                }
	                printf("\n");
	                memset(recvbuf, 0, sizeof(recvbuf));
	            }
	            /*用户输入信息了,开始处理信息并发送*/
	            if(FD_ISSET(0, &rfds))
	            {
	                char sendbuf[BUFFER_SIZE];
	                fgets(sendbuf, sizeof(sendbuf), stdin);

	                if(0 == strcmp(sendbuf,"1\n"))
	                {
	                  send(sock_cli, cmd_fire, sizeof(cmd_fire),0); //发送
	                  printf("cmd_fire\n");
	                }

	                if(0 == strcmp(sendbuf,"2\n"))
	                {
	                  send(sock_cli, cmd_stop, sizeof(cmd_stop),0); //发送
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
	}

	close(sock_cli);
	return 0;
}
