#ifndef DEF_HW_ZYNQ7000_HI3516_DMAC_H
#define DEF_HW_ZYNQ7000_HI3516_DMAC_H

/*-----------------------------------*/
#define TRANSFER_DATA_WITH_DMA
/*-----------------------------------*/
#ifdef TRANSFER_DATA_WITH_DMA

#define PS_DDR_LENGTH_FOR_DMA_8M 	(0x800000)
#define PS_DDR_LENGTH_FOR_DMA_16M 	(0x1000000)
#define PS_DDR_LENGTH_FOR_DMA_32M 	(0x2000000)

/*********************dmac***********************/
#define PS_DDR_PHYADDR_FOR_DMA_83C0 		0x1E000000
#define PS_DDR_LENGTH_FOR_DMA_83C0 	 		PS_DDR_LENGTH_FOR_DMA_32M
/*********************dmac***********************/
#define PS_DDR_PHYADDR_FOR_DMA_83C4 		0x20000000
#define PS_DDR_LENGTH_FOR_DMA_83C4 	 		PS_DDR_LENGTH_FOR_DMA_8M
/*********************dmac config****************/
#define PS_2_PL_DMA_BASEADDR_83C4 0x83C40000
#define PL_2_PS_DMA_BASEADDR_83C0 0x83C00000
/************************************************/
#define PL_RX_DMA_MMAP_LENGTH 0x1000
/************************************************/
#if 1
#define PS_MALLOC_BUFFER_MAXNUM 16
#define EACH_BUFFER_SIZE_FOR_DMA 0x1000000
#define EACH_FRAME_SIZE_FOR_CAMERA (1920*1080)
#endif
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
#define AXI_DMAC_CTRL_PAUSE				(1 << 1)
#define AXI_DMAC_IRQ_SOT				(1 << 0)
#define AXI_DMAC_IRQ_EOT				(1 << 1)

#endif


#endif
