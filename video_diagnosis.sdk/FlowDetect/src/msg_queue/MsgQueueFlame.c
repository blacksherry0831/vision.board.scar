#include "MsgQueueFlame.h"
/*-----------------------------------*/
 /**
  *
 */
/*-----------------------------------*/

MsgQueueFlame::MsgQueueFlame(const int _qKey,const int _bId) :MsgQueue(_qKey,_bId)
{

}
/*-----------------------------------*/
 /**
  *
 */
/*-----------------------------------*/
int  MsgQueueFlame::snd_queue_flame(const int _on,const int _off)
{
	int*	data_t=new int[3];

	data_t[0]=0X55AA55AA;
	data_t[1]=_on;
	data_t[2]=_off;

	return 	this->snd_queue_buff(data_t);
}
/*-----------------------------------*/
 /**
  *
 */
/*-----------------------------------*/
int  MsgQueueFlame::rcv_queue_flame(int* _on,int* _off)
{

	MESSAGE msg=this->rcv_queue_buff();

	if(msg.message_type==ENOMSG){  //若 消息队列中无消息可读
			return 0;
	}else{

		  int*	data_t=(int*)(msg._data);

		  if(data_t[0]==0X55AA55AA){

			  	  	  *_on=data_t[1];
			  		  *_off=data_t[2];
			  		  delete []data_t;
			  		  return 1;

		  }
	}

	return 0;

}
/*-----------------------------------*/
 /**
  *
 */
/*-----------------------------------*/
void   MsgQueueFlame::release_queue_flame()
{
		int on,off;
		this->rcv_queue_flame(&on,&off);
}
/*-----------------------------------*/
 /**
  *
 */
/*-----------------------------------*/
