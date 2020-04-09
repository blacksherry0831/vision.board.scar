#include "image_process.h"
/*-----------------------------------*/
extern MsgQueueFlame gFlameCmdQueue;
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
void  flame_monitor_proc(const MESSAGE _msg,const int _draw)
{
		CMD_CTRL *img_t = (CMD_CTRL *)_msg._data;

		IplImageU* imgU=GetIplImageUx(img_t);
		IplImage* imgcv=GetIplImage(img_t);

		if(get_flame_monitor_flag())
		{
			IplImage* img_temp = cvCreateImageHeader(cvSize(1, 1), 8, 1);   //����ͼ��ͷ
			cvInitImageHeader(img_temp,cvSize(imgcv->width,imgcv->height), 8, 1, 0, 4);  //��ʼ��ͼƬͷ
			cvSetData(img_temp,imgcv->imageData, img_temp->widthStep);   //����ͼƬʵ������
			if(!img_temp)
				printf("Could not load image file!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
			//IplImage* dstImg=cvCreateImage(cvGetSize(img_temp), IPL_DEPTH_8U,1);
			//cvThreshold(img_temp, dstImg, 0, 255, CV_THRESH_BINARY);
			const int nonZerosNum = cvCountNonZero(img_temp);
			//cvSaveImage("/home/root/res.png",dstImg);

			if(_draw) {
				CvFont font;
				cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1, 1, 1, 2, 8);
				char strDst[256] = {0};
				sprintf(strDst,"%d",nonZerosNum);
				cvPutText(img_temp, strDst,cvPoint(imgcv->width-200, imgcv->height-200),&font,CV_RGB(240,240,240));
			}

			if(get_cnt_i() == 0)  //û�л���
			{
				if(nonZerosNum > get_thresholde_area())
				{
					inc_cnt_i();
					set_current_flame(nonZerosNum);
				}
				if(_draw) {
					cvRectangle( img_temp, cvPoint(imgcv->width-10, imgcv->height-10), cvPoint(imgcv->width-150, imgcv->height-150), cvScalar(250, 250, 250), 3, 4, 0 );
				}
			}
			else
			{
				inc_cnt_i();
				set_last_flame(get_current_flame());
				set_current_flame(nonZerosNum);

				if(nonZerosNum > get_thresholde_area()
						&& is_up_to_thresholde_difference())  //�����ȶ�
				{
					if(get_igniter_status())  //��������ڵ��״̬
					{
						//���
						//set_fire_on(0);
						//set_fire_off(1);

						gFlameCmdQueue.snd_queue_flame(0,1);

						//cvCircle(img_temp,cvPoint(100,100), 50,CV_RGB(250,250,250),3);
					}

					if(_draw) {
						cvCircle(img_temp,cvPoint(imgcv->width-100,imgcv->height-100), 50,CV_RGB(250,250,250),3);
					}
				}
				else  //���治�ȶ�
				{
					if(!get_igniter_status())  //����������ڵ��״̬
					{
						//���
						//set_fire_off(0);
						//set_fire_on(1);

						gFlameCmdQueue.snd_queue_flame(1,0);

						//cvLine(img_temp,cvPoint(0,0),cvPoint(150,150),CV_RGB(250,250,250),3);
						//cvLine(img_temp,cvPoint(0,150),cvPoint(150,0),CV_RGB(250,250,250),3);
					}

					if(_draw){
						cvLine(img_temp,cvPoint(imgcv->width,imgcv->height),cvPoint(imgcv->width-150,imgcv->height-150),CV_RGB(250,250,250),3);
						cvLine(img_temp,cvPoint(imgcv->width,imgcv->height-150),cvPoint(imgcv->width-150,imgcv->height),CV_RGB(250,250,250),3);
					}

				}

				//cvCvtColor(img_temp, img_temp, CV_BGR2GRAY);//��ͨ��ת3ͨ��
			}

			cvReleaseImageHeader(&img_temp);
			//cvReleaseImage(&dstImg);

		}



}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
void  scar_detect_01_proc(const MESSAGE _msg,const int _draw)
{

}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
int IsMessageImageFrame(const MESSAGE _msg)
{
	CMD_CTRL *img_t = (CMD_CTRL *)_msg._data;
		if(img_t!=NULL){
			if(IsCmdCtrlHeader(img_t)){  //��֤ cmd��ͷ
				if(IsImageFrame(img_t)){  //��Ϊimg����
					return TRUE;
				}
			}
		}
		return FALSE;
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
void  image_proc_project(const MESSAGE _msg,const int _draw)
{

	if(IsProjectRun(flame_monitor)){
			 flame_monitor_proc(_msg,_draw);
	}else if(IsProjectRun(scar_detect_01)){
			scar_detect_01_proc(_msg,_draw);
	}else{
			assert(0);
	}

}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
void  image_proc(const MESSAGE _msg,const int _draw)
{
	if(IsMessageImageFrame(_msg)){
		image_proc_project(_msg,_draw);
	}
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
