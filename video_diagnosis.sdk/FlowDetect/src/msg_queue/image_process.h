#ifndef _IMAGE_PROCESS_H_
#define _IMAGE_PROCESS_H_
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
void  image_proc(const MESSAGE _msg,const int _draw);
/*-----------------------------------*/

#endif
