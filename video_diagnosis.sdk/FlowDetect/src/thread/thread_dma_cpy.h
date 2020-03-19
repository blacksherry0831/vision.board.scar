#ifndef THREAD_DMA_CPY_H
#define THREAD_DMA_CPY_H
/*-----------------------------------*/
#include "module_zynq7000_hi3516/axi_base.h"
/*-----------------------------------*/
#include "sync/sync_ps_mem_0_4_lock.h"
#include "sync/sync_pl_mem_4_8_lock.h"

#include "sync/sync_global.h"
#include "sync/sem_sync.h"
#include "module_zynq7000_hi3516/dma_83c0_ex.h"
/*-----------------------------------*/
pthread_t init_dma_server(void *_data);
/*-----------------------------------*/
#endif
