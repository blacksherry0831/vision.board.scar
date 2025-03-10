#ifndef _DMA_83c0_EX_H_
#define _DMA_83c0_EX_H_
/*-----------------------------------*/
#include "linux_header.h"

#include "module_zynq7000_hi3516/dma_83c0.h"
#include "module_zynq7000_hi3516/mem_pl.h"

#include "modules_ex/base.h"

#include "../img_cfg/img_cfg.h"

#include "module_zynq7000_hi3516/axi_base.h"

/*-----------------------------------*/
#include "hw_module_base/axi_api.h"
/*-----------------------------------*/
#include "status.h"
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

/*-----------------------------------*/
int 	memcpyDMA2MemChEx(CMD_CTRL* img,const  int _space_ch,const int _space_fr);

void dmac_trans_all_frame();
/*-----------------------------------*/

/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

#endif
