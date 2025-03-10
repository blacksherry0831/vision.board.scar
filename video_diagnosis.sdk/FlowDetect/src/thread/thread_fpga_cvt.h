#ifndef THREAD_FPGA_CVT_H
#define THREAD_FPGA_CVT_H
/*-----------------------------------*/
#include "linux_c_def.h"
/*-----------------------------------*/
#include "sync/sync_pl_mem_4_8_lock.h"
/*-----------------------------------*/
#include "modules/printf_log/printf_log.h"

#include "sync/sync_global.h"
#include "module_zynq7000_hi3516/axi_base.h"
#include "thread_module/fpga_cvt_module.h"
#include "thread_module/fpga_cvt_scar_module.h"

/*-----------------------------------*/
pthread_t init_fpga_cvt_server(void *_data);
/*-----------------------------------*/
#endif
