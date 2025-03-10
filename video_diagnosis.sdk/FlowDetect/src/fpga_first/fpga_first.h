#ifndef _FPGA_FIRST_H_
#define _FPGA_FIRST_H_
/*-----------------------------------*/
#include "linux_header.h"
/*-----------------------------------*/
#include "def.h"
#include "modules_ex/type.h"
/*-----------------------------------*/

#include "module_zynq7000_hi3516/axi_fpga_ctrl_img.h"
#include "module_zynq7000_hi3516/def_hw_zynq7000_hi3516_PL_MEM.h"

#include "img_cfg/img_cfg.h"

#include "status.h"

void outside_first(int DATA_MODE);

#endif
