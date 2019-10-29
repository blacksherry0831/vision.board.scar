#ifndef DMA_83C0_H
#define DMA_83C0_H
/*-----------------------------------*/
#include "../linux_header.h"
#include "def_hw_zynq7000_hi3516.h"
#include "modules_ex/base.h"
#include "../img_cfg/img_cfg.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/axi_base.h"
/*-----------------------------------*/
#include "dma_hw_base.h"
/*-----------------------------------*/
#define  AXI_MAP_FRAME(X)   (X)
#define  AXI_MAP_AVERAGE	 AXI_MAP_FRAME(-1)
/***********************************************/
int				dmac_83c0_transfer_init(void);
int				dmac_83c0_addr_mmap_hw(void);
int				dmac_83c0_addr_unmap_hw(void);
int 			dmac_83c0_config_and_transfer(unsigned int dst_phyaddr, unsigned int src_phyaddr, unsigned int len);
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#endif
