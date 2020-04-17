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

		//IplImageU* imgU=GetIplImageUx(img_t);
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
			const int nonZerosNum = cvCountNonZero(img_temp);
			//cvSaveImage("/home/root/res.png",dstImg);

			if(_draw) {
				CvFont font;
				cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1, 1, 1, 2, 8);
				char strDst[256] = {0};
				sprintf(strDst,"%d",nonZerosNum);
				cvPutText(img_temp, strDst,cvPoint(imgcv->width-200, imgcv->height-200),&font,CV_RGB(240,240,240));
			}

			if(get_cnt_i() == 0)  //没有火焰
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
						&& is_up_to_thresholde_difference())  //火焰稳定
				{
					if(get_igniter_status())  //点火器处于点火状态
					{
						//灭火
						//set_fire_on(0);
						//set_fire_off(1);

						gFlameCmdQueue.snd_queue_flame(0,1);

						//if(_draw) {
						//	cvCircle(img_temp,cvPoint(100,100), 50,CV_RGB(250,250,250),3);
						//}
					}

					if(_draw) {
						cvCircle(img_temp,cvPoint(imgcv->width-100,imgcv->height-100), 50,CV_RGB(250,250,250),3);
					}
				}
				else  //火焰不稳定
				{
					if(!get_igniter_status())  //点火器不处于点火状态
					{
						//点火
						//set_fire_off(0);
						//set_fire_on(1);

						gFlameCmdQueue.snd_queue_flame(1,0);

						//if(_draw) {
						//	cvLine(img_temp,cvPoint(0,0),cvPoint(150,150),CV_RGB(250,250,250),3);
						//	cvLine(img_temp,cvPoint(0,150),cvPoint(150,0),CV_RGB(250,250,250),3);
						//}
					}

					if(_draw){
						cvLine(img_temp,cvPoint(imgcv->width,imgcv->height),cvPoint(imgcv->width-150,imgcv->height-150),CV_RGB(250,250,250),3);
						cvLine(img_temp,cvPoint(imgcv->width,imgcv->height-150),cvPoint(imgcv->width-150,imgcv->height),CV_RGB(250,250,250),3);
					}

				}

				//cvCvtColor(img_temp, img_temp, CV_BGR2GRAY);//单通道转3通道
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
	int posFlag = 0;  //正样本（有裂纹样本）标识符

	CMD_CTRL *img_cmd = (CMD_CTRL *)_msg._data;
	IplImage* imgcv=GetIplImage(img_cmd);
	IplImage* img_temp = cvCreateImageHeader(cvSize(1, 1), 8, 1);   //创建图像头
	cvInitImageHeader(img_temp,cvSize(imgcv->width,imgcv->height), 8, 1, 0, 4);  //初始化图片头
	cvSetData(img_temp,imgcv->imageData, img_temp->widthStep);   //连接图片实体数据
	if(!img_temp)
		printf("Could not load image file!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

	//查找黑皮
	IplImage* img_b = ImgProcessIpl_BlackSkin(img_temp, &posFlag);

	//二值化+去噪
	ImgProcessIpl_Base(img_temp);

	//hough+形态学分析
	ImgProcessIpl(img_temp, &posFlag);

	if (get_is_blackSkin())
	{
		if (!get_is_hough())
		{
			cvSetZero(img_temp);
		}

		cvAdd(img_b, img_temp, img_temp);
	}

	//结果判定
	ImgProcessIpl_PredictResult(posFlag);

	//一轮检测的已检测蒙板图片个数自增加1
	inc_processed_cnt();

	//判定结果展示
	if(_draw && get_is_showResult() && (get_processed_cnt() == get_number_of_mask()))
	{
		ImgProcessIpl_ShowResult(img_temp);
	}

	cvReleaseImage(&img_b);

	cvReleaseImageHeader(&img_temp);
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
			if(IsCmdCtrlHeader(img_t)){  //验证 cmd的头
				if(IsImageFrame(img_t)){  //若为img命令
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

#ifdef _DEBUG
	TIME_START();
#endif

		image_proc_project(_msg,_draw);

#ifdef _DEBUG
	TIME_END("image process : ");
#endif

	}
	else
	{
		other_cmd_proc_project(_msg,_draw);
	}
}
/*-----------------------------------*/
 /* *
  *其它（非图片）命令的处理
 */
/*-----------------------------------*/
void  other_cmd_proc_project(const MESSAGE _msg,const int _draw)
{
	if(IsProjectRun(scar_detect_01))
	{
		if(IsMessageImageDetStart(_msg))
		{
			CMD_CTRL *img_t = (CMD_CTRL *)_msg._data;
			IplImageU* imgU=GetIplImageUx(img_t);
			const int frame = UChar2Int(imgU->frame,ALIGN_SIZE_T);

			img_proc_init(frame);
		}
	}

}
/*-----------------------------------*/
 /* *
  *判断是否为检测序列开始命令
 */
/*-----------------------------------*/
int IsMessageImageDetStart(const MESSAGE _msg)
{
	CMD_CTRL *img_t = (CMD_CTRL *)_msg._data;
		if(img_t!=NULL){
			if(IsCmdCtrlHeader(img_t)){  //验证 cmd的头
				if(IsImgDetStart(img_t)){  //判断是否为检测序列开始命令
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
