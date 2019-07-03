#ifndef  THREAD_WORK_IMG_TRANS_H
#define  THREAD_WORK_IMG_TRANS_H
/*-----------------------------------*/
#include "linux_header.h"
/*-----------------------------------*/

/*-----------------------------------*/
#include "module_zynq7000_hi3516/axi_base.h"
/*-----------------------------------*/
#include "task/task_sync.h"
/*-----------------------------------*/
#include "modules_ex/tcp_server.h"
/*-----------------------------------*/
#include "msg_queue/msg_sysV_queue.h"
/*-----------------------------------*/
pthread_t tcp_image_buff_trans_server(void *_data);
/*-----------------------------------*/
#endif
