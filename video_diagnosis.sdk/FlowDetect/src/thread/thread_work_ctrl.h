#ifndef  THREAD_WORK_CTRL_H
#define  THREAD_WORK_CTRL_H
/*-----------------------------------*/
#include "../linux_header.h"
/*-----------------------------------*/

#include "module_zynq7000_hi3516/axi_base.h"
#include "module_zynq7000_hi3516/dma.h"
#include "task/task_sync.h"
/*-----------------------------------*/
#include "modules_ex/tcp_server.h"
/*-----------------------------------*/
pthread_t task_flow_ctrl_server();
/*-----------------------------------*/
#endif
