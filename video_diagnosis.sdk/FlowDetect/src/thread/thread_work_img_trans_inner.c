#include "thread_work_img_trans_inner.h"
/*-----------------------------------*/
/**
 *ͼƬ���ݽ����߳�-��ʼ����
 */
/*-----------------------------------*/
void *inner_transfer_image(void* _pdata)
{
	while(IsRun()){

		if(0==GetTcpTransImgThreads()){  //���޿ͻ�������

			MESSAGE msg=rcv_queue_img_buff_image_process(0);  //��ͼƬ��Ϣ�����ж�ȡͼƬ����

			if(msg.message_type==ENOMSG){  //�� ��Ϣ����������Ϣ�ɶ�
				usleep(10);
			}else{
				CMD_CTRL *img_data=(CMD_CTRL *)msg._data;

				if(IsCmdCtrlHeader(img_data)){  //��֤ cmd��ͷ

					if(IsImageFrame(img_data)){  //��Ϊimg����

						IplImageU* imgU=GetIplImageUx(img_data);
						IplImage* imgcv=GetIplImage(img_data);
						const int ch=imgU->IpAddrChannel[0];
						PRINTF_DBG_EX("inner rcv a image Channel:%d\n",ch);

					}

					ReleaseCmdCtrl(&img_data);  //�ͷ�cmd�ڴ�

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
 *ͼƬ���ݽ����̣߳����޿ͻ���������
 */
/*-----------------------------------*/
pthread_t inner_image_buff_trans_server(void *_data)
{
	pthread_t _thread_tid;
	//pthread_createΪ�½��߳� ��������Ϊ���̱߳�ʶ�����߳����ԣ��߳����к�������ʼ��ַ�����к����Ĳ���
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
