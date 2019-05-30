#include "tcp_server.h"

void * tcp_send_data(void *arg);



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





static struct filename filename_config[]= {
		{"tcp_data.txt", "tcp_len.txt", TCP_PROTOCOL},
		{"udp_data.txt", "udp_len.txt", UDP_PROTOCOL},
		{"ip_data.txt", "ip_len.txt", IP_PROTOCOL},
};


//#define EACH_FRAME_SIZE_FOR_CAMERA 1920*1080


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
void *tcp_server(void* _data)
{
	assert(_data!=NULL);
    struct sockaddr_in *server = (struct sockaddr_in *)mem_malloc(socket_struct_len);
    struct sockaddr_in *client = (struct sockaddr_in *)mem_malloc(socket_struct_len);
    const  unsigned int client_size = sizeof(*client);

    int sockfd=-1;
    int err=-1;
    int tmp = 1;

    const int send_buf_size = 16*1024*1024;

    TCP_SERVER* tcp_server=(TCP_SERVER*)_data;
    const int server_port=tcp_server->port;
    /*设置服务器地址*/
    server->sin_family = AF_INET;

    server->sin_port = htons( tcp_server->port);

    server->sin_addr.s_addr = inet_addr("0.0.0.0");
    /*建立一个流式套接字*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    int sock_flags = fcntl(sockfd, F_GETFL, 0);
    printf("sock_flag 0x%x\n",sock_flags);
    err = fcntl(sockfd, F_SETFL,sock_flags|O_NONBLOCK);
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
#if 1
    err = set_socket_buf_size(sockfd,send_buf_size);
    if(err < 0){
    	 printf_error();
    	 goto EXIT_TCP_SERVER;
    }
#endif
    err = bind(sockfd, (struct sockaddr*)server, sizeof(*server));
    if(err==-1){
    	 printf_error();
    	 goto EXIT_TCP_SERVER;
    }
    /*监听端口*/
    listen(sockfd, SOMAXCONN);/*侦听队列长度*/

    do{

    	   err =SelectAccept(sockfd,30);
    	   if(err==0){
    		   continue;//time out
    	   }else if(err==-1){
    		   break;//fali
    	   }else if(err==1){

#if 1
		pthread_t _thread_ap_id;
		int* volatile _clientfd_ptr=mem_malloc(sizeof(int));
		*_clientfd_ptr = accept(sockfd, (struct sockaddr*)client, &client_size);

		if (*_clientfd_ptr < 0 ){
			PRINTF_DBG("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
				break;
		}else{
			if(IsRun()){
				PRINTF_DBG("Connected to %s:%u\n",inet_ntoa(client->sin_addr),ntohs(client->sin_port));
					if(pthread_create(&_thread_ap_id,NULL,tcp_server->pfunClient,_clientfd_ptr) == -1){
						 fprintf(stderr,"pthread_create error!\n");
					}
			}else{
				close(*_clientfd_ptr);
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

	mem_free_clr(&server);
    mem_free_clr(&client);
    mem_free_clr(&_data);

    ExitTcpServer(sockfd,server_port);
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
int tcp_client_trans_row_data(int sc)
{
	int write_num=0;
    unsigned char Chn_num=0;

    unsigned char* BUFF=mem_malloc(image_size_frame());



                for(Chn_num=0;Chn_num<8;Chn_num++){

                	TIME_START();
                	dmac_trans(Chn_num,0);
                	TIME_END("DMA");

                	memcpyDMA2MemCh(BUFF,image_size_frame(),Chn_num);
                	write_num=writen(sc,BUFF,image_size_frame());
                }





    mem_free_clr(&BUFF);
   	return  write_num==image_size_frame();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

extern unsigned int g_pl_ddr_pyhaddr;
unsigned long TIMECOUNT=0;

static int g1 = 0, g2 = 0, g3 = 0;


/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

void* tcp_trans_row_image_2(void *_data)
{

	int *_clientfd_p=(int*)_data;
	int sock_server=*_clientfd_p;
	int socket_status=TRUE;
	mem_free_clr(&_data);

	StartFpgaCircle(WM_SIZE_FULL|WM_DIFF_IMG);

	PRINTF_DBG("tcp_trans_row_image>>send Start FPGA signal \n");

	/*-----------------------------------*/
		while(IsRun() && socket_status){

									MESSAGE msg=rcv_queue_img_buff();

									CMD_CTRL *img_data=msg._data;

									if(msg.message_type==ENOMSG){
										  usleep(5*1000);
									}else{

											if(IsImageFrame(img_data)){
#if 1
												 TIME_START();
												 	 socket_status=socket_write_1_cmd_raw_release(sock_server,img_data);
												 TIME_END("tcp send a frame cost :");
#else
												 ReleaseCmdCtrl(&img_data);
#endif
											}else{
												 ReleaseCmdCtrl(&img_data);
											}

									}

		}
	/*-----------------------------------*/
		close(sock_server);

		StopFpgaCircleRunning();

		PRINTF_DBG("pthread>>tcp data transfer thread is close\n");
		pthread_exit(NULL);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
