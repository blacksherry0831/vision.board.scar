#ifndef _DMA_83C1_H
#define _DMA_83C1_H
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
int				dmac_83c1_transfer_init(void);
int				dmac_83c1_addr_mmap_hw(void);
int				dmac_83c1_addr_unmap_hw(void);
int 			dmac_83c1_config_and_transfer(
							unsigned int dst_phyaddr,
							unsigned int src_phyaddr,
							unsigned int len);
/*-----------------------------------*/
int				dmac_83c1_pthread_mutex_lock();
int 			dmac_83c1_pthread_mutex_unlock();
/*-----------------------------------*/
unsigned char *dmac_83c1_get_mem_ps_phy_base_addr();
unsigned char *dmac_83c1_get_mem_ps_virtual_base_addr();
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#endif
