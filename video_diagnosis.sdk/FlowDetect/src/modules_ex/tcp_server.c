#include "tcp_server.h"
/*-----------------------------------*/
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <netinet/in.h>
/*-----------------------------------*/
const unsigned int socket_struct_len = sizeof(struct sockaddr_in);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
struct filename{
		unsigned char data_file[32];
		unsigned char len_file[32];
		unsigned char index;
	};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

char target_addr[20] = {0};
int target_port = 0;
char server_addr[20] = {0};
int server_port = 0;


unsigned int tcp_len=0;
unsigned int udp_len=0;
unsigned int ip_len=0;

//***********传输变量定义**********************

#define Amax 2001
#define Qmax 10000

//*****************************************

union position{
	unsigned long lpos;
	unsigned char cpos[4];
	}pos;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int set_keepalive(const int fd)
{
	const int keep_alive = 1;
	const int keep_idle = 6;//s
	const int keep_interval = 5;//s
	const int keep_count = 2;

	if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &keep_alive, sizeof(keep_alive)) == -1) {
		PRINTF_DBG_EX("setsockopt SO_KEEPALIVE: %s", strerror(errno));
		return -1;
	}

#ifdef __linux__
	if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &keep_idle, sizeof(keep_idle)) < 0) {
		PRINTF_DBG_EX("setsockopt TCP_KEEPIDLE: %s\n", strerror(errno));
		return -1;
	}

	if (setsockopt(fd, SOL_TCP,TCP_KEEPINTVL, (void *)&keep_interval, sizeof(keep_interval)) < 0) {
		PRINTF_DBG_EX("setsockopt TCP_KEEPINTVL: %s\n", strerror(errno));
		return -1;
	}

	if (setsockopt(fd, SOL_TCP,TCP_KEEPCNT, (void *)&keep_count, sizeof(keep_count)) < 0) {
		PRINTF_DBG_EX("setsockopt TCP_KEEPCNT: %s\n", strerror(errno));
		return -1;
	}
