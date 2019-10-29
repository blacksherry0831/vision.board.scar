#ifndef  THREAD_MEM_CPY_H
#define  THREAD_MEM_CPY_H
/*-----------------------------------*/
#include "../linux_header.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/axi_base.h"
#include "module_zynq7000_hi3516/def_hw_zynq7000_hi3516_PL_MEM.h"
#include "task/task_sync.h"
/*-----------------------------------*/
#include "sync_dma.h"
/*-----------------------------------*/
pthread_t init_memcpy_server(void *_data);
#endif
