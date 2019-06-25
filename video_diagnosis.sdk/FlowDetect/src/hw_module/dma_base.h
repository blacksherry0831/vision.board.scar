#ifndef DMA_H
#define DMA_H
/*-----------------------------------*/
#include "../linux_header.h"
#include "../outside_process.h"
#include "../base.h"
#include "../img_cfg/img_cfg.h"
#include "../storage/circular_queue.h"
#include "../axi_base.h"
#include "../flow_ctrl/flow_sync.h"
/*-----------------------------------*/
#include "dma_hw.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int 	dmac_trans(unsigned char _ch,int _frame);
/*-----------------------------------*/
int 	memcpyDMA2MemChEx(CMD_CTRL* img,unsigned int _ch);
/*-----------------------------------*/
int 	Wait4DmaTransDone(long timeout_ms);
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

#endif
