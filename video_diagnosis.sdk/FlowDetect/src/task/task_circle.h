#ifndef 	_TASK_CIRCLE_H_
#define 	_TASK_CIRCLE_H_
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

/*-----------------------------------*/
#include "sync/sync_task.h"
#include "sync/sync_fpga_cvt_circle.h"
#include "sync/sync_global.h"
/*-----------------------------------*/
#include "status.h"
/*-----------------------------------*/
int IsCircleTaskRunning();
/*-----------------------------------*/
#endif
