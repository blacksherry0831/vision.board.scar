#include "thread_work_img_trans_inner.h"
/*-----------------------------------*/
/**
 *图片数据交互线程-起始函数
 */
/*-----------------------------------*/
void *inner_transfer_image(void* _pdata)
{
	while(IsRun()){

		if(0==GetTcpTransImgThreads()){  //若无客户端相连

			MESSAGE msg=rcv_queue_img_buff_image_process(0);  //从图片消息队列中读取图片数据

			if(msg.message_type==ENOMSG){  //若 消息队列中无消息可读
				usleep(10);
			}else{
				CMD_CTRL *img_data=(CMD_CTRL *)msg._data;

				if(IsCmdCtrlHeader(img_data)){  //验证 cmd的头

					if(IsImageFrame(img_data)){  //若为img命令

						IplImageU* imgU=GetIplImageUx(img_data);
						IplImage* imgcv=GetIplImage(img_data);
						const int ch=imgU->IpAddrChannel[0];
						PRINTF_DBG_EX("inner rcv a image Channel:%d\n",ch);

					}

					ReleaseCmdCtrl(&img_data);  //释放cmd内存

				}
			}
		}else{
			sleep_1ms();
		}
	}

	pthread_exit(NULL);

}
/*-----------------------------------*/
/**
 *图片数据交互线程（若无客户端相连）
 */
/*-----------------------------------*/
pthread_t inner_image_buff_trans_server(void *_data)
{
	pthread_t _thread_tid;
	//pthread_create为新建线程 参数依次为新线程标识符，线程属性，线程运行函数的起始地址，运行函数的参数
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
