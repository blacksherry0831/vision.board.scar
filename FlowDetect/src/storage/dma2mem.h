#ifndef DMA2MEM_H
#define DMA2MEM_H
/*-----------------------------------*/
#include "../linux_header.h"
#include "../def.h"
/*-----------------------------------*/
#include "../type.h"
#include "../axi_base.h"
#include "../hw_module/dma.h"
#include "../flow_ctrl/flow_sync.h"
/*-----------------------------------*/
pthread_t init_memcpy_server(void *_data);
#endif
