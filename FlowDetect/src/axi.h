#ifndef AXI_H
#define AXI_H

#include "linux_header.h"
#include "outside_process.h"
#include "def.h"
#include "msg_sysV_queue.h"

#include "axi_map.h"

#include "type.h"

#include "tcp_server.h"

#include "axi/axi_fpga_ctrl.h"

extern int FPGA_CONVERT_DONE;
extern void AXILitetoUser(int virtual_addr,int phy_addr,unsigned char *p_ucData,int Size);
extern void UsertoAXILite(int virtual_addr,int phy_addr,unsigned char *p_ucData,int Size);
extern int AXILitemmap(int Addr);
extern void AXILiteunmmap(void);
extern void outside_read(int addr, int* pidata);
extern unsigned char* pl_ddr3_read(int addr, unsigned char *pcArray, int uiLength);
extern void pl_ddr3_write(int addr, unsigned char *pcArray, int uiLength);
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
