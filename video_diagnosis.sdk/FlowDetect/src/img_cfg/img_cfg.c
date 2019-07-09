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
const char* KEY_PROJECT		=	"project";
const char* KEY_SIGMA		=	"sigma";
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
				strcpy(G_View[schi][sfri].colorModel,COLOR_GRAY);
		}
	}

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
				if(is_space_frame_output(schi,sfri)){

						const int space_ch_fr_dix=sfri+schi*SPACE_FRAME_NUM;

						const int View_channel=image_view_channel(schi,sfri);
						const int nChannels=image_view_nChannel(schi,sfri);

						const CvRect rect=GetRectSpaceChannelFrame(schi,sfri);


						_buff[space_ch_fr_dix]=CreateImageCtrl(View_channel,_img_frame,rect.width,rect.height,nChannels,_seq);

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


	copyimage_cut(buff_src_p,image_width_current,image_height_current,buff_dst_p,cut_rect);

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
int image_view_nChannel(int _space_ch,int _space_frame)
{
	return G_View[_space_ch][_space_frame].nChannels;
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


	    cJSON *space_used_json  = cJSON_GetObjectItemCaseSensitive(cfg_json, KEY_SPACE_USED_CHANNELS);
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


	end:
	    cJSON_Delete(cfg_json);
	    return status;
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
	    cJSON * sigma =  cJSON_CreateNumber(GetSigma());
	    if (sigma == NULL)
	    {
	        goto end;
	    }
	    cJSON_AddItemToObject(root, KEY_SIGMA, sigma);
	    /**<----------------------------------------------------------------*/
	    cJSON * project =  cJSON_CreateString(GetProjectRunStr());
	  	    if (project == NULL)
	  	    {
	  	        goto end;
	  	    }
	  	 cJSON_AddItemToObject(root, KEY_PROJECT, project);
	    /**<----------------------------------------------------------------*/
	   	    cJSON * space_used_all = cJSON_CreateArray();
	   	    if (space_used_all == NULL)
	   	    {
	   	        goto end;
	   	    }
	   	    cJSON_AddItemToObject(root, KEY_SPACE_USED_CHANNELS, space_used_all);
	   	 /**<----------------------------------------------------------------*/
	    	int schi=0;
	    	int sfri=0;

	    	for(schi=0; schi <SPACE_CHANNEL_NUM;schi++){
	    		 	 	 	/**<----------------------------------------------------------------*/
							cJSON *space_used_one_channel =cJSON_CreateArray();
							if (space_used_one_channel == NULL){
									goto end;
							}
							cJSON_AddItemToArray(space_used_all,space_used_one_channel);
							/**<----------------------------------------------------------------*/
							for(sfri=0;sfri<SPACE_FRAME_NUM;sfri++){
											if(is_space_frame_used(schi,sfri)){
															/**<----------------------------------------------------------------*/
															cJSON *space_used_one_frame =cJSON_CreateObject();
															if (space_used_one_frame == NULL){
																		goto end;
															}
															cJSON_AddItemToArray(space_used_one_channel,space_used_one_frame);
															/**<----------------------------------------------------------------*/
															cJSON* SpaceCh = cJSON_CreateNumber(G_View[schi][sfri].SpaceCh);
															 if (SpaceCh == NULL){
																goto end;
															}
															cJSON_AddItemToObject(space_used_one_frame, KEY_SPACE_CH, SpaceCh);
#if 1
															/**<----------------------------------------------------------------*/
															cJSON* SpaceFrame = cJSON_CreateNumber(G_View[schi][sfri].SpaceFrame);
															 if (SpaceFrame == NULL){
																goto end;
															}
															cJSON_AddItemToObject(space_used_one_frame, KEY_SPACE_FRAME, SpaceFrame);
															/**<----------------------------------------------------------------*/
															cJSON* SpaceUsed = cJSON_CreateNumber(G_View[schi][sfri].SpaceUsed);
															 if (SpaceUsed == NULL){
																goto end;
															}
															cJSON_AddItemToObject(space_used_one_frame, KEY_SPACE_USED, SpaceUsed);
															/**<----------------------------------------------------------------*/
															cJSON* ViewCh = cJSON_CreateNumber(G_View[schi][sfri].ViewCh);
															 if (ViewCh == NULL){
																goto end;
															}
															cJSON_AddItemToObject(space_used_one_frame, KEY_VIEW_CH, ViewCh);
															/**<----------------------------------------------------------------*/
															cJSON* ViewOutput = cJSON_CreateNumber(G_View[schi][sfri].ViewOutput);
															 if (ViewOutput == NULL){
																goto end;
															}
															cJSON_AddItemToObject(space_used_one_frame, KEY_VIEW_OUTPUT, ViewOutput);
															/**<----------------------------------------------------------------*/
															cJSON* nChannels = cJSON_CreateNumber(G_View[schi][sfri].nChannels);
															 if (nChannels == NULL){
																goto end;
															}
															cJSON_AddItemToObject(space_used_one_frame, KEY_N_CHANNELS, nChannels);
															/**<----------------------------------------------------------------*/
															cJSON* CutSize_x = cJSON_CreateNumber(G_View[schi][sfri].CutSize.x);
															 if (CutSize_x == NULL){
																goto end;
															}
															cJSON_AddItemToObject(space_used_one_frame, KEY_CUT_SIZE_X, CutSize_x);
															/**<----------------------------------------------------------------*/
															cJSON* CutSize_y = cJSON_CreateNumber(G_View[schi][sfri].CutSize.y);
															 if (CutSize_y == NULL){
																goto end;
															}
															cJSON_AddItemToObject(space_used_one_frame, KEY_CUT_SIZE_Y, CutSize_y);
															/**<----------------------------------------------------------------*/
															cJSON* CutSize_width = cJSON_CreateNumber(G_View[schi][sfri].CutSize.width);
															 if (CutSize_width == NULL){
																goto end;
															}
															cJSON_AddItemToObject(space_used_one_frame, KEY_CUT_SIZE_WIDTH, CutSize_width);
															/**<----------------------------------------------------------------*/
															cJSON* CutSize_height= cJSON_CreateNumber(G_View[schi][sfri].CutSize.height);
															if (CutSize_height== NULL){
																goto end;
															}
															cJSON_AddItemToObject(space_used_one_frame,KEY_CUT_SIZE_HEIGHT, CutSize_height);
															/**<----------------------------------------------------------------*/
															cJSON* OrgSize_width = cJSON_CreateNumber(G_View[schi][sfri].OrgSize.width);
															 if (OrgSize_width == NULL){
																goto end;
															}
															cJSON_AddItemToObject(space_used_one_frame, KEY_ORG_SIZE_WIDTH, OrgSize_width);
															/**<----------------------------------------------------------------*/
															cJSON* OrgSize_height= cJSON_CreateNumber(G_View[schi][sfri].OrgSize.height);
															if (OrgSize_height== NULL){
																goto end;
															}
															cJSON_AddItemToObject(space_used_one_frame, KEY_ORG_SIZE_HEIGHT, OrgSize_height);
															/**<----------------------------------------------------------------*/
															cJSON* colorMode= cJSON_CreateString(G_View[schi][sfri].colorModel);
															if (OrgSize_height== NULL){
																goto end;
															}
															cJSON_AddItemToObject(space_used_one_frame, KEY_COLOR_MODE, colorMode);
															/**<----------------------------------------------------------------*/
#endif


											}
							}


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
