#ifndef DEF_H
#define DEF_H

#include "outside_process.h"
/////////////////////////////////////////////////////
#ifndef FALSE
#define FALSE 		(0)
#endif
#ifndef TRUE
#define TRUE 		(1)
#endif

#ifndef SUCCESS
#define SUCCESS		(0)
#endif
/////////////////////////////////////////////////////
//GP1地址声明4K范围
/////////////////////////////////////////////////////
#define			UART0_RSTADDR 			(0x010)//初始化
#define			UART0_RATEADDR 			(0x012)//波特率
#define			UART0_RDENADDR			(0x014)//读使能
#define			UART0_RDATAADDR			(0x015)//取数据
#define			UART0_WDATAADDR			(0x016)//写数据
#define			UART0_STATUSADDR		(0x01F)//数据缓存状态
#define			UART_SIZEADDR 			(0x010)//UART数据地址分区大小
//uart0~7...

#define TIME_START()  do{struct timeval startTime,endTime;float Timeuse;gettimeofday(&startTime,NULL);

#define TIME_END(X)		gettimeofday(&endTime,NULL);Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);	printf("%s = %f us,%f ms\n",X,Timeuse,Timeuse/1000);}while(0)

/////////////////////////////////////////////////////
//GP1地址声明4k范围END
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
//GP0地址声明1G范围	(0x4-0x8)
/////////////////////////////////////////////////////
#define			DDR3_ADDR       		(0x60000000)
//PL DDR3
#define  MEM_DEV "/dev/mem"
/////////////////////////////////////////////////////
//GP0地址声明4-8范围END
/////////////////////////////////////////////////////



#define TCP_PROTOCOL 0
#define UDP_PROTOCOL 1
#define IP_PROTOCOL 2
#define			DDR3_ADDR       		(0x60000000)
#define FILESIZE 1<<20


/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#define TCP_PORT_VIDEO_TRANS (10001)
#define TCP_POET_CMD_CTRL    (10000)
#define TCP_PORT_VIDEO_RAW	 (8888)
#define TCP_PORT_TELNET	 	 (8889)
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#define ALIGN_SIZE_T (8)
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#define RCV_IMAGE_BY_SELF (0)
#define RCV_IMAGE_BY_TCP  (1)
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#define _DEBUG TRUE
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

#endif
