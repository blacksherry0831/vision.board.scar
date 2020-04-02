#ifndef 	_FPGA_CMD_SCAR_MODUOLE_H_
#define 	_FPGA_CMD_SCAR_MODUOLE_H_
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
/*-----------------------------------*/
#include "sync/sync_global.h"
#include "sync/sync_fpga_cvt_circle.h"
#include "task/task_cmd.h"
#include "sync/sync_task.h"
#include "sync/sem_sync.h"
#include "flame_monitor.h"
#include "flame/flame_sync.h"
/*-----------------------------------*/

void setFpgaCircleCmdScar(const CMD_CTRL* const _cmd_ctrl);

#endif
