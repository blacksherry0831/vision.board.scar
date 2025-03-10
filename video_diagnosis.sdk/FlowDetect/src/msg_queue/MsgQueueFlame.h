#pragma once
#ifndef _MSG_QUEUE_FLAME_H_
#define _MSG_QUEUE_FLAME_H_
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#include "msg_queue/MsgQueue.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
class MsgQueueFlame : public MsgQueue
{
public:
	MsgQueueFlame(const int _qKey,const int _bId);
public:
	int  snd_queue_flame(const int _on,const int _off);
	int  rcv_queue_flame(int* _on,int* _off);
	void  release_queue_flame();
	void clear_queue_flame();

	int snd_flag = 1;
};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#endif
