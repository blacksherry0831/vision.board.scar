#include "msg_sysV_queue.h"
/*-----------------------------------*/
 /**
  *
 */
/*-----------------------------------*/

int get_queue(key_t _key)
{

	/* First, we set up the message queue. */

    int msgid = msgget(_key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    return msgid;
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
int snd_queue(int _msgid,int _type,void* _data)
{
	MESSAGE msg;
	msg.message_type=_type;
	msg._data=_data;
	 if (msgsnd(_msgid,&msg,sizeof(void*), 0) == -1) {
		            fprintf(stderr, "msg queue [snd] failed\n");
		          return 0;
	 }
	 return 1;
}
/*-----------------------------------*/
 /* *
  *从_msgid消息队列中读取（第一个类型等于_type）消息
 */
/*-----------------------------------*/
MESSAGE rcv_queue(int _msgid,int _type)
{
	MESSAGE msg={0,NULL};

	//msgrcv 从消息队列读取消息；参数以此为消息队列标识符，存放消息的结构体，要接收消息的大小，接收第一个消息或第一个等于_type的消息，如果没有返回条件的消息调用立即返回
	ssize_t result_t=msgrcv(_msgid, (void *)&msg, sizeof(void*),_type,

#if 1
				IPC_NOWAIT
#else
				0
#endif
			);

	//从消息队列读取消息-失败
	if ( result_t== -1) {

		if(ENOMSG==errno){  //若 消息队列中无消息可读
			msg._data=NULL;
			msg.message_type=ENOMSG;
		}else if(EIDRM==errno){  //若 标识符为msqid的消息队列已被删除
			msg._data=NULL;
			msg.message_type=EIDRM;
		}else{  //其它未知错误
			    fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			    exit(EXIT_FAILURE);
		}

     }
	return msg;
}



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
  *rcv_queue_img_buff(从图片消息队列中，读取第一个图片数据) 的封装
 */
/*-----------------------------------*/
MESSAGE  rcv_queue_img_buff_ex()
{
	MESSAGE msg = rcv_queue_img_buff();  //从_msgid消息队列中读取（第一个 _type=0）消息

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
