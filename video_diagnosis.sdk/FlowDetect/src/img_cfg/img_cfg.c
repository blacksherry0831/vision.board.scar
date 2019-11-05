#include "img_cfg.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#define FILE_TYPE_TXT (".txt")
/*-----------------------------------*/

/*-----------------------------------*/
#define PATH_SDCARD_FILE(_file)	  (PATH_SDCARD##_file)
/*-----------------------------------*/
#define IMG_MASK_CH_08 	("img_mask")
/*-----------------------------------*/
#define IMG_CFG 		("img_cfg.txt")
#define IMG_CFG_SAMPLE	("img_cfg_sample.txt")
/*-----------------------------------*/
#define IMG_CFG_JSON_DEFAULT	("img.cfg.json.default.txt")
#define IMG_CFG_JSON			("img.cfg.json.txt")
/*-----------------------------------*/
#define PATH_SDCARD_IMG_CFG   			"/media/sdcard/img_cfg.txt"
#define PATH_SDCARD_IMG_CFG_SAMPLE  	"/media/sdcard/img_cfg_sample.txt"
/*-----------------------------------*/
const char path_sdcard[]= PATH_SDCARD;
const char file_type_txt[]=FILE_TYPE_TXT;
/*-----------------------------------*/
const char* KEY_PROJECT			=	"project";
const char* KEY_SIGMA_UP		=	"sigma.up";
const char* KEY_SIGMA_DOWN		=	"sigma.down";
/*-----------------------------------*/
const char* KEY_SCAR_IMG_CFG	=	"scar.img.cfg";
/*-----------------------------------*/
const char* KEY_SCAR_IMG_CFG_WORK_MODE		=	"work.mode";
const char* KEY_SCAR_IMG_CFG_TH_GLOBAL_UP	=	"global.up";
const char* KEY_SCAR_IMG_CFG_TH_GLOBAL_DOWN	=	"global.down";
const char* KEY_SCAR_IMG_CFG_TH_ROW_UP		=	"row.up";
const char* KEY_SCAR_IMG_CFG_TH_ROW_DOWN	=	"row.down";
const char* KEY_SCAR_IMG_CFG_TH_COL_UP		=	"col.up";
const char* KEY_SCAR_IMG_CFG_TH_COL_DOWN	=	"col.down";
/*-----------------------------------*/
const char* KEY_SPACE_USED_CFG	=	"space_used_config";
const char* NOTE_SPACE_USED_CFG	=	"this is fpga && dma  && image cfg";
/*-----------------------------------*/
const char* KEY_SPACE_USED_CHANNELS	=	"space_used_channels";
/*-----------------------------------*/
const char* KEY_SPACE_CH		=	"SpaceCh";
const char* KEY_SPACE_FRAME		=	"SpaceFrame";
const char* KEY_SPACE_USED		=	"SpaceUsed";
const char* KEY_VIEW_CH			=	"ViewCh";
const char* KEY_VIEW_OUTPUT		=	"ViewOutput";
const char* KEY_N_CHANNELS		=	"nChannels";
/*-----------------------------------*/
const char* KEY_CUT_SIZE_X			=	"CutSize_x";
const char* KEY_CUT_SIZE_Y			=	"CutSize_y";
const char* KEY_CUT_SIZE_WIDTH		=	"CutSize_width";
const char* KEY_CUT_SIZE_HEIGHT		=	"CutSize_height";
/*-----------------------------------*/
const char* KEY_ORG_SIZE_WIDTH		=	"OrgSize_width";
const char* KEY_ORG_SIZE_HEIGHT		=	"OrgSize_height";
/*-----------------------------------*/
const char* KEY_COLOR_MODE			=	"colorMode";
/*-----------------------------------*/
const char* COLOR_GRAY_AVG			=	"gray.avg";
const char* COLOR_GRAY				=	"gray";
const char* COLOR_YUV				=	"yuv";
/*-----------------------------------*/
const char*	COLOR_B					=	"b";
const char* COLOR_G					=	"g";
const char* COLOR_R					=	"r";
/*-----------------------------------*/
const char* COLOR_LAB_L				=	"lab_l";
const char* COLOR_LAB_theta			=	"lab_theta";
const char* COLOR_LAB_m				=	"m";
/*-----------------------------------*/
static struct ViewInfo  G_View[SPACE_CHANNEL_NUM][SPACE_FRAME_NUM];
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void image_View_output(int _space_ch,int _space_frame)
{
	G_View[_space_ch][_space_frame].ViewOutput=TRUE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CvRect image_size_org(int _space_ch,int _space_frame)
{
	return G_View[_space_ch][_space_frame].OrgSize;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CvRect image_size_cut(int _space_ch,int _space_frame)
{
	return G_View[_space_ch][_space_frame].CutSize;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ClearViewInfo()
{
	memset(G_View,0,sizeof(G_View));

	int schi=0;
	int sfri=0;

	for(schi=0; schi <SPACE_CHANNEL_NUM;schi++){
		for(sfri=0;sfri<SPACE_FRAME_NUM;sfri++){

				G_View[schi][sfri].SpaceCh=schi;
				G_View[schi][sfri].SpaceFrame=sfri;

				G_View[schi][sfri].ViewCh=-1;
				G_View[schi][sfri].ImageMask=-1;
				strcpy(G_View[schi][sfri].colorModel,COLOR_GRAY);
		}
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void initViewInfo_1_sensor_default_intrinsics_distortion(
		const int _si,
		const int _fi)

{
		G_View[_si][_fi].Distortion[0][0]=-3.65634471e-01;
		G_View[_si][_fi].Distortion[1][0]= 1.40376598e-01;
		G_View[_si][_fi].Distortion[2][0]=-2.57731555e-03;
		G_View[_si][_fi].Distortion[3][0]=-2.75499711e-04;
		G_View[_si][_fi].Distortion[4][0]=0;

		G_View[_si][_fi].Intrinsics[0][0]=1.54510645e+03;
		G_View[_si][_fi].Intrinsics[0][2]=1.10233044e+03;
		G_View[_si][_fi].Intrinsics[1][1]=1.54874036e+03;
		G_View[_si][_fi].Intrinsics[1][2]=6.17808777e+02;
		G_View[_si][_fi].Intrinsics[2][2]=1;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void initViewInfo_1_sensor_default(const int _si,
		const int _fi,
		const int _width,
		const int _height)
{

	G_View[_si][_fi].CutSize.x=G_View[_si][_fi].CutSize.y=G_View[_si][_fi].OrgSize.x=G_View[_si][_fi].OrgSize.y=0;

	G_View[_si][_fi].CutSize.width=G_View[_si][_fi].OrgSize.width=_width;
	G_View[_si][_fi].CutSize.height=G_View[_si][_fi].OrgSize.height=_height;

	if(_fi==0){
		G_View[_si][_fi].nChannels=8;
		strcpy(G_View[_si][_fi].colorModel,COLOR_GRAY_AVG);
	}else{
		G_View[_si][_fi].nChannels=1;
		strcpy(G_View[_si][_fi].colorModel,COLOR_GRAY);
	}

	G_View[_si][_fi].SpaceCh=_si;
	G_View[_si][_fi].SpaceFrame=_fi;
	G_View[_si][_fi].SpaceUsed=TRUE;

	G_View[_si][_fi].ViewCh=_si;

	initViewInfo_1_sensor_default_intrinsics_distortion(_si,_fi);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void image_disable_output_frame()
{

		int schi=0;
		int sfri=0;

		for(schi=0; schi <SPACE_CHANNEL_NUM;schi++){
			for(sfri=0;sfri<SPACE_FRAME_NUM;sfri++){
				G_View[schi][sfri].ViewOutput=0;
			}
		}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void image_enable_output_frame(const int _space_frame)
{

		int schi=0;

		for(schi=0; schi <SPACE_CHANNEL_NUM;schi++){

			if(G_View[schi][_space_frame].ViewCh>=0){

				G_View[schi][_space_frame].ViewOutput=TRUE;

			}

		}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void image_enable_output_frame_only(int _space_frame)
{
	image_disable_output_frame();
	image_enable_output_frame(_space_frame);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void image_enable_output_frame_only_1()
{
	image_enable_output_frame_only(1);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void image_enable_output_frame_only_2()
{
	image_enable_output_frame_only(2);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void initViewInfo_img_basic(const int _width,const int _height)
{

	int si=0;
	const int SensorMAX=SENSOR_MAX_NUM;


	for(si=0;si<SensorMAX;si++){

		if(GetGlobalSensorMask(si)){

			initViewInfo_1_sensor_default(si,0,1920,1080);
			initViewInfo_1_sensor_default(si,1,_width,_height);
			initViewInfo_1_sensor_default(si,2,_width,_height);

		}

	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void initViewInfo_output_basic(const int _space_frame)
{

	int si=0;
	const int SensorMAX=SENSOR_MAX_NUM;

	for(si=0;si<SensorMAX;si++){

		if(GetGlobalSensorMask(si)){
				image_View_output(si,_space_frame);
		}

	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void initViewInfo_basic(const int _width,const int _height,const int _space_frame)
{
	ClearViewInfo();
	initViewInfo_img_basic(_width,_height);
	initViewInfo_output_basic(_space_frame);

	saveImgCfgJsonDefault();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CvRect GetRectSpaceChannelFrame(const int _si,const int _fi)
{
	 CvRect rect_t;

	 		 if((GetFpgaCircleWorkMode()&WM_SIZE_FULL)==WM_SIZE_FULL){
	 			 rect_t=image_size_org(_si,_fi);
	 		 }else if((GetFpgaCircleWorkMode()&WM_SIZE_CUT)==WM_SIZE_CUT){
	 			 rect_t=image_size_cut(_si,_fi);
	 		 }

	 return rect_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void  MallocImageBuff4ViewOutput(CMD_CTRL** _buff,const int _seq,const int _img_frame)
{

	int schi=0;
	int sfri=0;

	for(schi=0; schi <SPACE_CHANNEL_NUM;schi++){
		for(sfri=0;sfri<SPACE_FRAME_NUM;sfri++){

						const int frameOutput=is_space_frame_output(schi,sfri);
						const int space_ch_fr_dix=sfri+schi*SPACE_FRAME_NUM;
						const int viewChannel=image_view_channel(schi,sfri);
						const int nChannels=image_nchannels(schi,sfri);

						const CvRect rect=GetRectSpaceChannelFrame(schi,sfri);
						const char* color_model=image_view_colorModel(schi,sfri);

						if((frameOutput==TRUE) &&
							(viewChannel>=0)	){

							_buff[space_ch_fr_dix]=CreateImageCtrl(viewChannel,_img_frame,rect.width,rect.height,nChannels,_seq);

							InitImageColorMode(_buff[space_ch_fr_dix],color_model);

						}



		}
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void copyimage_cut(const unsigned char* _src,
		const unsigned int _src_w,
		const unsigned int _src_h,
		unsigned char* _dst,
		const CvRect rect)
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
void copyimage_cut_ch(const unsigned char* _src,
		const unsigned int _src_w,
		const unsigned int _src_h,
		unsigned char* _dst,
		const CvRect _r,
		const int _chs)
{

	int hi=0;
	const int hi_min=_r.y;
	const int hi_max=_r.y+_r.height;

	const int STEP=_src_w*_chs;
	const int STEP_CUT=_r.width*_chs;


	for(hi=hi_min;hi<hi_max;hi++){

		const int idx_src=_r.x*_chs+hi*STEP;
		const int idx_dst=(hi-_r.y)*STEP_CUT;

		const unsigned char *buff_row_src=&_src[idx_src];
		unsigned char *buff_row_dst=&_dst[idx_dst];

		memcpy(buff_row_dst,buff_row_src,STEP_CUT);
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
void CopyImage(void* const buff_src,CMD_CTRL* img_dst,const  int _space_ch,const int _space_fr)
{
	const CvRect cut_rect=  GetRectSpaceChannelFrame(_space_ch,_space_fr);
	const CvRect rect_roi=  image_size_cut(_space_ch,_space_fr);
	const int ViewChannel=image_view_channel(_space_ch,_space_fr);

	const int image_width_current=image_width(_space_ch,_space_fr);
	const int image_height_current=image_height(_space_ch,_space_fr);
	const int nChannels=image_nchannels(_space_ch,_space_fr);

	const IplImage* const img_ptr=GetIplImage(img_dst);

#if _DEBUG
	if(IsCmdCtrl(img_dst)==FALSE){
		PRINTF_DBG("copy buff_src 2 image: image ctrl is not a valid buff ");
		assert(IsCmdCtrl(img_dst));
	}
#endif



	InitImageRoiRR(img_dst,ViewChannel,cut_rect,rect_roi);


	const unsigned char *buff_src_p=(unsigned char *)buff_src;
	unsigned char *buff_dst_p=(unsigned char *)(img_ptr->imageData);

	if(nChannels==1){

		copyimage_cut(buff_src_p,image_width_current,image_height_current,buff_dst_p,cut_rect);
	}else{

		copyimage_cut_ch(buff_src_p,image_width_current,image_height_current,buff_dst_p,cut_rect,nChannels);
	}



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


	adjRect44(rect);


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
void SetRectCutCmd(CMD_CTRL*  cmd_t)
{

	const IplImageU* imgU=GetIplImageUx(cmd_t);

	const int Viewchannel=UChar2Int(imgU->IpAddrChannel,8);

	const int x=UChar2Int(imgU->x_roi,8);
	const int y=UChar2Int(imgU->y_roi,8);
	int width=UChar2Int(imgU->width_roi,8);
	const int height=UChar2Int(imgU->height_roi,8);

	width=width-width%4;

	const CvRect rect_t=cvRect(x,y,width,height);

	set_img_cut_rect(rect_t,Viewchannel);

	StoreImgCfgJson();

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void encodeWithState(
		const char* filename,
		const unsigned char* image,
		unsigned width,
		unsigned height)
{
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
void SetMaskImageFileName_space_frame(
		char* _filename,
		const int _w,
		const int _h,
		const int _ch_space,
		const int _ch_frame)
{
	assert(_ch_space<SCAR_IMG_MASK_CHANNEL_MAX);
	assert(_ch_frame<SCAR_IMG_MASK_FRAME_MAX);
	sprintf(_filename,
			"%sw.%d.h.%d.chs.%d.chf.%d.mask.png",
			PATH_SDCARD,
			_w,
			_h,
			_ch_space,
			_ch_frame);
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

	encodeWithState(
			filename_t,
			(unsigned char *)data_t,
			width,
			height);

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
void SaveImgMaskMatrix_SCAR(const CMD_CTRL* const  _cmd)
{
	const int UCHAR_SIZE=8;

	const IplImageU * imgU=GetIplImageUx(_cmd);

	char* data_t=GetIplImageImageData(_cmd);

	const int mask_pos=UChar2Int(imgU->IpAddrChannel,UCHAR_SIZE);

	const int ch_space=mask_pos%SCAR_IMG_MASK_CHANNEL_MAX;
	const int ch_frame=mask_pos/SCAR_IMG_MASK_CHANNEL_MAX;

	const int width=UChar2Int(imgU->width,UCHAR_SIZE);
	const int height=UChar2Int(imgU->height,UCHAR_SIZE);

	char filename_t[1024];

	SetMaskImageFileName_space_frame(filename_t,width,height,ch_space,ch_frame);

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


		if(SUCCESS==fs_is_file_exist(filename_t)){
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
CvRect image_view_Rect_cut(int _space_ch,int _space_frame)
{
	return G_View[_space_ch][_space_frame].CutSize;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CvRect image_view_Rect_org(int _space_ch,int _space_frame)
{
	return G_View[_space_ch][_space_frame].OrgSize;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
char* image_view_colorModel(int _space_ch,int _space_frame)
{
	return G_View[_space_ch][_space_frame].colorModel;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int image_view_channel(int _space_ch,int _space_frame)
{
	return G_View[_space_ch][_space_frame].ViewCh;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int image_nchannels(int _space_ch,int _space_frame)
{
	return G_View[_space_ch][_space_frame].nChannels;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int image_width(int _space_ch,int _space_frame)
{
	return G_View[_space_ch][_space_frame].OrgSize.width;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int image_height(int _space_ch,int _space_frame)
{
	return G_View[_space_ch][_space_frame].OrgSize.height;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int image_frame_size(int _space_ch,int _space_frame)
{
	const int w=image_width(_space_ch,_space_frame);
	const int h=image_height(_space_ch,_space_frame);
	const int nchannels=image_nchannels(_space_ch,_space_frame);
	const int imageSize=w*h*nchannels;
	return imageSize;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int is_space_frame_output(int _space_ch,int _space_fr)
{

	return G_View[_space_ch][_space_fr].ViewOutput;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int is_space_frame_used(int _space_ch,int _space_fr)
{

	return G_View[_space_ch][_space_fr].SpaceUsed;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int img_space_frame_output_num()
{
	int schi=0;
	int sfri=0;
	int output_num=0;
	for(schi=0; schi <SPACE_CHANNEL_NUM;schi++){
		for(sfri=0;sfri<SPACE_FRAME_NUM;sfri++){
				if(is_space_frame_output(schi,sfri)){
					output_num++;
				}
		}
	}

	return output_num++;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void set_img_cut_rect(const CvRect _cut,const int _ViewCh)
{
	int schi=0;
	int sfri=0;

	for(schi=0; schi <SPACE_CHANNEL_NUM;schi++){
		for(sfri=0;sfri<SPACE_FRAME_NUM;sfri++){
				if(_ViewCh==image_view_channel(schi,sfri)){
					G_View[schi][sfri].CutSize=_cut;
				}
		}
	}


}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int image_frame_size_first_output(const int _space_ch)
{
		int sfi=0;
		unsigned int frame_size=0;

		for(sfi=0;sfi<SPACE_FRAME_NUM;sfi++){

			if(is_space_frame_output(_space_ch,sfi)){
				frame_size=image_frame_size(_space_ch,sfi);
				break;
			}

		}
		return frame_size;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int image_frame_dma_offset(const int _space_ch,const int _space_frame)
{
	int sfi=0;
	int sci=0;
	unsigned int offset=0;


	for(sci=0;sci<=_space_ch;sci++){

			for(sfi=0;sfi<=_space_frame;sfi++){

						if(is_space_frame_output(sci,sfi)){
							offset+=image_frame_size(sci,sfi);
						}

			}
	}

	offset-=image_frame_size( _space_ch,_space_frame);

	return offset;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int image_frame_fpga_ps_offset(const int _space_ch,const int _space_frame)
{
	unsigned int offset=0;
	int sfi=0;

			for(sfi=0;sfi<_space_frame;sfi++){

						if(is_space_frame_used(_space_ch,sfi)){
							offset+=image_frame_size(_space_ch,sfi);
						}

			}

	return offset;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void* ParseScarImgCfgItem(cJSON*	_cfg_json)
{
				 cJSON *scar_img_cfg_json  = cJSON_GetObjectItemCaseSensitive(_cfg_json, KEY_SCAR_IMG_CFG);

				 cJSON *work_mode  = cJSON_GetObjectItemCaseSensitive(scar_img_cfg_json,  KEY_SCAR_IMG_CFG_WORK_MODE);

				 cJSON *th_global_up  = cJSON_GetObjectItemCaseSensitive(scar_img_cfg_json,  KEY_SCAR_IMG_CFG_TH_GLOBAL_UP );
				 cJSON *th_global_down  = cJSON_GetObjectItemCaseSensitive(scar_img_cfg_json, KEY_SCAR_IMG_CFG_TH_GLOBAL_DOWN);

				 cJSON *th_row_up  =  cJSON_GetObjectItemCaseSensitive(scar_img_cfg_json, KEY_SCAR_IMG_CFG_TH_ROW_UP);
				 cJSON *th_row_down  = cJSON_GetObjectItemCaseSensitive(scar_img_cfg_json, KEY_SCAR_IMG_CFG_TH_ROW_DOWN);

				 cJSON *th_col_up  = cJSON_GetObjectItemCaseSensitive(scar_img_cfg_json, KEY_SCAR_IMG_CFG_TH_COL_UP);
				 cJSON *th_col_down  = cJSON_GetObjectItemCaseSensitive(scar_img_cfg_json, KEY_SCAR_IMG_CFG_TH_COL_DOWN);

				 SetScarWorkMode2FPGA(work_mode->valueint);
				 SetScarGlobalThresholdUp2FPGA(th_global_up->valueint);
				 SetScarGlobalThresholdDown2FPGA(th_global_down->valueint);
				 SetScarRowThresholdUp2FPGA(th_row_up->valueint);
				 SetScarRowThresholdDown2FPGA(th_row_down->valueint);
				 SetScarColThresholdUp2FPGA(th_col_up->valueint);
				 SetScarColThresholdDown2FPGA(th_col_down->valueint);



}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void* ParseSpaceUsedItem(cJSON*	_cfg_json)
{
	 cJSON *space_used_json  = cJSON_GetObjectItemCaseSensitive(_cfg_json, KEY_SPACE_USED_CHANNELS);
		    cJSON *one_space_used_json;

		    cJSON_ArrayForEach(one_space_used_json, space_used_json)
		       {
		    	 cJSON *one_frame_used_json;

		    	 	 	 cJSON_ArrayForEach(one_frame_used_json, one_space_used_json)
		    		       {

																				 /**<----------------------------------------------------------------*/
																					cJSON* SpaceCh 		=	cJSON_GetObjectItemCaseSensitive(one_frame_used_json, KEY_SPACE_CH);
																					cJSON* SpaceFrame 	=	cJSON_GetObjectItemCaseSensitive(one_frame_used_json, KEY_SPACE_FRAME);
																					/**<----------------------------------------------------------------*/
			 	 	 																cJSON* SpaceUsed = 		cJSON_GetObjectItemCaseSensitive(one_frame_used_json, KEY_SPACE_USED);
				    	 	 														cJSON* ViewCh = 		cJSON_GetObjectItemCaseSensitive(one_frame_used_json, KEY_VIEW_CH);
				    	 	 														cJSON* ViewOutput = 	cJSON_GetObjectItemCaseSensitive(one_frame_used_json, KEY_VIEW_OUTPUT);
				    	 	 														cJSON* nChannels = 		cJSON_GetObjectItemCaseSensitive(one_frame_used_json, KEY_N_CHANNELS);

				    	 	 														cJSON* CutSize_x = 		cJSON_GetObjectItemCaseSensitive(one_frame_used_json, KEY_CUT_SIZE_X);
				    	 	 														cJSON* CutSize_y = 		cJSON_GetObjectItemCaseSensitive(one_frame_used_json, KEY_CUT_SIZE_Y);
				    	 	 														cJSON* CutSize_width= 	cJSON_GetObjectItemCaseSensitive(one_frame_used_json, KEY_CUT_SIZE_WIDTH);
				    	 	 														cJSON* CutSize_height= 	cJSON_GetObjectItemCaseSensitive(one_frame_used_json, KEY_CUT_SIZE_HEIGHT);

				    	 	 														cJSON* OrgSize_width = 	cJSON_GetObjectItemCaseSensitive(one_frame_used_json, KEY_ORG_SIZE_WIDTH);
				    	 	 														cJSON* OrgSize_height= 	cJSON_GetObjectItemCaseSensitive(one_frame_used_json, KEY_ORG_SIZE_HEIGHT);
				    	 	 														cJSON* colorMode= 		cJSON_GetObjectItemCaseSensitive(one_frame_used_json, KEY_COLOR_MODE);
																				/**<----------------------------------------------------------------*/
																					const int schi=SpaceCh->valueint;
																					const int sfri=SpaceFrame->valueint;

																					assert(schi==G_View[schi][sfri].SpaceCh);
																					assert(sfri==G_View[schi][sfri].SpaceFrame);


																					G_View[schi][sfri].SpaceUsed=SpaceUsed->valueint;
																					G_View[schi][sfri].ViewCh=ViewCh->valueint;

																					G_View[schi][sfri].ViewOutput=ViewOutput->valueint;
																					G_View[schi][sfri].nChannels=nChannels->valueint;
																					G_View[schi][sfri].CutSize.x=CutSize_x->valueint;
																					G_View[schi][sfri].CutSize.y=CutSize_y->valueint;

																					G_View[schi][sfri].CutSize.width=CutSize_width->valueint;

																					G_View[schi][sfri].CutSize.height=CutSize_height->valueint;
																					G_View[schi][sfri].OrgSize.width=OrgSize_width->valueint;
																					G_View[schi][sfri].OrgSize.height=OrgSize_height->valueint;

																					strcpy(G_View[schi][sfri].colorModel,colorMode->valuestring);

																				/**<----------------------------------------------------------------*/

		    		       }

		       }

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ParseImgCfgJsonStr(const char* _str)
{
	    int status = 0;
	    cJSON *cfg_json = cJSON_Parse(_str);
	    if (cfg_json == NULL){

	        const char *error_ptr = cJSON_GetErrorPtr();
	        if (error_ptr != NULL)
	        {
	            fprintf(stderr, "Error before: %s\n", error_ptr);
	        }
	        status = 0;
	        goto end;

	    }

	    cJSON *sigma_up  = cJSON_GetObjectItemCaseSensitive(cfg_json, KEY_SIGMA_UP);
	    cJSON *sigma_down  = cJSON_GetObjectItemCaseSensitive(cfg_json, KEY_SIGMA_DOWN);

	    SetSigmaUp2FPGA(sigma_up->valueint);
	    SetSigmaDown2FPGA(sigma_down->valueint);

	    ParseSpaceUsedItem(cfg_json);
	    ParseScarImgCfgItem(cfg_json);

	end:
	    cJSON_Delete(cfg_json);
	    return status;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void* AddScarImgCfgItem(cJSON*	_root)
{
	/**<----------------------------------------------------------------*/
		cJSON *scar_img_cfg =cJSON_CreateObject();
	  		 if (scar_img_cfg == NULL){
	  			return NULL;
	  		 }
	  	cJSON_AddItemToObject(_root, KEY_SCAR_IMG_CFG, scar_img_cfg);
	/**<----------------------------------------------------------------*/
	  	{
	  												cJSON* scar_work_mode = cJSON_CreateNumber(GetScarWorkMode());
	  												 if (scar_work_mode == NULL){
	  													 return NULL;
	  												}
	  												cJSON_AddItemToObject(scar_img_cfg, KEY_SCAR_IMG_CFG_WORK_MODE, scar_work_mode);
	  												/**<----------------------------------------------------------------*/
	  												cJSON*  scar_th_global_up = cJSON_CreateNumber(GetScarGlobalThresholdUp());
	  												 if (scar_th_global_up == NULL){
	  													return NULL;
	  												}
	  												cJSON_AddItemToObject(scar_img_cfg, KEY_SCAR_IMG_CFG_TH_GLOBAL_UP, scar_th_global_up);
	  												/**<----------------------------------------------------------------*/
	  												cJSON* scar_th_global_down = cJSON_CreateNumber(GetScarGlobalThresholdDown());
	  												 if (scar_th_global_down == NULL){
	  													 return NULL;
	  												}
	  												cJSON_AddItemToObject(scar_img_cfg, KEY_SCAR_IMG_CFG_TH_GLOBAL_DOWN, scar_th_global_down);
	  												/**<----------------------------------------------------------------*/
	  												cJSON*  scar_th_row_up = cJSON_CreateNumber(GetScarRowThresholdUp());
	  												 if (scar_th_row_up == NULL){
	  													 return NULL;
	  												}
	  												cJSON_AddItemToObject(scar_img_cfg, KEY_SCAR_IMG_CFG_TH_ROW_UP, scar_th_row_up);
	  												/**<----------------------------------------------------------------*/
	  												cJSON* scar_th_row_down = cJSON_CreateNumber(GetScarRowThresholdDown());
	  												 if (scar_th_row_down == NULL){
	  													 return NULL;
	  												}
	  												cJSON_AddItemToObject(scar_img_cfg, KEY_SCAR_IMG_CFG_TH_ROW_DOWN, scar_th_row_down);
	  												/**<----------------------------------------------------------------*/
	  												cJSON*  scar_th_col_up = cJSON_CreateNumber(GetScarColThresholdUp());
	  												 if (scar_th_col_up == NULL){
	  													 return NULL;
	  												}
	  												cJSON_AddItemToObject(scar_img_cfg, KEY_SCAR_IMG_CFG_TH_COL_UP, scar_th_col_up);
	  												/**<----------------------------------------------------------------*/
	  												cJSON* scar_th_col_down = cJSON_CreateNumber(GetScarColThresholdDown());
	  												 if (scar_th_col_down == NULL){
	  													 return NULL;
	  												}
	  												cJSON_AddItemToObject(scar_img_cfg, KEY_SCAR_IMG_CFG_TH_COL_DOWN, scar_th_col_down);
	  												/**<----------------------------------------------------------------*/
	  	}
		/**<----------------------------------------------------------------*/
		return scar_img_cfg;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void* AddSpaceUsedItem(cJSON*	_root)
{
	    cJSON * space_used_all = cJSON_CreateArray();
	    if (space_used_all == NULL)
	    {
	    	 return NULL;
	    }
	    cJSON_AddItemToObject(_root, KEY_SPACE_USED_CHANNELS, space_used_all);
	 /**<----------------------------------------------------------------*/


	 /**<----------------------------------------------------------------*/
	int schi=0;
	int sfri=0;

	for(schi=0; schi <SPACE_CHANNEL_NUM;schi++){
		 	 	 	/**<----------------------------------------------------------------*/
					cJSON *space_used_one_channel =cJSON_CreateArray();
					if (space_used_one_channel == NULL){
						 return NULL;
					}
					cJSON_AddItemToArray(space_used_all,space_used_one_channel);
					/**<----------------------------------------------------------------*/
					for(sfri=0;sfri<SPACE_FRAME_NUM;sfri++){
									if(is_space_frame_used(schi,sfri)){
													/**<----------------------------------------------------------------*/
													cJSON *space_used_one_frame =cJSON_CreateObject();
													if (space_used_one_frame == NULL){
														 return NULL;
													}
													cJSON_AddItemToArray(space_used_one_channel,space_used_one_frame);
													/**<----------------------------------------------------------------*/
													cJSON* SpaceCh = cJSON_CreateNumber(G_View[schi][sfri].SpaceCh);
													 if (SpaceCh == NULL){
														 return NULL;
													}
													cJSON_AddItemToObject(space_used_one_frame, KEY_SPACE_CH, SpaceCh);
#if 1
													/**<----------------------------------------------------------------*/
													cJSON* SpaceFrame = cJSON_CreateNumber(G_View[schi][sfri].SpaceFrame);
													 if (SpaceFrame == NULL){
														 return NULL;
													}
													cJSON_AddItemToObject(space_used_one_frame, KEY_SPACE_FRAME, SpaceFrame);
													/**<----------------------------------------------------------------*/
													cJSON* SpaceUsed = cJSON_CreateNumber(G_View[schi][sfri].SpaceUsed);
													 if (SpaceUsed == NULL){
														 return NULL;
													}
													cJSON_AddItemToObject(space_used_one_frame, KEY_SPACE_USED, SpaceUsed);
													/**<----------------------------------------------------------------*/
													cJSON* ViewCh = cJSON_CreateNumber(G_View[schi][sfri].ViewCh);
													 if (ViewCh == NULL){
														 return NULL;
													}
													cJSON_AddItemToObject(space_used_one_frame, KEY_VIEW_CH, ViewCh);
													/**<----------------------------------------------------------------*/
													cJSON* ViewOutput = cJSON_CreateNumber(G_View[schi][sfri].ViewOutput);
													 if (ViewOutput == NULL){
														 return NULL;
													}
													cJSON_AddItemToObject(space_used_one_frame, KEY_VIEW_OUTPUT, ViewOutput);
													/**<----------------------------------------------------------------*/
													cJSON* nChannels = cJSON_CreateNumber(G_View[schi][sfri].nChannels);
													 if (nChannels == NULL){
														 return NULL;
													}
													cJSON_AddItemToObject(space_used_one_frame, KEY_N_CHANNELS, nChannels);
													/**<----------------------------------------------------------------*/
													cJSON* CutSize_x = cJSON_CreateNumber(G_View[schi][sfri].CutSize.x);
													 if (CutSize_x == NULL){
														 return NULL;
													}
													cJSON_AddItemToObject(space_used_one_frame, KEY_CUT_SIZE_X, CutSize_x);
													/**<----------------------------------------------------------------*/
													cJSON* CutSize_y = cJSON_CreateNumber(G_View[schi][sfri].CutSize.y);
													 if (CutSize_y == NULL){
														 return NULL;
													}
													cJSON_AddItemToObject(space_used_one_frame, KEY_CUT_SIZE_Y, CutSize_y);
													/**<----------------------------------------------------------------*/
													cJSON* CutSize_width = cJSON_CreateNumber(G_View[schi][sfri].CutSize.width);
													 if (CutSize_width == NULL){
														 return NULL;
													}
													cJSON_AddItemToObject(space_used_one_frame, KEY_CUT_SIZE_WIDTH, CutSize_width);
													/**<----------------------------------------------------------------*/
													cJSON* CutSize_height= cJSON_CreateNumber(G_View[schi][sfri].CutSize.height);
													if (CutSize_height== NULL){
														 return NULL;
													}
													cJSON_AddItemToObject(space_used_one_frame,KEY_CUT_SIZE_HEIGHT, CutSize_height);
													/**<----------------------------------------------------------------*/
													cJSON* OrgSize_width = cJSON_CreateNumber(G_View[schi][sfri].OrgSize.width);
													 if (OrgSize_width == NULL){
														 return NULL;
													}
													cJSON_AddItemToObject(space_used_one_frame, KEY_ORG_SIZE_WIDTH, OrgSize_width);
													/**<----------------------------------------------------------------*/
													cJSON* OrgSize_height= cJSON_CreateNumber(G_View[schi][sfri].OrgSize.height);
													if (OrgSize_height== NULL){
														 return NULL;
													}
													cJSON_AddItemToObject(space_used_one_frame, KEY_ORG_SIZE_HEIGHT, OrgSize_height);
													/**<----------------------------------------------------------------*/
													cJSON* colorMode= cJSON_CreateString(G_View[schi][sfri].colorModel);
													if (OrgSize_height== NULL){
														 return NULL;
													}
													cJSON_AddItemToObject(space_used_one_frame, KEY_COLOR_MODE, colorMode);
													/**<----------------------------------------------------------------*/
#endif


									}
					}


	}

	return space_used_all;


}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
char* GetImgCfgJsonStr()
{
	     /**<----------------------------------------------------------------*/
	    cJSON *root = cJSON_CreateObject();
	    if (root == NULL)
	    {
	        goto end;
	    }
	    /**<----------------------------------------------------------------*/
	    cJSON * space_used_config = cJSON_CreateString(NOTE_SPACE_USED_CFG);
	    if (space_used_config == NULL)
	    {
	        goto end;
	    }
	    cJSON_AddItemToObject(root, KEY_SPACE_USED_CFG,space_used_config);
	    /**<----------------------------------------------------------------*/
	    cJSON * sigma_up =  cJSON_CreateNumber(GetSigmaUp());
	    if (sigma_up == NULL)
	    {
	        goto end;
	    }
	    cJSON_AddItemToObject(root, KEY_SIGMA_UP, sigma_up);
	    /**<----------------------------------------------------------------*/
	    cJSON * sigma_down =  cJSON_CreateNumber(GetSigmaDown());
	    if (sigma_down == NULL)
	    {
	        goto end;
	    }
	    cJSON_AddItemToObject(root, KEY_SIGMA_DOWN, sigma_down);
	    /**<----------------------------------------------------------------*/
	    cJSON * project =  cJSON_CreateString(GetProjectRunStr());
	  	    if (project == NULL)
	  	    {
	  	        goto end;
	  	    }
	  	 cJSON_AddItemToObject(root, KEY_PROJECT, project);
		 /**<----------------------------------------------------------------*/
	  	 cJSON* scar_img_cfg =AddScarImgCfgItem(root);
	  		 if (scar_img_cfg == NULL){
	  		 	goto end;
	  		 }
	    /**<----------------------------------------------------------------*/
	   	 cJSON* space_used_all = AddSpaceUsedItem(root);
	   	    if (space_used_all == NULL){
	   	        goto end;
	   	    }
	   	  /**<----------------------------------------------------------------*/
		    char* string = cJSON_Print(root);
	    	    if (string == NULL)
	    	    {
	    	        fprintf(stderr, "Failed to print monitor.\n");
	    	    }
	   /**<----------------------------------------------------------------*/
end:
	    cJSON_Delete(root);
	    return string;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void initImgCfgJsonFileDefault(char* _cfg_json_file)
{
	sprintf(_cfg_json_file,"%s%s",PATH_SDCARD,IMG_CFG_JSON_DEFAULT);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void initImgCfgJsonFileEx(char* _cfg_json_file)
{
	sprintf(_cfg_json_file,"%s%s",PATH_SDCARD,IMG_CFG_JSON);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void saveImgCfgJsonDefault()
{
	char cfg_json_file[256];
	initImgCfgJsonFileDefault(cfg_json_file);

	char* cfg_json=GetImgCfgJsonStr();
			fs_store_txt(cfg_json_file,cfg_json);
	cJSON_free(cfg_json);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void StoreImgCfgJson()
{
	char cfg_json_file[256];
	initImgCfgJsonFileEx(cfg_json_file);

	char* cfg_json=GetImgCfgJsonStr();
			fs_store_txt(cfg_json_file,cfg_json);
	cJSON_free(cfg_json);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void LoadImgCfgJson()
{

	char cfg_json_file[256];
	initImgCfgJsonFileEx(cfg_json_file);

	if(fs_is_file_exist(cfg_json_file)==SUCCESS){

				int file_size=fs_file_size(cfg_json_file);

				char *buffer=malloc(file_size+1);
				{
								if(fs_load_txt(cfg_json_file,buffer)==SUCCESS){
										ParseImgCfgJsonStr(buffer);
								}

				}
				free(buffer);
				buffer=NULL;

	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
