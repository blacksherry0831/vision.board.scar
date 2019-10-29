#ifndef AXI_FPGA_CTRL_H
#define AXI_FPGA_CTRL_H
/*-----------------------------------*/
#include "linux_header.h"
#include "linux_c_def.h"
/*-----------------------------------*/
#include "def_hw_zynq7000_hi3516.h"
/*-----------------------------------*/
#include "hw_module_base/axi_api.h"
/*-----------------------------------*/
int FPGA_CTRL_mmap();
void FPGA_CTRL_unmmap();
/*-----------------------------------*/
int FPGA_CTRL_send(int addr, int* pidata);
int FPGA_CTRL_send_int(int _addr,const  int _data);
int FPGA_CTRL_send_int_1_0(int _addr);
int FPGA_CTRL_read(int addr, int* pidata);
int FPGA_CTRL_send_unit(int addr,unsigned int* pidata);
/*-----------------------------------*/
#endif
