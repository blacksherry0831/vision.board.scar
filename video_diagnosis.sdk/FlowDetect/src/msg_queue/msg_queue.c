#include "msg_queue.h"
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
#if 1
mqd_t m_mqfd_img_buffer=-1;
#endif
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
int open_queue(const char *_name,int _maxmsg,int _msgsize)
{

	mqd_t mqfd;

	struct mq_attr attr;
	int open_flags  = 0;

	/* Fill in attributes for message queue */
	 attr.mq_maxmsg  = 2;
	 attr.mq_msgsize  = 104;
	 attr.mq_flags  = 0;

	/* Set the flags for the open of the queue.
	 * Make it a blocking open on the queue, meaning it will block if
	 * this process tries to send to the queue and the queue is full.
	 * (Absence of O_NONBLOCK flag implies that the open is blocking)
	 *
	 * Specify O_CREAT so that the file will get created if it does not
	 * already exist.
	 *
	 * Specify O_WRONLY since we are only planning to write to the queue,
	 * although we could specify O_RDWR also.
	 */
	 open_flags = O_WRONLY|O_CREAT;

	/* Open the queue, and create it if the receiving process hasn't
	 * already created it.
	 */
	 mqfd = mq_open(_name,open_flags,PMODE,&attr);
	if (mqfd == -1)
	{
		int errsv = errno;
		perror("mq_open failure from main");
		exit(0);



	}else{


	}

	return mqfd;

}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
int open_queueN(const char*_name)
{
	return open_queue(_name,3000,1024);
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
int open_queue_img_buff()
{
	m_mqfd_img_buffer=open_queue("/mq_image_buffer" ,3000,1024);
	return m_mqfd_img_buffer;
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
void destory_queue_img_buff()
{
	close_queue(m_mqfd_img_buffer);
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
int send_queue_img_buff(void * _data)
{
	uintptr_t ptr_t = (uintptr_t)_data;
	return	send_queue_mq(m_mqfd_img_buffer,(char*) &ptr_t,sizeof(uintptr_t));
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
void * rcv_queue_imag_buff()
{

		char msg_buffer[1024];

		int num_bytes_received = mq_receive(m_mqfd_img_buffer,msg_buffer,1024,0);


		if (num_bytes_received == -1){
			perror("mq_receive failure on mqfd\n");

		}else if(num_bytes_received==sizeof(void *)){
			PRINTF_DBG_EX("data read \n");

			uintptr_t* ptr_pt=(uintptr_t*)msg_buffer;
			uintptr_t ptr_t=*ptr_pt;

			uintptr_t* ptr_pt_buff=(uintptr_t*)ptr_t;

			return ptr_pt_buff;


		}else{
			PRINTF_DBG_EX("data read error \n");
		}

		return NULL;
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/

/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
int send_queue_mq(mqd_t mqfd,const char* msg_buffer,int num_bytes_to_send)
{

	const int priority_of_msg=1;

	if (mqfd == -1)
	{
		perror("mq_open failure from main");
		exit(0);
	}

	int status  = mq_send(mqfd,msg_buffer,num_bytes_to_send,priority_of_msg);

	if (status == -1){
			perror("mq_send failure on mqfd");
	}else{
			PRINTF_DBG_EX("successful call to mq_send");
	}




	return status;

}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
int send_queue(const char*_name,const char* msg_buffer,int num_bytes_to_send)
{
	const int priority_of_msg=1;
	mqd_t mqfd=open_queueN(_name);

	if (mqfd == -1)
	{
		perror("mq_open failure from main");
		exit(0);
	}

	int status  = mq_send(mqfd,msg_buffer,num_bytes_to_send,priority_of_msg);

	if (status == -1){
			perror("mq_send failure on mqfd");
	}else{
			PRINTF_DBG_EX("successful call to mq_send");
	}




	return status;
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
int recv_queue(const char*_name)
{
	const int priority_of_msg=1;
	char msg_buffer[1024];
	mqd_t mqfd=open_queueN(_name);

		if (mqfd == -1)
		{
			perror("mq_open failure from main");
			exit(0);
		}

		int num_bytes_received = mq_receive(mqfd,msg_buffer,1024,0);


		if (num_bytes_received == -1){
			perror("mq_receive failure on mqfd");
		}else{
			PRINTF_DBG_EX("data read ");
		}






		return num_bytes_received;
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
int close_queue(mqd_t mqfd)
{
	/* Done with queue, so close it */
	if (mq_close(mqfd) == -1)
	perror("mq_close failure on mqfd");

}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
