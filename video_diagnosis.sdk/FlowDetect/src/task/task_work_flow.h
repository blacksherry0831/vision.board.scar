#ifndef 	_TASK_WORK_FLOW_H_
#define 	_TASK_WORK_FLOW_H_
/*-----------------------------------*/
#include <stdio.h>
#include <time.h>
/*-----------------------------------*/
#include <sys/time.h>    // for gettimeofday()
/*-----------------------------------*/
#include "linux_c_def.h"
/*-----------------------------------*/
#include "modules/printf_log/printf_log.h"
/*-----------------------------------*/
#include "modules_ex/type.h"
/*-----------------------------------*/
#include "sync/sync_pl_mem_4_8_lock.h"
/*-----------------------------------*/
#include "sync/sync_task.h"
/*-----------------------------------*/
#include "status.h"
/*-----------------------------------*/
#include "task_circle.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/axi_fpga_ctrl_img.h"
/*-----------------------------------*/

#include "fpga_second/fpga_second.h"
#include "sync/sem_sync.h"
#include "cfg.h"

void CvtFrameScar(unsigned int _base_idx,unsigned int current_idx,const int _org,const int _fi);

#endif
