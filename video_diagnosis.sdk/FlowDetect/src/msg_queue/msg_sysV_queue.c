#include "msg_sysV_queue.h"
#include<stdio.h>
#include <stdlib.h>
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

	MESSAGE temp;
	temp.message_type = msg.message_type;
	temp._data = msg._data;

	if(temp.message_type==ENOMSG){  //若 消息队列中无消息可读

	}else{
		CMD_CTRL *img_t = (CMD_CTRL *)temp._data;

		if(IsCmdCtrlHeader(img_t)){  //验证 cmd的头

			if(IsImageFrame(img_t)){  //若为img命令

				IplImageU* imgU=GetIplImageUx(img_t);
				IplImage* imgcv=GetIplImage(img_t);

				if(get_flame_monitor_flag())
				{
					IplImage* img_temp = cvCreateImageHeader(cvSize(1, 1), 8, 1);   //创建图像头
					cvInitImageHeader(img_temp,cvSize(imgcv->width,imgcv->height), 8, 1, 0, 4);  //初始化图片头
					cvSetData(img_temp,imgcv->imageData, img_temp->widthStep);   //连接图片实体数据
					if(!img_temp)
						printf("Could not load image file!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
					//IplImage* dstImg=cvCreateImage(cvGetSize(img_temp), IPL_DEPTH_8U,1);
					//cvThreshold(img_temp, dstImg, 0, 255, CV_THRESH_BINARY);
					int nonZerosNum = cvCountNonZero(img_temp);
					//cvSaveImage("/home/root/res.png",dstImg);

					CvFont font;
					cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1, 1, 1, 2, 8);
					char strDst[256] = {0};
					sprintf(strDst,"%d",nonZerosNum);
					cvPutText(img_temp, strDst,cvPoint(imgcv->width-200, imgcv->height-200),&font,CV_RGB(240,240,240));

					if(get_cnt_i() == 0)  //没有火焰
					{
						if(nonZerosNum > get_thresholde_area())
						{
							inc_cnt_i();
							set_current_flame(nonZerosNum);
						}

						cvRectangle( img_temp, cvPoint(imgcv->width-10, imgcv->height-10), cvPoint(imgcv->width-150, imgcv->height-150), cvScalar(250, 250, 250), 3, 4, 0 );

					}
					else
					{
						inc_cnt_i();
						set_last_flame(get_current_flame());
						set_current_flame(nonZerosNum);

						if(nonZerosNum > get_thresholde_area()
								&& is_up_to_thresholde_difference())  //火焰稳定
						{
							if(get_igniter_status())  //点火器处于点火状态
							{
								//灭火
								set_fire_on(0);
								set_fire_off(1);

								//cvCircle(img_temp,cvPoint(100,100), 50,CV_RGB(250,250,250),3);
							}

							cvCircle(img_temp,cvPoint(imgcv->width-100,imgcv->height-100), 50,CV_RGB(250,250,250),3);
						}
						else  //火焰不稳定
						{
							if(!get_igniter_status())  //点火器不处于点火状态
							{
								//点火
								set_fire_off(0);
								set_fire_on(1);

								//cvLine(img_temp,cvPoint(0,0),cvPoint(150,150),CV_RGB(250,250,250),3);
								//cvLine(img_temp,cvPoint(0,150),cvPoint(150,0),CV_RGB(250,250,250),3);
							}

							cvLine(img_temp,cvPoint(imgcv->width,imgcv->height),cvPoint(imgcv->width-150,imgcv->height-150),CV_RGB(250,250,250),3);
							cvLine(img_temp,cvPoint(imgcv->width,imgcv->height-150),cvPoint(imgcv->width-150,imgcv->height),CV_RGB(250,250,250),3);
						}

						//cvCvtColor(img_temp, img_temp, CV_BGR2GRAY);//单通道转3通道
					}

					cvReleaseImageHeader(&img_temp);
					//cvReleaseImage(&dstImg);

				}

			}

			//ReleaseCmdCtrl(&img_t);  //释放cmd内存
		}
	}

	return msg;
}

/*-----------------------------------*/
 /* *
  *rcv_queue_img_buff(从图片消息队列中，读取第一个图片数据) 的封装  无上位机
 */
/*-----------------------------------*/
MESSAGE  rcv_queue_img_buff_ex_inner()
{
	MESSAGE msg = rcv_queue_img_buff();  //从_msgid消息队列中读取（第一个 _type=0）消息

	MESSAGE temp;
	temp.message_type = msg.message_type;
	temp._data = msg._data;

	if(temp.message_type==ENOMSG){  //若 消息队列中无消息可读

	}else{
		CMD_CTRL *img_t = (CMD_CTRL *)temp._data;

		if(IsCmdCtrlHeader(img_t)){  //验证 cmd的头

			if(IsImageFrame(img_t)){  //若为img命令

				IplImageU* imgU=GetIplImageUx(img_t);
				IplImage* imgcv=GetIplImage(img_t);

				if(get_flame_monitor_flag())
				{
					IplImage* img_temp = cvCreateImageHeader(cvSize(1, 1), 8, 1);   //创建图像头
					cvInitImageHeader(img_temp,cvSize(imgcv->width,imgcv->height), 8, 1, 0, 4);  //初始化图片头
					cvSetData(img_temp,imgcv->imageData, img_temp->widthStep);   //连接图片实体数据
					if(!img_temp)
						printf("Could not load image file!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

					int nonZerosNum = cvCountNonZero(img_temp);

					if(get_cnt_i() == 0)  //没有火焰
					{
						if(nonZerosNum > get_thresholde_area())
						{
							inc_cnt_i();
							set_current_flame(nonZerosNum);
						}
					}
					else
					{
						inc_cnt_i();
						set_last_flame(get_current_flame());
						set_current_flame(nonZerosNum);

						if(nonZerosNum > get_thresholde_area()
								&& is_up_to_thresholde_difference())  //火焰稳定
						{
							if(get_igniter_status())  //点火器处于点火状态
							{
								//灭火
								set_fire_on(0);
								set_fire_off(1);
							}
						}
						else  //火焰不稳定
						{
							if(!get_igniter_status())  //点火器不处于点火状态
							{
								//点火
								set_fire_off(0);
								set_fire_on(1);
							}
						}
					}
					cvReleaseImageHeader(&img_temp);
				}
			}
		}
	}

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
