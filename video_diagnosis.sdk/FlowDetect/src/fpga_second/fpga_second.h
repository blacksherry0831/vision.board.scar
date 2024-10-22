#ifndef FPGA_SECOND_H
#define FPGA_SECOND_H
/*-----------------------------------*/
#include "linux_header.h"
/*-----------------------------------*/
#include "def.h"
#include "modules_ex/type.h"
/*-----------------------------------*/

#include "module_zynq7000_hi3516/axi_fpga_ctrl_img.h"
#include "module_zynq7000_hi3516/def_hw_zynq7000_hi3516_PL_MEM.h"
#include "module_zynq7000_hi3516/axi_fpga_ctrl.h"

#include "img_cfg/img_cfg.h"

#include "status.h"

#include "fpga_base/fpga_base.h"

#include "module_zynq7000_hi3516/axi_base.h"

void scar_cvt_cost_time(int _org,const int _fi);

#endif
