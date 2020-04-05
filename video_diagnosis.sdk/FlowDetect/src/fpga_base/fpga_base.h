#ifndef FPGA_BASE_H
#define FPGA_BASE_H
/*-----------------------------------*/
#include "linux_header.h"
/*-----------------------------------*/
#include "def.h"
#include "modules_ex/type.h"
/*-----------------------------------*/

#include "module_zynq7000_hi3516/axi_fpga_ctrl_img.h"
#include "module_zynq7000_hi3516/def_hw_zynq7000_hi3516_PL_MEM.h"
#include "module_zynq7000_hi3516/axi_fpga_ctrl_img_scar.h"
#include "img_cfg/img_cfg.h"
#include "task/task_circle.h"
#include "status.h"
/*-----------------------------------*/
enum FPGA_STATUS{
	FPGA_NO_ERR		=0x0000,
	FPGA_ERR_SENSOR	=0x0001,
	FPGA_ERR_BUSY	=0x0002,
	FPGA_ERR_OTHER	=0x8000,
};
/*-----------------------------------*/
unsigned int GetFpgaError();
unsigned int SetFpgaError(const unsigned int _err,const unsigned int _sensor);
/*-----------------------------------*/
int wait4FpgaConvertDone();
/*-----------------------------------*/

#endif
