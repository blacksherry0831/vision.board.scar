#ifndef INIT_DESTORY_H
#define INIT_DESTORY_H

#include "linux_header.h"
#include "def.h"

#include "cfg.h"
#include "status.h"

#include "task/task_sync.h"

#include "modules/uCOS/mem_pool_fixed.h"

#include "modules_58/life_cycle.h"

#include "module_zynq7000_hi3516/dma_83c0.h"

void init();


void destory();

void setProjectMode(const struct cmd_param _cmd_param);

int main_ring();

void run_main();


#endif
