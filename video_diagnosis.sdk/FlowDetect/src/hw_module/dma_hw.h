#ifndef DMA_HW_H
#define DMA_HW_H
/*-----------------------------------*/
#include "../linux_header.h"
#include "../outside_process.h"
#include "../base.h"
#include "../img_cfg/img_cfg.h"
#include "../storage/circular_queue.h"
#include "../axi_base.h"
#include "../flow_ctrl/flow_sync.h"
/*-----------------------------------*/
#define  MEM_DEV "/dev/mem"
/*-----------------------------------*/
#define  AXI_MAP_FRAME(X)   (X)
#define  AXI_MAP_AVERAGE	 AXI_MAP_FRAME(-1)
/*-----------------------------------*/
#define TRANSFER_DATA_WITH_DMA
/*-----------------------------------*/
#ifdef TRANSFER_DATA_WITH_DMA
/*********************dmac***********************/
#define PS_DDR_PHYADDR_FOR_DMA 	0x1E000000
#define PS_DDR_LENGTH_FOR_DMA 	0x2000000//(1920*1080)
/*********************dmac config****************/
#define PL_RX_DMA_BASEADDR 0x83c00000
#define PL_RX_DMA_MMAP_LENGTH 0x1000
/*********************dmac axi*******************/
#define AXI_DMAC_REG_IRQ_MASK			0x80
#define AXI_DMAC_REG_IRQ_PENDING		0x84
#define AXI_DMAC_REG_IRQ_SOURCE			0x88
#define AXI_DMAC_REG_CTRL				0x400
#define AXI_DMAC_REG_TRANSFER_ID		0x404
#define AXI_DMAC_REG_START_TRANSFER		0x408
#define AXI_DMAC_REG_FLAGS				0x40c
#define AXI_DMAC_REG_DEST_ADDRESS		0x410
#define AXI_DMAC_REG_SRC_ADDRESS		0x414
#define AXI_DMAC_REG_X_LENGTH			0x418
#define AXI_DMAC_REG_Y_LENGTH			0x41c
#define AXI_DMAC_REG_DEST_STRIDE		0x420
#define AXI_DMAC_REG_SRC_STRIDE			0x424
#define AXI_DMAC_REG_TRANSFER_DONE		0x428
#define AXI_DMAC_REG_ACTIVE_TRANSFER_ID 0x42c
#define AXI_DMAC_REG_STATUS				0x430
#define AXI_DMAC_REG_CURRENT_DEST_ADDR	0x434
#define AXI_DMAC_REG_CURRENT_SRC_ADDR	0x438
#define AXI_DMAC_REG_DBG0				0x43c
#define AXI_DMAC_REG_DBG1				0x440
#define AXI_DMAC_CTRL_ENABLE			(1 << 0)
#define AXI_DMAC_CTRL_PAUSE			(1 << 1)
#define AXI_DMAC_IRQ_SOT				(1 << 0)
#define AXI_DMAC_IRQ_EOT				(1 << 1)
/***********************************************/
int		dmac_transfer_init(void);
int		dmac_addr_mmap_hw(void);
int		dmac_addr_unmap_hw(void);
int 	dmac_config_and_transfer(unsigned int dst_phyaddr, unsigned int src_phyaddr, unsigned int len);
/*-----------------------------------*/
void	memcpyDMA2MemCh(void *buff_dst,unsigned int _size,unsigned int _ch);
int 	memcpyDMA2MemChEx(CMD_CTRL* img,unsigned int _ch);
/*-----------------------------------*/
void SetCurrentDmaCh(int _ch);
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
