#pragma once
#ifndef _MSG_QUEUE_H_
#define _MSG_QUEUE_H_
/*-----------------------------------*/
#include<stdio.h>
#include <stdlib.h>
/*-----------------------------------*/
#include "linux_header.h"
#include "def.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#include "msg_queue/msg_sysV_q.h"
#include "sync/sync_global.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
class MsgQueue
{
public:
	MsgQueue(const int _qKey,const int _bId);
	~MsgQueue();
private:
	key_t 	mQueueKey;
	int 	mQueueId;
	int 	mBuffId;
private:
	void init();
	void destory();
public:
	int  snd_queue_buff(void * _data);
	MESSAGE  rcv_queue_buff();
};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#endif
