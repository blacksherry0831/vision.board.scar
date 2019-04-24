#ifndef AXI_MAP_H
#define AXI_MAP_H
/*-----------------------------------*/
#include "linux_header.h"
#include "outside_process.h"
#include "base.h"
#include "img_cfg/img_cfg.h"
/*-----------------------------------*/
#define  MEM_DEV "/dev/mem"
#define  AXI_MAP_FRAME(X)   (X)
#define  AXI_MAP_AVERAGE	 AXI_MAP_FRAME(-1)
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void video_map_all_ch();

int video_map_ch(unsigned char _ch,int _frame);

int video_unmap();

int memcpy_video(void * _data,int _ch,int _frame,int _size);
int memcpy_video_frame(void * _data,int _ch,int _frame,int _size);
int memcpy_video_avg(void * _data,int _ch,int _frame,int _size);

int write_tcp_direct(int socketfd,int _size);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
extern volatile unsigned char *g_virtual_addr;
extern const size_t CHANNELS;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
extern int AXILitemmap(int Addr);
extern void AXILiteunmmap(void);
extern void AXILitetoUser(int virtual_addr,int phy_addr,unsigned char *p_ucData,int Size);
extern void UsertoAXILite(int virtual_addr,int phy_addr,unsigned char *p_ucData,int Size);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

#define TRANSFER_DATA_WITH_DMA


#ifdef TRANSFER_DATA_WITH_DMA
/*********************dmac***********************/
#define PS_DDR_PHYADDR_FOR_DMA 0x1E000000
#define PS_DDR_LENGTH_FOR_DMA 0x2000000//(1920*1080)
#define PS_MALLOC_BUFFER_MAXNUM 16
#define EACH_BUFFER_SIZE_FOR_DMA 0x1000000
#define EACH_FRAME_SIZE_FOR_CAMERA (1920*1080)

/*********************dmac config***********************/
#define PL_RX_DMA_BASEADDR 0x83c00000
#define PL_RX_DMA_MMAP_LENGTH 0x1000

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

int dmac_transfer_init(void);
int dmac_addr_mmap(void);
int dmac_addr_unmap(void);

#endif
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

#endif
