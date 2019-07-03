#ifndef  THREAD_MEM_CPY_H
#define  THREAD_MEM_CPY_H
/*-----------------------------------*/
#include "../linux_header.h"

/*-----------------------------------*/
#include "module_zynq7000_hi3516/axi_base.h"
#include "module_zynq7000_hi3516/dma.h"
#include "task/task_sync.h"
/*-----------------------------------*/
pthread_t init_memcpy_server(void *_data);
#endif
