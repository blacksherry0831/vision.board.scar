#include "msg_sysV_q.h"
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
  *��_msgid��Ϣ�����ж�ȡ����һ�����͵���_type����Ϣ
 */
/*-----------------------------------*/
MESSAGE rcv_queue(int _msgid,int _type)
{
	MESSAGE msg={0,NULL};

	//msgrcv ����Ϣ���ж�ȡ��Ϣ�������Դ�Ϊ��Ϣ���б�ʶ���������Ϣ�Ľṹ�壬Ҫ������Ϣ�Ĵ�С�����յ�һ����Ϣ���һ������_type����Ϣ�����û�з�����������Ϣ������������
	ssize_t result_t=msgrcv(_msgid, (void *)&msg, sizeof(void*),_type,

#if 1
				IPC_NOWAIT
#else
				0
#endif
			);

	//����Ϣ���ж�ȡ��Ϣ-ʧ��
	if ( result_t== -1) {

		if(ENOMSG==errno){  //�� ��Ϣ����������Ϣ�ɶ�
			msg._data=NULL;
			msg.message_type=ENOMSG;
		}else if(EIDRM==errno){  //�� ��ʶ��Ϊmsqid����Ϣ�����ѱ�ɾ��
			msg._data=NULL;
			msg.message_type=EIDRM;
		}else{  //����δ֪����
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
int remove_queue(const int _id)
{
	int result=0;

	if(_id!=-1){
		 result=msgctl(_id, IPC_RMID, NULL);
		 if(result==_id){
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