#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#include "linux_header.h"
#include "def.h"
#include "modules_ex/tcp_server.h"
#include "opencv2/opencv.hpp"
#include "flame_monitor.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
typedef struct {

	long int message_type;

	void* _data;

}MESSAGE;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  get_queue_img_buff();
int  remove_queue_img_buff();
int  snd_queue_img_buff(void * _data);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  snd_queue_img_buff(void * _data);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
MESSAGE  rcv_queue_img_buff();

MESSAGE  rcv_queue_img_buff_ex();

MESSAGE  rcv_queue_img_buff_ex_inner();
/*-----------------------------------*/
int msgTypeImage();
/*-----------------------------------*/
#endif
