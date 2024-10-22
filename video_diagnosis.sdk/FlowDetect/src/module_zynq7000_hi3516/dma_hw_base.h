#ifndef DMA_HW_BASE_H
#define DMA_HW_BASE_H
/*-----------------------------------*/
#include "linux_header.h"
#include <stdint.h>
#include <fcntl.h>
/*-----------------------------------*/
#include <linux/types.h>
/*-----------------------------------*/
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
/*-----------------------------------*/
#include <assert.h>
/*-----------------------------------*/
#include "modules/printf_log/printf_log.h"
/*-----------------------------------*/
#include "def_hw_zynq7000_hi3516.h"
/*-----------------------------------*/
typedef struct _DMA_PS_PL_OBJECT
{
	 char DEV[256];

	uint32_t transfer_id;
	off_t   DMA_Base_Addr_Phy;
	size_t  DMA_Space_size;
	unsigned char *DMA_Base_Addr_Virtual;

	off_t   MEM_PS_Base_Addr_Phy;
	size_t  MEM_PS_Space_size;

	unsigned char *MEM_PS_Base_Addr_Virtual;


	pthread_mutex_t lock;
}DMA_PS_PL_OBJ;
/*-----------------------------------*/
int dmac_addr_mmap_hw_base(DMA_PS_PL_OBJ* _dma_obj);
int dmac_addr_unmap_hw_base(DMA_PS_PL_OBJ* _dma_obj);
int dmac_config_and_transfer_base(DMA_PS_PL_OBJ* 	_dma_obj,
		unsigned int dst_phyaddr,
		unsigned int src_phyaddr,
		unsigned int len);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#endif
