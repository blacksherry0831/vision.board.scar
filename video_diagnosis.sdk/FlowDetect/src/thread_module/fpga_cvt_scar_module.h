#ifndef 	_FPGA_CVT_SCAR_MODULE_H_
#define 	_FPGA_CVT_SCAR_MODULE_H_
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
#include "module_zynq7000_hi3516/axi_fpga_ctrl_img_scar.h"
/*-----------------------------------*/
#include "status.h"
/*-----------------------------------*/
#include "fpga_cvt_module.h"

#include "sync/sync_task.h"
#include "sync/sync_global.h"
#include "sync/sync_task.h"
#include "thread_module/fpga_cvt_module.h"
#include "thread_module/fpga_cvt_module.h"
#include "status.h"
#include "img_cfg/img_cfg_scar.h"
#include "cfg.h"
#include "task/task_work_flow.h"
/*-----------------------------------*/

void theFirstCircleScar();
void theSecondCircleScar();

int GetMaskSeqFrames();
/*-----------------------------------*/
#endif
