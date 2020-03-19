#ifndef  THREAD_WORK_IMG_TRANS_H
#define  THREAD_WORK_IMG_TRANS_H
/*-----------------------------------*/
#include "linux_header.h"
/*-----------------------------------*/
#include "def_app.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/axi_base.h"
/*-----------------------------------*/

/*-----------------------------------*/
#include "modules_ex/tcp_server.h"
/*-----------------------------------*/
#include "msg_queue/msg_sysV_queue.h"
/*-----------------------------------*/
#include "sync/sync_img_msg_q.h"

#include "sync/sync_task.h"
#include "sync/sync_global.h"
#include "sync/sync_task.h"
/*-----------------------------------*/
pthread_t tcp_image_buff_trans_server(void *_data);
/*-----------------------------------*/
#endif
