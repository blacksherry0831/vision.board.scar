#ifndef  THREAD_WORK_CTRL_H
#define  THREAD_WORK_CTRL_H
/*-----------------------------------*/
#include "../linux_header.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/axi_base.h"
/*-----------------------------------*/

/*-----------------------------------*/
#include "modules_ex/tcp_server.h"

#include "thread_module/fpga_cmd_scar_module.h"
#include "modules_ex/type.h"
#include "img_cfg/img_cfg.h"
/*-----------------------------------*/
pthread_t task_flow_ctrl_server();
/*-----------------------------------*/
#endif
