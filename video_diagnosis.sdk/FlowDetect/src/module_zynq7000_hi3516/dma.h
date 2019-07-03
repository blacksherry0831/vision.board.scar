#ifndef DMA_H
#define DMA_H
/*-----------------------------------*/
#include "../linux_header.h"
#include "../linux_c_def.h"
/*-----------------------------------*/
#include "def_hw_zynq7000_hi3516.h"
/*-----------------------------------*/
#include "modules_ex/base.h"
#include "../img_cfg/img_cfg.h"
/*-----------------------------------*/

/*-----------------------------------*/
#include "status.h"
/*-----------------------------------*/
#define  AXI_MAP_FRAME(X)   (X)
#define  AXI_MAP_AVERAGE	 AXI_MAP_FRAME(-1)
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

#define TRANSFER_DATA_WITH_DMA


#ifdef TRANSFER_DATA_WITH_DMA
/*********************dmac***********************/
int dmac_transfer_init(void);
int dmac_addr_mmap(void);
int dmac_addr_unmap(void);
void dmac_trans(unsigned char _ch,int _frame);
void memcpyDMA2MemCh(void *buff_dst,unsigned int _size,unsigned int _ch);
/*-----------------------------------*/
int Wait4DmaTransDone(long timeout_ms);
/*-----------------------------------*/
pthread_t init_dma_server(void *_data);

/*-----------------------------------*/
pthread_mutex_t DMA_mutex_trans0;
/*-----------------------------------*/
int memcpyDMA2MemChEx(CMD_CTRL* img,unsigned int _ch);
/*-----------------------------------*/
void SetCurrentDmaFrame(int _frame);
int  getCurrentDmaFrame();
/*-----------------------------------*/
#endif
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

#endif
