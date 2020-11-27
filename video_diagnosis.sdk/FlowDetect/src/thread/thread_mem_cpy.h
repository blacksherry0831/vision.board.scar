#ifndef  THREAD_MEM_CPY_H
#define  THREAD_MEM_CPY_H
/*-----------------------------------*/
#include "../linux_header.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/axi_base.h"
#include "module_zynq7000_hi3516/def_hw_zynq7000_hi3516_PL_MEM.h"
#include "module_zynq7000_hi3516/dma_83c0_ex.h"
#include "msg_queue/msg_sysV_queue.h"
/*-----------------------------------*/

/*-----------------------------------*/
#include "sync/sync_global.h"
#include "sync/sem_sync.h"
#include "sync/sync_ps_mem_0_4_lock.h"
#include "sync/sync_task.h"
/*-----------------------------------*/
#include "img_cfg/img_cfg.h"
/*-----------------------------------*/
#include "status.h"
/*-----------------------------------*/
#include "fpga_base/fpga_base.h"
/*-----------------------------------*/
#include "thread_module/fpga_cvt_scar_module.h"
/*-----------------------------------*/
pthread_t init_memcpy_server(void *_data);
#endif
