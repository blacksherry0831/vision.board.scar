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
  *
 */
/*-----------------------------------*/
MESSAGE rcv_queue(int _msgid,int _type)
{
	MESSAGE msg={0,NULL};

	ssize_t result_t=msgrcv(_msgid, (void *)&msg, sizeof(void*),_type,

#if 1
				IPC_NOWAIT
#else
				0
#endif
			);

	if ( result_t== -1) {

		if(ENOMSG==errno){
			msg._data=NULL;
			msg.message_type=ENOMSG;
		}else if(EIDRM==errno){
			msg._data=NULL;
			msg.message_type=EIDRM;
		}else{
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
  *
 */
/*-----------------------------------*/
MESSAGE  rcv_queue_img_buff()
{
	return 	rcv_queue(m_msgid_img_buff,m_img_buff_type);
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
