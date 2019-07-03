#ifndef DMA_HW_H
#define DMA_HW_H
/*-----------------------------------*/
#include "../linux_header.h"
#include "def_hw_zynq7000_hi3516.h"
#include "modules_ex/base.h"
#include "../img_cfg/img_cfg.h"

#include "module_zynq7000_hi3516/axi_base.h"

/*-----------------------------------*/

/*-----------------------------------*/
#define  AXI_MAP_FRAME(X)   (X)
#define  AXI_MAP_AVERAGE	 AXI_MAP_FRAME(-1)
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

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#endif
