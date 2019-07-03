#include "img_cfg.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#define FILE_TYPE_TXT (".txt")
/*-----------------------------------*/
#define PATH_SDCARD   ("/media/sdcard/")
/*-----------------------------------*/
#define PATH_SDCARD_FILE(_file)	  (PATH_SDCARD##_file)
/*-----------------------------------*/
#define IMG_MASK_CH_08 	("img_mask")
#define IMG_CFG 		("img_cfg.txt")
#define IMG_CFG_SAMPLE	("img_cfg_sample.txt")
/*-----------------------------------*/
#define PATH_SDCARD_IMG_CFG   			"/media/sdcard/img_cfg.txt"
#define PATH_SDCARD_IMG_CFG_SAMPLE  	"/media/sdcard/img_cfg_sample.txt"
/*-----------------------------------*/
const char path_sdcard[]= PATH_SDCARD;
const char file_type_txt[]=FILE_TYPE_TXT;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
const size_t IMAGE_SIZE_AVG=1920*1080*8;
const size_t CHANNEL_BLOCK_SIZE=0x8000000;
const size_t CHANNELS=8;
/*-----------------------------------*/
size_t mImageWidth=1920;
size_t mImageHeight=1080;
size_t mImageSizeFrame=1920*1080;
/*-----------------------------------*/
CvRect CHANNEL_RECT_CUT[]={
		{480,270,1920/2,1080/2},
		{480,270,1920/2,1080/2},
		{480,270,1920/2,1080/2},
		{480,270,1920/2,1080/2},
		{480,270,1920/2,1080/2},
		{480,270,1920/2,1080/2},
		{480,270,1920/2,1080/2},
		{480,270,1920/2,1080/2}
};
/*-----------------------------------*/
CvRect mChannelRectOrg[]={
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}
};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CvRect GetRect(int chi)
{
	 CvRect rect_t;

	 		 if((GetFpgaCircleWorkMode()&WM_SIZE_FULL)==WM_SIZE_FULL){
	 			 rect_t=mChannelRectOrg[chi];
	 		 }else if((GetFpgaCircleWorkMode()&WM_SIZE_CUT)==WM_SIZE_CUT){
	 			 rect_t=CHANNEL_RECT_CUT[chi];
	 		 }

	 return rect_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CvRect GetRectCut(int chi)
{
	 CvRect rect_t=cvRect(0,0,0,0);


			 rect_t=CHANNEL_RECT_CUT[chi];


	 return rect_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void initRectCut()
{
	int SIZE=sizeof(CHANNEL_RECT_CUT)/sizeof(CvRect);

	int recti=0;

	for(recti=0;recti<SIZE;recti++){

		CHANNEL_RECT_CUT[recti]=mChannelRectOrg[recti];
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CMD_CTRL* CreateImageCtrlLocal(int _ch,int _frame, int _seq)
{
	 CvRect rect_t=  GetRect(_ch);
	 return	CreateImageCtrl(_ch,_frame,rect_t.width,rect_t.height,1,_seq);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void  MallocImageBuff(CMD_CTRL** _buff,const int _frame,const int _Chs)
{
	int chi=0;
	const int seq_t=GetFrameCircleSeq();

	for(chi=0;chi<_Chs;chi++){

		if(GetGlobalChannelMask(chi)){
		 	  _buff[chi]=CreateImageCtrlLocal(chi,_frame,seq_t);
		}
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void copyimage_cut(const unsigned char* _src,
		unsigned int _src_w,
		unsigned int _src_h,
		unsigned char* _dst,
		CvRect rect)
{

	int hi=0;
	const int hi_min=rect.y;
	const int hi_max=rect.y+rect.height;

	for(hi=hi_min;hi<hi_max;hi++){

		const int idx_src=rect.x+hi*_src_w;
		const int idx_dst=(hi-rect.y)*rect.width;

		const unsigned char *buff_row_src=&_src[idx_src];
		unsigned char *buff_row_dst=&_dst[idx_dst];

		memcpy(buff_row_dst,buff_row_src,rect.width);
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void copyimage_cut_m2(const unsigned char* _src,unsigned int _src_w,unsigned int _src_h,unsigned char* _dst,CvRect rect)
{
	int swi=0;
	int shi=0;


	for(swi=0;swi<rect.width;swi++){
		for(shi=0;shi<rect.height;shi++){

			const int idx_dst=swi+shi*rect.width;
			const int idx_src=(swi+rect.x)+(shi+rect.height)*_src_w;
			_dst[idx_dst]=_src[idx_src];

		}
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void CopyImage(void* const buff_src,CMD_CTRL* img_dst,int _channel)
{
	const CvRect rect=  GetRect(_channel);
	const CvRect rect_roi=  GetRectCut(_channel);

	int image_width_current;
	int image_height_current;
	const IplImage* const img_ptr=GetIplImage(img_dst);

#if _DEBUG
	if(IsCmdCtrl(img_dst)==FALSE){
		PRINTF_DBG("copy buff_src 2 image: image ctrl is not a valid buff ");
		assert(IsCmdCtrl(img_dst));
	}
#endif

		image_width_current=image_width();
		image_height_current=image_height();
		InitImageRoiRR(img_dst,_channel,rect,rect_roi);


	const unsigned char *buff_src_p=(unsigned char *)buff_src;
	unsigned char *buff_dst_p=(unsigned char *)(img_ptr->imageData);


#if 1
	copyimage_cut(buff_src_p,image_width_current,image_height_current,buff_dst_p,rect);
#endif

#if 0
	copyimage_cut_m2(buff_src_p,image_width_current,image_height_current,buff_dst_p,rect);
#endif
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SaveRect2SDCard(const char* const path)
{
		char buff[1024];
		FILE *fp = fopen(path,"wt+");
	 	const int  CHANNEL_NUMS=sizeof(CHANNEL_RECT_CUT)/sizeof(CvRect);
	 	int chi=0;

	 	if (NULL == fp){
	 		return ;
	 	}

	 	for(chi=0;chi<CHANNEL_NUMS;chi++){

	 		CvRect rect_t=CHANNEL_RECT_CUT[chi];

	 		snprintf(buff,sizeof(buff),"%d,%d,%d,%d,%d \n",chi,rect_t.x,rect_t.y,rect_t.width,rect_t.height);
	 		fputs(buff,fp);
	 	}

	 	 fclose(fp);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void adjRect44(CvRect* rect)
{

	while(rect->x%4!=0) rect->x++;

	while(rect->width%4!=0) rect->width--;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void adjRect44Ex(CvRect* rect)
{

	int image_width_current;
	int image_height_current;

	adjRect44(rect);

			image_width_current=image_width();
			image_height_current=image_height();


	if(rect->width>image_width_current)  rect->width=image_width_current;
	if(rect->height>image_height_current) rect->height=image_height_current;



}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ReadRect4SDCard(const char* const path)
{
		char buff[1024]={0};
		int  param[10]={0};
		int  param_idx=0;
		FILE *fp = fopen(path,"r");
	 	const int  CHANNEL_NUMS=sizeof(CHANNEL_RECT_CUT)/sizeof(CvRect);
	 	int chi=0;

	 	if (NULL == fp){
	 		return ;
	 	}

	 	for(chi=0;chi<CHANNEL_NUMS;chi++){


	 		memset(buff,0,sizeof(buff));
	 		fgets(buff,sizeof(buff),fp);

	 		 char*token=strtok(buff,",");

	 		 while(token!=NULL){

	 			 param[param_idx++]= atoi(token);

				 token=strtok(NULL,",");


	 		 }

	 		 const int ch=param[0];
	 		 CvRect* rect_t=& CHANNEL_RECT_CUT[ch];
	 		 rect_t->x=param[1];
	 		 rect_t->y=param[2];
	 		 rect_t->width=param[3];
	 		 rect_t->height=param[4];

	 		 adjRect44Ex(rect_t);

	 		 if(!IsEffectiveRect(rect_t)){
	 			 PRINTF_DBG("Error Rect Setting, ch[%d] \n",chi);
	 			 pthread_exit(NULL);
	 		 }

	 		 param_idx=0;

	 	}


	 	 fclose(fp);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int create_file(const char* const path)
{
    int fd=creat(path,00777);
    return fd;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SaveRect2SDCard_Sample()
{
	const char *const path_sample=PATH_SDCARD_IMG_CFG_SAMPLE;

	SaveRect2SDCard(path_sample);
	//ClearRectCut();

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ReadRectCutArea4SDCard()
{
	const char *const path=PATH_SDCARD_IMG_CFG;

		if(access(path,F_OK)==0){
					//exist
				ReadRect4SDCard(path);
		}else{
				initRectCut();
				SaveRect2SDCard_Sample();
		}
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void init_image_cfg(const int _width,const int _height)
{

	ReadRectCutArea4SDCard();

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetRectCut(int _ch,CvRect _rect)
{

	 if(IsEffectiveRect(&_rect)){

		 adjRect44Ex(&_rect);

		 CHANNEL_RECT_CUT[_ch]=_rect;
		 SaveRect2SDCard(PATH_SDCARD_IMG_CFG);
	 }




}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetRectCutCmd(CMD_CTRL*  cmd_t)
{

	IplImageU* imgU=GetIplImageUx(cmd_t);

	int channel=UChar2Int(imgU->IpAddrChannel,8);

	int x=UChar2Int(imgU->x_roi,8);
	int y=UChar2Int(imgU->y_roi,8);
	int width=UChar2Int(imgU->width_roi,8);
	int height=UChar2Int(imgU->height_roi,8);

	width=width-width%4;

	CvRect rect_t=cvRect(x,y,width,height);

	SetRectCut(channel,rect_t);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void encodeWithState(const char* filename, const unsigned char* image, unsigned width, unsigned height) {
  unsigned error;
  unsigned char* png;
  size_t pngsize;
  LodePNGState state;

  lodepng_state_init(&state);
  /*optionally customize the state*/

  state.info_raw.colortype=LCT_GREY;

  error = lodepng_encode(&png, &pngsize, image, width, height, &state);
  if(!error) lodepng_save_file(png, pngsize, filename);

  /*if there's an error, display it*/
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

  lodepng_state_cleanup(&state);
  free(png);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int decodeWithState(const char* filename,char* dst,int _width,int _height,int _nChannels)
{
  unsigned error;
  unsigned char* image;
  unsigned width, height;
  unsigned char* png;
  size_t pngsize;
  LodePNGState state;
  int result_t=0;
  lodepng_state_init(&state);
  /*optionally customize the state*/
  state.info_raw.colortype=LCT_GREY;

  lodepng_load_file(&png, &pngsize, filename);
  error = lodepng_decode(&image, &width, &height, &state, png, pngsize);
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

  free(png);

  /*use image here*/
  /*state contains extra information about the PNG such as text chunks, ...*/
  assert(width==_width);
  assert(height==_height);
  unsigned int Size=width*height*_nChannels;
  if(error==0){

	  memcpy(dst,image,Size);
	  result_t=1;
  }

  /*free  image here*/
  lodepng_state_cleanup(&state);
  free(image);

  return  result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetMaskImageFileName(char* _filename,int _w,int _h,int _ch)
{
	sprintf(_filename,"%sw.%d.h.%d.ch.%d.mask.png",PATH_SDCARD,_w,_h,_ch);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImgMaskValid(const CMD_CTRL* const  _cmd)
{
	const int UCHAR_SIZE=8;

	const IplImageU * imgU=GetIplImageUx(_cmd);

	const int width=UChar2Int(imgU->width,UCHAR_SIZE);
	const int height=UChar2Int(imgU->height,UCHAR_SIZE);

	return (width+height)>16;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SaveImgMaskMatrix(const CMD_CTRL* const  _cmd)
{
	const int UCHAR_SIZE=8;

	const IplImageU * imgU=GetIplImageUx(_cmd);
	const IplImage* img=GetIplImage(_cmd);

	char* data_t=GetIplImageImageData(_cmd);

	const int channel=UChar2Int(imgU->IpAddrChannel,UCHAR_SIZE);

	const int width=UChar2Int(imgU->width,UCHAR_SIZE);
	const int height=UChar2Int(imgU->height,UCHAR_SIZE);

	char filename_t[1024];

	SetMaskImageFileName(filename_t,width,height,channel);

	encodeWithState(filename_t,data_t,width,height);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int ReadImgMaskMatrix(const CMD_CTRL* _cmd)
{
		const int UCHAR_SIZE=8;

		const IplImageU * imgU=GetIplImageUx(_cmd);
		const IplImage* img=GetIplImage(_cmd);

		char* data_t=GetIplImageImageData(_cmd);

		const int channel=UChar2Int(imgU->IpAddrChannel,UCHAR_SIZE);
		const int width=UChar2Int(imgU->width,UCHAR_SIZE);
		const int height=UChar2Int(imgU->height,UCHAR_SIZE);
		const int nChannels=UChar2Int(imgU->nChannels,UCHAR_SIZE);

		char filename_t[1024];

		SetMaskImageFileName(filename_t,width,height,channel);


		if(SUCCESS==is_file_exist(filename_t)){
				return decodeWithState(filename_t,data_t,width,height,nChannels);
		}else{
				return FALSE;
		}



}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void init_image_area(const int _width,const int _height)
{
	mImageWidth=_width;
	mImageHeight=_height;
    mImageSizeFrame=_width*_height;

    int CH_MAX=sizeof(mChannelRectOrg)/sizeof(CvRect);
    int chi=0;

    for(chi=0;chi<CH_MAX;chi++){
    	mChannelRectOrg[chi].x=0;
    	mChannelRectOrg[chi].y=0;

    	mChannelRectOrg[chi].height=_height;
    	mChannelRectOrg[chi].width = _width;

    }


}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int image_width()
{
	return mImageWidth;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int image_height()
{
	return mImageHeight;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int image_size_frame()
{
	return mImageWidth*mImageHeight;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SaveImgMask2SDCard(const char* const path,const int* _param,const int _size)
{
		char buff[1024];
		FILE *fp = fopen(path,"wt+");

	 	int i=0;

	 	if (NULL == fp){
	 		return ;
	 	}

	 	for(i=0;i<_size;i++){
	 		snprintf(buff,sizeof(buff),"%d,%d\n",i,_param[i]);
	 		fputs(buff,fp);
	 	}

	 	 fclose(fp);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
