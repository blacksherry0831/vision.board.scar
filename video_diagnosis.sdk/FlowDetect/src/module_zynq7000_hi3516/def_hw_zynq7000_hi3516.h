#ifndef _DEF_HW_ZYNQ7000_HI3516_H
#define _DEF_HW_ZYNQ7000_HI3516_H
/*-----------------------------------*/
#include "def_hw_zynq7000_hi3516_PL_MEM.h"
#include "def_hw_zynq7000_hi3516_axi.h"
#include "def_hw_zynq7000_hi3516_dmac.h"
/*-----------------------------------*/
/**
 *GP1��ַ����4K��Χ
 *uart0~7...
 */
/*-----------------------------------*/
#define			UART0_RSTADDR 			(0x010)//��ʼ��
#define			UART0_RATEADDR 			(0x012)//������
#define			UART0_RDENADDR			(0x014)//��ʹ��
#define			UART0_RDATAADDR			(0x015)//ȡ����
#define			UART0_WDATAADDR			(0x016)//д����
#define			UART0_STATUSADDR		(0x01F)//���ݻ���״̬
#define			UART_SIZEADDR 			(0x010)//UART���ݵ�ַ������С
/*-----------------------------------*/
#define PATH_SDCARD   ("/media/sdcard/")
/*-----------------------------------*/
#define  MEM_DEV	 "/dev/mem"
/*-----------------------------------*/
#endif
