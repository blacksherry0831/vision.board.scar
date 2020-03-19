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
	int port;
	int svr_fd;
	int client_fd;
	void* (*pfunClient)(void*);

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
