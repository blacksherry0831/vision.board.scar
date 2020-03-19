#ifndef TCP_SERVER_H
#define TCP_SERVER_H
/*-----------------------------------*/
#include "linux_header.h"
#include "def.h"
#include "base.h"


#include "tcp_server.h"


/*-----------------------------------*/
extern pthread_t init_tcp_server(void *_data);
extern pthread_t tcp_telnet(void *_data);
extern pthread_t tcp_trans_row_data(void *_data);
/*-----------------------------------*/
extern void* tcp_process_data(void *data);
extern void *tcp_cfg_server(void *_data);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
typedef struct {
	int port;  //端口号
	int svr_fd; //服务器端描述符
	int client_fd;  //客户端描述符
	void* (*pfunClient)(void*);  //客户端线程调用的函数

}TCP_SERVER;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void *tcp_server(void* _data);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#define HEART_BEAT_FREQUENCY  (5)
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#endif
