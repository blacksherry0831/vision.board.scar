#ifndef DEF_HW_ZYNQ7000_HI3516_H
#define DEF_HW_ZYNQ7000_HI3516_H
/*-----------------------------------------------------------------------------------------------*/
/**
 *
 *0x4000,0000|0x0000,0000----------------------------------1Ch-Gray-----| 1920*1080*8==16588800==0x00FD,2000
 *			 |0x00FD,2000=1920*1080*(8+0)------------------1Ch-Frame-0--| 1920*1080*1== 2073600==0x001F,A400?
 *			 |------------1920*1080*(8+1)------------------1Ch-Frame-1--| 1920*1080*1== 2073600
 *			 |------------1920*1080*(8+2)------------------1Ch-Frame-2--|
 *			 |------------1920*1080*(8+n)------------------1Ch-Frame-n--|
 *			 |----------------------blank----------------(0x0800,0000-1)| 0x0800,0000==128MB
 *			 @@Channel(N)@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 *		 	 |0x0800,0000*(N-1)----------------------------NCh-Gray-----| 1920*1080*8==16588800==0x00FD,2000
 *			 |------------1920*1080*(8+0)------------------1Ch-Frame-0--| 1920*1080*1== 2073600==0x001F,A400?
 *			 |------------1920*1080*(8+1)------------------1Ch-Frame-1--| 1920*1080*1== 2073600
 *			 |------------1920*1080*(8+2)------------------1Ch-Frame-2--|
 *			 |------------1920*1080*(8+n)------------------1Ch-Frame-n--|
 *			 |----------blank----------------------(0x8,000,000*(N-1)-1)|
 *
 */
/*-----------------------------------------------------------------------------------------------*/
#define PL_DDR3_ADDR_BASE 		 (0x40000000)
/*-----------------------------------*/
#define PL_PARA_ADDR_BASE   	 (0x80000000)
#define PL_PARA_ADDR_SIZE   	 (0x00001000)
/*-----------------------------------*/
#define			DDR3_ADDR		(0x60000000)
/*-----------------------------------*/
#define SPACE_CHANNEL_NUM	(8)
#define SPACE_FRAME_NUM		(64)
/*-----------------------------------*/
#define ADDR_OUTSIDE_RESET       (0x100*4)
#define ADDR_OUTSIDE_DATA_MODE   (0x101*4)
#define ADDR_OUTSIDE_START_EN    (0x102*4)
#define ADDR_OUTSIDE_WORK_MODE   (0x103*4)
/*-----------------------------------*/
#define FLOW_DETECT_THD			 (0x107*4)
/*-----------------------------------*/
#define ADDR_OUTSIDE_BUSY        (0x100*4)
/*-----------------------------------*/
#define ADDR_SENSOR_STATE        (0x110*4)
/*-----------------------------------*/
#define SVM_ENABLE_CTRL			 (0x10A*4)
/*-----------------------------------*/
/**
 *GP1地址声明4K范围
 *uart0~7...
 */
/*-----------------------------------*/
#define			UART0_RSTADDR 			(0x010)//初始化
#define			UART0_RATEADDR 			(0x012)//波特率
#define			UART0_RDENADDR			(0x014)//读使能
#define			UART0_RDATAADDR			(0x015)//取数据
#define			UART0_WDATAADDR			(0x016)//写数据
#define			UART0_STATUSADDR		(0x01F)//数据缓存状态
#define			UART_SIZEADDR 			(0x010)//UART数据地址分区大小

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
#define AXI_DMAC_CTRL_PAUSE			(1 << 1)
#define AXI_DMAC_IRQ_SOT				(1 << 0)
#define AXI_DMAC_IRQ_EOT				(1 << 1)

#endif
/*-----------------------------------*/
#define PATH_SDCARD   ("/media/sdcard/")
/*-----------------------------------*/
#define  MEM_DEV	 "/dev/mem"
/*-----------------------------------*/
#define  SENSOR_MAX_NUM		(8)
/*-----------------------------------*/

#endif
