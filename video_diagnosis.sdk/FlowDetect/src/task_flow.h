#ifndef TASK_FLOW_H
#define TASK_FLOW_H

#include "linux_header.h"
#include "def.h"
#include "type.h"
#include "axi.h"
#include "tcp_server.h"

extern pthread_t init_task_flow(void* _data);
extern pthread_t task_flow_ctrl_server();



#endif
