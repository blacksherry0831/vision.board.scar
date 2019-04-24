#ifndef INIT_DESTORY_H
#define INIT_DESTORY_H

#include "linux_header.h"
#include "def.h"
#include "axi.h"
#include "tcp_server.h"
#include "task_flow.h"
#include "axi/axi_fpga_ctrl.h"

#include "uCOS/mem_pool_fixed.h"

#include "life_cycle.h"


void init();


void destory();

void setProjectMode(const struct cmd_param _cmd_param);

int main_ring();

void run_main();


#endif
