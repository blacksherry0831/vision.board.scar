/*
 * flame_monitor.c
 *
 *  Created on: 2020��3��17��
 *      Author: yjkj909
 */

#include "flame_sync.h"

static const key_t 	flame_queue_key=321;
static const int    flame_buff_id=123;

MsgQueueFlame gFlameCmdQueue(flame_queue_key,flame_buff_id);
