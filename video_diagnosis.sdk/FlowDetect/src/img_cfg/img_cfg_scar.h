#ifndef _IMG_CFG_SCAR_H_
#define _IMG_CFG_SCAR_H_
/*-----------------------------------*/
#include "linux_header.h"
#include "cfg.h"
/*-----------------------------------*/
#include "modules_ex/type.h"
#include "modules_ex/cmd_scar.h"
/*-----------------------------------*/

/*-----------------------------------*/
#include <modules_up/png_up.h>
/*-----------------------------------*/
#include "modules/cJSON/cJSON.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/def_hw_zynq7000_hi3516.h"
#include "module_zynq7000_hi3516/dma_83c1_ex.h"
/*-----------------------------------*/
#include "scar_cfg.h"
#include "sync/sync_pl_mem_4_8_lock.h"
#include "sync/sync_ps_mem_0_4_lock.h"
/*-----------------------------------*/
void sendImageStart_DetectSno(
		const int _frame_total,
		const int _sno);
/*-----------------------------------*/
void Save_And_Dma_ImageMask_Scar(CMD_CTRL*  _cmd);
/*-----------------------------------*/
void Clear_And_Dma_ImageMask_Scar(CMD_CTRL*  _cmd);
/*-----------------------------------*/

void  InitMaskImage_scar();

#endif