#endif
	return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void setSockSndTimeOut_5s(const int _sock_fd)
{

	//struct timeval tv;
	//	tv.tv_sec = 5;
	//	tv.tv_usec = 0;

	int network_chek_time = GetNetworkCheckTime();
	if(network_chek_time <= 0)
	{
		network_chek_time = 5000;
		SetNetworkCheckTime(network_chek_time);
		StoreImgCfgJson();
	}

	struct timeval tv;
	tv.tv_sec = network_chek_time/1000;
	tv.tv_usec = (network_chek_time%1000)*1000;

	setsockopt(_sock_fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void setSockRcvTimeOut_5s(const int _sock_fd)
{

	//struct timeval tv;
	//	tv.tv_sec = 5;
	//	tv.tv_usec = 0;

	int network_chek_time = GetNetworkCheckTime();
	if(network_chek_time <= 0)
	{
		network_chek_time = 5000;
		SetNetworkCheckTime(network_chek_time);
		StoreImgCfgJson();
	}

	struct timeval tv;
	tv.tv_sec = network_chek_time/1000;
	tv.tv_usec = (network_chek_time%1000)*1000;

	setsockopt(_sock_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

}
/*-----------------------------------*/
/**
 *关闭并退出服务端线程
 */
/*-----------------------------------*/
void ExitTcpServer(int socket_fd,int server_port)
{
	close(socket_fd);
	PRINTF_DBG_EX("pthread close>> [TcpServer:%d]\n",server_port);
	pthread_exit(NULL);
}
/*-----------------------------------*/
/**
 *服务端线程-起始函数
 */
/*-----------------------------------*/
void *tcp_server(void* _data)
{
	assert(_data!=NULL);
    struct sockaddr_in *server = (struct sockaddr_in *)mem_malloc(socket_struct_len);  //申请空间
    struct sockaddr_in *client = (struct sockaddr_in *)mem_malloc(socket_struct_len);  //申请空间
    const  unsigned int client_size = sizeof(*client);

    int sockfd=-1;
    int err=-1;
    int tmp = 1;
    const int send_buf_size = 16*1024*1024;
    TCP_SERVER* tcp_server=(TCP_SERVER*)_data;
    const int server_port=tcp_server->port;

    server->sin_family = AF_INET;  //协议族类型 IPv4
    server->sin_port = htons( tcp_server->port);  //端口
    server->sin_addr.s_addr = inet_addr("0.0.0.0");  // ip，INADDR_ANY为通配地址其值为0

    /*建立一个流式套接字*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //socket设置为非阻塞方式
    int sock_flags = fcntl(sockfd, F_GETFL, 0);  //读取socket描述符状态
    printf("sock_flag 0x%x\n",sock_flags);
    err = fcntl(sockfd, F_SETFL,sock_flags|O_NONBLOCK);  //socket设置为非阻塞方式
    if(err < 0){
    	 printf_error();
    	 goto EXIT_TCP_SERVER;
    }

    /*一个端口释放后会等待两分钟之后才能再被使用，SO_REUSEADDR是让端口释放后立即就可以被再次使用*/
    err = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(int));
    if(err < 0){
    	 printf_error();
    	 goto EXIT_TCP_SERVER;
    }

   err= set_keepalive(sockfd);

   if(err<0){
	   printf_error();
	   goto EXIT_TCP_SERVER;
   }

#if 1
    //设置socket的发送缓冲区大小
    err = set_socket_buf_size(sockfd,send_buf_size);
    if(err < 0){
    	 printf_error();
    	 goto EXIT_TCP_SERVER;
    }
#endif

    //服务器监听地址
    err = bind(sockfd, (struct sockaddr*)server, sizeof(*server));
    if(err==-1){
    	 printf_error();
    	 goto EXIT_TCP_SERVER;
    }

    //服务器监听端口
    listen(sockfd, SOMAXCONN);/*侦听队列长度*/

    do{
    	err =SelectAccept(sockfd,30);  //判断set集合中描述符socketfd是否准备好可读
    	   if(err==0){
    		   continue;//time out
    	   }else if(err==-1){
    		   break;//fali
    	   }else if(err==1){  //准备好了

#if 1
		pthread_t _thread_ap_id;
		int* volatile _clientfd_ptr=(int*)mem_malloc(sizeof(int));
		const int client_fd = accept(sockfd, (struct sockaddr*)client, (socklen_t*)&client_size);  //接受客户端的连接 返回客户端连接的描述符

		*_clientfd_ptr=client_fd;

		if (client_fd < 0 ){
			PRINTF_DBG_EX("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
				break;
		}else{
			if(IsRun()){
				PRINTF_DBG_EX("Connected to %s:%u\n",inet_ntoa(client->sin_addr),ntohs(client->sin_port));
				set_keepalive(client_fd);
				setSockRcvTimeOut_5s(client_fd);
				setSockSndTimeOut_5s(client_fd);
				if(pthread_create(&_thread_ap_id,NULL,tcp_server->pfunClient,_clientfd_ptr) == -1){  //创建与客户端的交互线程
						 fprintf(stderr,"pthread_create error!\n");
				}

			}else{
				close(client_fd);  //关闭客户端交互线程
			}
		}
#endif

    	   }else if(err==-2){
    		   break;
    	   }else{
    		   break;
    	   }

    }while(IsRun());

EXIT_TCP_SERVER:

	mem_free_clr((void**)&server);
    mem_free_clr((void**)&client);
    mem_free_clr(&_data);

    ExitTcpServer(sockfd,server_port);  //关闭并退出服务端线程
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/


/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void cal_image_part(unsigned char* img_src,unsigned char* img_dst,unsigned int* cal,const int WIDTH,const int HEIGHT,int left,int top, int right ,int bottom)
{

	int coli=left;
	int rowi=top;
	int i=0;
#if 0
	for(i=0;i<1920*1080;i++){
		*(img_dst+i)=img_src[cal[i]];
	}

#else
	for(coli=left;coli<right;coli++){
			for(rowi=top;rowi<bottom;rowi++){
				unsigned int idx=coli*1080+rowi;
				*(img_dst+idx)=img_src[cal[idx]];

		}
	}
#endif


}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

/*TCP服务器接受连接后的处理程序*/
extern unsigned char *g_ps_ddr_virtual_baseaddr;
extern int dmac_transfer_init(void);
extern int dmac_transfer_init_copy(unsigned char *dst_virtaddr, unsigned int src_phyaddr, unsigned int len);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
extern unsigned int g_pl_ddr_pyhaddr;
unsigned long TIMECOUNT=0;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
