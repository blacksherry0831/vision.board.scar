#include "MsgQueue.h"
/*-----------------------------------*/
 /**
  *
 */
/*-----------------------------------*/
MsgQueue::MsgQueue(const int _qKey,const int _bId)
{
	this->mQueueKey=_qKey;
	this->mBuffId=_bId;
	this->init();
}
/*-----------------------------------*/
 /**
  *
 */
/*-----------------------------------*/
MsgQueue::~MsgQueue()
{
	this->destory();
}
/*-----------------------------------*/
 /**
  *
 */
/*-----------------------------------*/
void MsgQueue::init()
{
	this->mQueueId=get_queue(mQueueKey);
}
/*-----------------------------------*/
 /**
  *
 */
/*-----------------------------------*/
void MsgQueue::destory()
{
	remove_queue(mQueueId);
}
/*-----------------------------------*/
 /**
  *
 */
/*-----------------------------------*/
int  MsgQueue::snd_queue_buff(void * _data)
{
	return 	snd_queue(mQueueId,mBuffId,_data);
}
/*-----------------------------------*/
 /**
  *
 */
/*-----------------------------------*/
MESSAGE  MsgQueue::rcv_queue_buff()
{
	MESSAGE msg = rcv_queue(mQueueId,mBuffId);  //��_msgid��Ϣ�����ж�ȡ����һ�� _type=0����Ϣ

	return msg;
}