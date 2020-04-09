#include "msg_sysV_queue.h"
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
int 			m_msgid_img_buff=-1;
const key_t 	m_key_img_queue=654321;
const int       m_img_buff_type=123456;
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
int msgTypeImage()
{
	return m_img_buff_type;
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
int  get_queue_img_buff()
{

	m_msgid_img_buff=get_queue(m_key_img_queue);
	return m_msgid_img_buff;
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
int  snd_queue_img_buff(void * _data)
{
	return 	snd_queue(m_msgid_img_buff,m_img_buff_type,_data);
}
/*-----------------------------------*/
 /* *
  *从图片消息队列中，读取第一个图片数据
 */
/*-----------------------------------*/
MESSAGE  rcv_queue_img_buff()
{
	MESSAGE msg = rcv_queue(m_msgid_img_buff,m_img_buff_type);  //从_msgid消息队列中读取（第一个 _type=0）消息

	return msg;
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
int remove_queue_img_buff()
{
	int result=0;

	if(m_msgid_img_buff!=-1){
		 result=msgctl(m_msgid_img_buff, IPC_RMID, NULL);
		 if(result==m_msgid_img_buff){
			 m_msgid_img_buff=-1;
			 sleep(1);
			 return 1;
		 }

	}
	return 0;
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
MESSAGE  rcv_queue_img_buff_image_process(const int _draw)
{
	const MESSAGE msg = rcv_queue_img_buff();  //从_msgid消息队列中读取（第一个 _type=0）消息

	if(msg.message_type==ENOMSG){  //若 消息队列中无消息可读

	}else{
			image_proc(msg,_draw);
	}
	return msg;
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
