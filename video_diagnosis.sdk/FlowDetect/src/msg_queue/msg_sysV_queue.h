#ifndef _MSG_SYSV_QUEUE_H
#define _MSG_SYSV_QUEUE_H
/*-----------------------------------*/
#include "linux_header.h"
#include "def.h"
/*-----------------------------------*/
#include "msg_sysV_q.h"
/*-----------------------------------*/
#include "modules_ex/tcp_server.h"
#include "opencv2/opencv.hpp"
#include "flame_monitor.h"
/*-----------------------------------*/
#include "flame/flame_sync.h"
/*-----------------------------------*/
#include "image_process.h"
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

MESSAGE  rcv_queue_img_buff_image_process(const int _draw);
/*-----------------------------------*/
int msgTypeImage();
/*-----------------------------------*/
#endif
