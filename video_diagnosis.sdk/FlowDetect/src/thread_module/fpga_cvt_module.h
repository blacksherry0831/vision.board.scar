#ifndef 	_FPGA_CVT_MODULE_H_
#define 	_FPGA_CVT_MODULE_H_
/*-----------------------------------*/
#include <stdio.h>
#include <time.h>
/*-----------------------------------*/
#include <sys/time.h>    // for gettimeofday()
/*-----------------------------------*/
#include "linux_c_def.h"
/*-----------------------------------*/
#include "modules/printf_log/printf_log.h"

#include "modules_ex/type.h"

#include "task/task_circle.h"
#include "sync/sem_sync.h"
#include "module_zynq7000_hi3516/axi_base.h"
#include "sync/sync_fpga_cvt_circle.h"
/*-----------------------------------*/
extern volatile int FRAME_IDX_FIRST;
/*-----------------------------------*/
extern volatile int FRAME_IDX_SECOND;
/*-----------------------------------*/

int wait_fpga_start_sig();
int wait4Circle1st();
int wait4Circle2nd();
int IsSecondCircleRunning();
int IsFrameCollect();
int wait4FpgaStart();
void startThisCircle();
void stopThisCircle();
#endif
