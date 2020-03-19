#ifndef _DEF_HW_ZYNQ7000_HI3516_H
#define _DEF_HW_ZYNQ7000_HI3516_H
/*-----------------------------------*/
#include "def_hw_zynq7000_hi3516_PL_MEM.h"
#include "def_hw_zynq7000_hi3516_axi.h"
#include "def_hw_zynq7000_hi3516_dmac.h"
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
#define PATH_SDCARD   ("/media/sdcard/")
/*-----------------------------------*/
#define  MEM_DEV	 "/dev/mem"
/*-----------------------------------*/
#endif
