#ifndef 	TASK_FPGA_CVT_H
#define 	TASK_FPGA_CVT_H

#include "linux_header.h"

#include "def.h"

#include "msg_queue/msg_sysV_queue.h"



#include "modules_ex/type.h"

#include "modules_ex/tcp_server.h"

#include "module_zynq7000_hi3516/axi_fpga_ctrl_img.h"

#include "status.h"

#include "task_sync.h"

extern int FPGA_CONVERT_DONE;
extern void AXILitetoUser(int virtual_addr,int phy_addr,unsigned char *p_ucData,int Size);
extern void UsertoAXILite(int virtual_addr,int phy_addr,unsigned char *p_ucData,int Size);
extern int AXILitemmap(int Addr);
extern void AXILiteunmmap(void);
extern void outside_read(int addr, int* pidata);
extern void outside_test();
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
extern int init_fpga();

extern void outside_second();
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

pthread_t rcv_image_buff_axi_server(void *_data);
pthread_t tcp_image_buff_axi_server(void *_data);


void *fpga_cvt_server(void* _pdata);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

extern volatile int FPGASTEP2RUN;

#endif
