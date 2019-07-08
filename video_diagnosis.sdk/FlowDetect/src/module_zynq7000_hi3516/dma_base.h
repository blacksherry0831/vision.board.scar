#ifndef DMA_H
#define DMA_H
/*-----------------------------------*/
#include "linux_header.h"


#include "modules_ex/base.h"

#include "../img_cfg/img_cfg.h"

#include "module_zynq7000_hi3516/axi_base.h"

/*-----------------------------------*/
#include "dma_hw.h"
#include "hw_module_base/axi_api.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int 	dmac_trans(unsigned char _ch,int _frame);
/*-----------------------------------*/
int 	memcpyDMA2MemChEx(CMD_CTRL* img,const  int _space_ch,const int _space_fr);
/*-----------------------------------*/
int 	Wait4DmaTransDone(long timeout_ms);
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

#endif
