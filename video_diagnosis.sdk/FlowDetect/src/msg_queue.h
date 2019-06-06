#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include "linux_header.h"
#include "def.h"
#include "printf_log.h"

struct my_msg_st {
    long int my_msg_type;
    char some_text[BUFSIZ];
};


#define PMODE 0666

int open_queueN(const char*_name);
int close_queue(mqd_t mqfd);
int send_queue_mq(mqd_t mqfd,const char* msg_buffer,int num_bytes_to_send);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  open_queue_img_buff();
int  send_queue_img_buff(void * _data);
void * rcv_queue_imag_buff();
void destory_queue_img_buff();
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#endif
