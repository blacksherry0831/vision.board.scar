#ifndef IMG_CFG_H
#define IMG_CFG_H
/*-----------------------------------*/
#include "linux_header.h"
#include "cfg.h"
/*-----------------------------------*/
#include "modules_ex/type.h"
#include "modules_ex/cmd_scar.h"
/*-----------------------------------*/
#include <modules/opencv2/core/types_c.h>
/*-----------------------------------*/
#include <modules_up/png_up.h>
/*-----------------------------------*/
#include "modules/cJSON/cJSON.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/def_hw_zynq7000_hi3516.h"
#include "module_zynq7000_hi3516/dma_83c1_ex.h"
/*-----------------------------------*/
#include "scar_cfg.h"
/*-----------------------------------*/
void sendImageStart_DetectSno(
		const int _frame_total,
		const int _sno);
/*-----------------------------------*/

#endif
