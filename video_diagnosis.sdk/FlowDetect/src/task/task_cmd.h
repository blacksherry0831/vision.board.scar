#ifndef 	_TASK_CMD_H_
#define 	_TASK_CMD_H_
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
/*-----------------------------------*/
#include "status.h"
/*-----------------------------------*/
int SetFpgaCircleWorkMode(int _wm);
/*-----------------------------------*/
#endif