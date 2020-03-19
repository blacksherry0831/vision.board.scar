#ifndef INIT_DESTORY_H
#define INIT_DESTORY_H
/*-----------------------------------*/
#include "linux_header.h"
#include "def.h"

#include "cfg.h"
#include "status.h"
/*-----------------------------------*/


#include "modules/uCOS/mem_pool_fixed.h"

#include "modules_58/life_cycle.h"

#include "module_zynq7000_hi3516/dma_83c0.h"
/*-----------------------------------*/
#include "thread/thread_work_img_trans_inner.h"

#include "module_zynq7000_hi3516/axi_fpga_ctrl.h"
#include "module_zynq7000_hi3516/dma_83c1.h"
#include "sync/sem_sync.h"
#include "thread/thread_work_img_trans.h"
#include "thread/thread_work_ctrl.h"
#include "thread/thread_fpga_cvt.h"
#include "thread/thread_dma_cpy.h"
#include "thread/thread_mem_cpy.h"

/*-----------------------------------*/
void init();


void destory();

void setProjectMode(const struct cmd_param _cmd_param);

int main_ring();

void run_main();


#endif
