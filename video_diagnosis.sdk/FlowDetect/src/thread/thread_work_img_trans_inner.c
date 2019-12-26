#include "thread_work_img_trans_inner.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void *inner_transfer_image(void* _pdata)
{
	while(IsRun()){

		if(0==GetTcpTransImgThreads()){

				MESSAGE msg=rcv_queue_img_buff();

				if(msg.message_type==ENOMSG){
					usleep(10);
				}else{

					CMD_CTRL *img_data=msg._data;
					{
							IplImageU* imgU=(IplImageU*)img_data;
							const int ch=imgU->IpAddrChannel[0];
							PRINTF_DBG_EX("inner rcv a image Channel:%d\n",ch);
					}
					ReleaseCmdCtrl(&img_data);
				}




		}else{
			sleep_1ms();
		}

	}

	pthread_exit(NULL);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
pthread_t inner_image_buff_trans_server(void *_data)
{
	pthread_t _thread_tid;
	if( pthread_create(&_thread_tid, NULL, inner_transfer_image, _data) ){
			PRINTF_DBG_EX(" Create print_thread1 thread error!\n");
			exit(0);
	}
 return _thread_tid;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
