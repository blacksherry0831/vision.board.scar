#include "type.h"

/*-----------------------------------*/
const int ALIGN_BYTE=4;
/*-----------------------------------*/
void InitImageRoiRR(CMD_CTRL* cmd_t,int _ch,CvRect _rect_org,CvRect _rect_roi);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int SetCmdParam(
		const CMD_CTRL* const _cmd_ctrl,
		const unsigned int _param)
{

	assert(_param>=0);
	assert(_cmd_ctrl->f_data_size>=2);

	_cmd_ctrl->f_data[0] = _param % 256;//low
	_cmd_ctrl->f_data[1] = _param / 256;//height

	return _param;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsCmdCtrlCmd(
		const CMD_CTRL* _cmd_ctrl,
		const unsigned char _cmd00,
		const unsigned char _cmd01)
{
	const CMD_CTRL_HEADER* _cmd=&(_cmd_ctrl->f_header);

	if( 	_cmd->f_cmd[0]==_cmd00 &&
			_cmd->f_cmd[1]==_cmd01){

		return TRUE;
	}else{
		return FALSE;
	}


}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetSensorStatus(CMD_CTRL* _cmd)
{
	IplImageU *image=(IplImageU *)_cmd->f_data;

	return UChar2Int(image->sensor_stat,sizeof(int));
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetSensorStatus(CMD_CTRL* _cmd,int _status,int _channel)
{
	if(_cmd==NULL) return;

	IplImageU *image=(IplImageU *)_cmd->f_data;

	const int SENSOR_STATUS=_status & (1<<_channel);

	SetInt2Char(SENSOR_STATUS,image->sensor_stat,ALIGN_SIZE_T-1);
}
/*-----------------------------------*/
/**
 *设置图片的色彩通道数
 */
/*-----------------------------------*/
void SetNchannels(CMD_CTRL* _cmd,int _nChannels)
{
	if(_cmd==NULL) return;

	IplImageU *image=(IplImageU *)_cmd->f_data;
	SetInt2Char(_nChannels,image->nChannels,ALIGN_SIZE_T-1);

	IplImage *Iplimg=&(image->Iplimg);
	Iplimg->nChannels=_nChannels;
	assert( Iplimg->width>0);
	Iplimg->widthStep= Iplimg->width*_nChannels;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetCMDBodySize(CMD_CTRL_HEADER _cmd)
{
	unsigned int size_t=_cmd.f_data_len[0]+
				_cmd.f_data_len[1]*256+
				_cmd.f_data_len_high[0]*256*256+
				_cmd.f_data_len_high[1]*256*256*256;
		
	return size_t;
	
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
char* 	GetIplImageImageData(const CMD_CTRL* const  _cmd)
{
	char* data_t=(char *)( & (_cmd->f_data[sizeof(IplImageUI)] ) );
	return data_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
IplImage* 	GetIplImage(const CMD_CTRL* cmd)
{
		 return & (((IplImageU*)( cmd->f_data))->Iplimg);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
IplImageU* GetIplImageUx(const CMD_CTRL* cmd_t)
{
	 return (IplImageU *)(cmd_t->f_data);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int isDoneCmd(const CMD_CTRL* const _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,'c',0x01);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int isStartCmd(const CMD_CTRL* const _cmd_ctrl)
{
	CMD_CTRL_HEADER _cmd=_cmd_ctrl->f_header;
	

	if( _cmd.f_cmd[0]==CT_CTRL){

		if(	(_cmd.f_cmd[1]==CT_START)    ||
			(_cmd.f_cmd[1]==CT_STOP) ||
			(_cmd.f_cmd[1]==CT_START_00) ||
			(_cmd.f_cmd[1]==CT_START_01) ||
			(_cmd.f_cmd[1]==CT_STOP_00) ||
			(_cmd.f_cmd[1]==CT_STOP_01) ){

			return TRUE;
		}

	}
		return FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetCmdParam(const CMD_CTRL* const _cmd_ctrl)
{

	assert(_cmd_ctrl->f_data_size>=2);

	const int param=_cmd_ctrl->f_data[0]+_cmd_ctrl->f_data[1]*256;

	return param;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetCmdCmd01(const CMD_CTRL* const _cmd_ctrl)
{
	const CMD_CTRL_HEADER* _cmd=&(_cmd_ctrl->f_header);

	const int param=_cmd->f_cmd[1];

	return param;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetStartCmdParam(const CMD_CTRL* const _cmd_ctrl)
{

	if(isStartCmd(_cmd_ctrl)){

		return GetCmdParam(_cmd_ctrl);

	}

	return -1;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetCmdImgViewChannel(const CMD_CTRL* const _cmd_ctrl)
{
	IplImageU* imgU=GetIplImageUx(_cmd_ctrl);

	return	_4UChar2Int(imgU->IpAddrChannel);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetCmdFrameSeq(const CMD_CTRL* const _cmd_ctrl)
{
	const unsigned int seq_t=_cmd_ctrl->f_header.f_cmd_idx[0]
	                        +_cmd_ctrl->f_header.f_cmd_idx[1]*256
	                        +_cmd_ctrl->f_header.f_cmd_idx[2]*256*256
	                        +_cmd_ctrl->f_header.f_cmd_idx[3]*256*256*256;

	return seq_t;
}
/*-----------------------------------*/
/**
 *设置命令序列号
 */
/*-----------------------------------*/
void SetCmdFrameSeq(CMD_CTRL*  _cmd_ctrl,unsigned int _cmd_idx)
{
	_cmd_ctrl->f_header.f_cmd_idx[0]= _cmd_idx % 256;
	_cmd_ctrl->f_header.f_cmd_idx[1]= _cmd_idx /256 % 256;
	_cmd_ctrl->f_header.f_cmd_idx[2]= _cmd_idx /256 /256% 256;
	_cmd_ctrl->f_header.f_cmd_idx[3]= _cmd_idx /256 /256 /256 % 256;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int isLifeCircleDeadlineCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_QUERY,CT_LIFE_CIRCLE_DEADLINE);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int isVersionCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_QUERY,CT_VERSION);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int isHeartbeatCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_HEART,CT_BEAT);
}
/*-----------------------------------*/
/**
 *将命令设为图片命令（图片I）
 */
/*-----------------------------------*/
int SetImageCmd(CMD_CTRL* _cmd_ctrl,const unsigned char _flag)
{
	CMD_CTRL_HEADER* _cmd=&(_cmd_ctrl->f_header);

	 _cmd->f_cmd[0]=CT_IMG;

	 _cmd->f_cmd[1]=_flag;

	return TRUE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetHeartbeatCmd(CMD_CTRL* cmd,int _need_resp)
{
	cmd->f_header.f_cmd[0]=CT_HEART;
	cmd->f_header.f_cmd[1]=CT_BEAT;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageFrame(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_FRAME);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageMaskChange(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_MASK_CHANGE);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageRect(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_RECT);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageChangeWorkMode(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_MODE_CHANGE);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageChangeSigmaUp(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_SIGMA_UP_CHANGE);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageQuerySigmaUp(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_QUERY,CT_IMG_SIGMA_UP_CHANGE);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageChangeSigmaDown(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_SIGMA_DOWN_CHANGE);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageQuerySigmaDown(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_QUERY,CT_IMG_SIGMA_DOWN_CHANGE);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int socket_read_1_cmd(int _sockfd,CMD_CTRL*  _cmd_ptr)
{

	 const int HEADER_SIZE = sizeof(CMD_CTRL_HEADER);

	 	 memset(&(_cmd_ptr->f_header),0,HEADER_SIZE);

	 if(readn(_sockfd,&(_cmd_ptr->f_header), HEADER_SIZE)!=HEADER_SIZE)
		 return FALSE;

	 const int BODY_SIZE=GetCMDBodySize(_cmd_ptr->f_header);

	 assert(BODY_SIZE>=2);

	 CreateCmdBody(_cmd_ptr,BODY_SIZE);


	 if(readn(_sockfd,_cmd_ptr->f_data,BODY_SIZE)!=BODY_SIZE)
		 return FALSE;


	 if(readn(_sockfd,&(_cmd_ptr->f_crc),1)!=1)
		 return FALSE;

	 return TRUE;
}

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int socket_write_1_cmd(int _sockfd,CMD_CTRL*  _cmd_ptr)
{

#ifdef _DEBUG

	static int image_frame_idx=0;
	if(IsImageFrame( _cmd_ptr)){
		image_frame_idx++;
	}

#endif

	if(IsCmdCtrl(_cmd_ptr)==FALSE){

		return FALSE;
	}

	ssize_t w_size_t=0;
	const int BODY_SIZE=_cmd_ptr->f_data_size;


	w_size_t=writen(_sockfd,&(_cmd_ptr->f_header),sizeof(CMD_CTRL_HEADER));

	if(w_size_t!=sizeof(CMD_CTRL_HEADER)){
		return FALSE;
	}

	 w_size_t=writen(_sockfd,_cmd_ptr->f_data,BODY_SIZE);

	 if(w_size_t!=BODY_SIZE){
		 return FALSE;
	 }


	 w_size_t=writen(_sockfd,&(_cmd_ptr->f_crc),1);

	 if(w_size_t!=1){
		 return FALSE;
	 }


	return TRUE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int socket_write_1_cmd_raw_data(int _sockfd,CMD_CTRL*  _cmd_ptr)
{

	ssize_t w_size_t=0;

	IplImageU * image=(IplImageU*) _cmd_ptr->f_data;

	IplImage*   IplImg=&(image->Iplimg);

	 w_size_t=writen(_sockfd,IplImg->imageData,IplImg->imageSize);


	 if( w_size_t==IplImg->imageSize){
		 return TRUE;
	 }else{
		 return FALSE;
	 }

	return TRUE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  TestCmdCtrl(CMD_CTRL*  _cmd_ptr)
{
#ifdef _DEBUG
#if 0
			if(isHeartbeatCmd(_cmd_ptr)){
				PRINTF_DBG_EX("socket send : HeartbeatCmd\n");
			}

			if(IsImageFrame(_cmd_ptr)){
				PRINTF_DBG_EX("socket send : ImageFrame\n");
			}

			if(IsFilePut(_cmd_ptr)){
				const char* ffp=GetCmdCtrl_File_FullName(_cmd_ptr);
				PRINTF_DBG_EX("socket send : File %s \n",ffp);
			}
#endif
#endif
			return 1;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int socket_write_1_cmd_release(int _sockfd,CMD_CTRL*  _cmd_ptr)
{
	int status=TRUE;

	if(IsCmdCtrl(_cmd_ptr)){

			status=socket_write_1_cmd(_sockfd,_cmd_ptr);
			assert(TestCmdCtrl(_cmd_ptr));
			ReleaseCmdCtrl(&_cmd_ptr);


	}else{
		//error memory
			printf("not a valid buff\n");
	}

	return status;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int socket_write_1_cmd_release_time_cost(
		const int 		_socketfd,
		int*			_status,
		CMD_CTRL* 	 	_cmd_ptr,
		const char* 	_msg)
{
		assert(_status!=NULL);
		*_status=FALSE;
		TIME_START();
		*_status=socket_write_1_cmd_release(_socketfd,_cmd_ptr);
		TIME_END(_msg);
		return *_status;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int socket_write_1_cmd_raw_release(int _sockfd,CMD_CTRL*  _cmd_ptr)
{
	int status=socket_write_1_cmd_raw_data(_sockfd,_cmd_ptr);

	ReleaseCmdCtrl(&_cmd_ptr);

	return status;
}
/*-----------------------------------*/
/**
 *释放命令控制数据实体空间
 */
/*-----------------------------------*/
void FreeCmdBody(CMD_CTRL*  _cmd_ptr)
{
	void * ptr=_cmd_ptr->f_data;
		mem_free_clr(&(ptr));
	_cmd_ptr->f_data_size=0;
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
void initIplimageHeader(IplImage * _img,
		char* _data,
		const int _width,
		const int _height,
		const int _nchannels)
{
	const unsigned int SIZE=_width*_height*_nchannels;

	if(_img!=NULL){
			_img->imageData=_data;
			_img->width=_width;
			_img->height=_height;
			_img->imageSize=SIZE;
			_img->nChannels=_nchannels;
	}else{
			PRINTF_DBG_EX("no memory");
	}

}
/*-----------------------------------*/
/**
 *将命令设为图片命令，并将图片相关参数记录到命令中
 */
/*-----------------------------------*/
void InitImageCfg(CMD_CTRL* cmd_t,const int _ch,int _frame,int _width,int _height)
{

	SetImageCmd(cmd_t,CT_IMG_FRAME);  //将命令设为图片命令

	IplImageU *image=GetIplImageUx(cmd_t);
	IplImage *Iplimg=GetIplImage(cmd_t);

	if(image!=NULL){
		/*-----------------------------------*/
			image->prefix[0]='I';
			image->prefix[1]='m';
			image->prefix[2]='a';
			image->prefix[3]='g';
			image->prefix[4]='e';
			image->prefix[5]='\0';
			/*-----------------------------------*/
			SetInt2Char(sizeof(IplImageU),image->nSize,ALIGN_SIZE_T);
			SetInt2Char(_ch,image->IpAddrChannel,ALIGN_SIZE_T);
			SetInt2Char(_frame,image->frame,ALIGN_SIZE_T);
			SetInt2Char(_width,image->width,ALIGN_SIZE_T);
			SetInt2Char(_height,image->height,ALIGN_SIZE_T);
			/*-----------------------------------*/
			SetInt2Char(0,image->width_roi,ALIGN_SIZE_T);
			SetInt2Char(0,image->height_roi,ALIGN_SIZE_T);
			SetInt2Char(0,image->x_roi,ALIGN_SIZE_T);
			SetInt2Char(0,image->y_roi,ALIGN_SIZE_T);
			/*-----------------------------------*/
	}else{
		PRINTF_DBG_EX("no memory");
	}

	char* data_t=GetIplImageImageData(cmd_t);

	initIplimageHeader(Iplimg,data_t,_width,_height,1); //初始化图片相关参数

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void InitImageRoi(CMD_CTRL* cmd_t,CvRect _rect_roi)
{
	IplImageU* imgU=GetIplImageUx(cmd_t);
	if(imgU!=NULL){
		SetInt2Char(_rect_roi.width,imgU->width_roi,ALIGN_SIZE_T);
		SetInt2Char(_rect_roi.height,imgU->height_roi,ALIGN_SIZE_T);
		SetInt2Char(_rect_roi.x,imgU->x_roi,ALIGN_SIZE_T);
		SetInt2Char(_rect_roi.y,imgU->y_roi,ALIGN_SIZE_T);
	}
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void InitImageColorMode(CMD_CTRL* cmd_t,const char* _color_mode)
{
	IplImageU* imgU=GetIplImageUx(cmd_t);
	if(imgU!=NULL){
		strcpy(imgU->colorModel,_color_mode);
	}
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void InitImageRoiRR(CMD_CTRL* cmd_t,int _ch,CvRect _rect_org,CvRect _rect_roi)
{
	if(IsEffectiveRect(&_rect_roi)){

		if((_rect_org.height !=_rect_roi.height )&&
					(_rect_org.width!=_rect_roi.width)&&
					(_rect_org.x!=_rect_roi.x)&&
					(_rect_org.y!=_rect_roi.y)){

					InitImageRoi(cmd_t,_rect_roi);
					return;

			}

	}

	InitImageRoi(cmd_t,cvRect(0,0,0,0));


}
/*-----------------------------------*/
/**
 *设置命令实体控制数据长度，并申请空间
 */
/*-----------------------------------*/
void CreateCmdBody(CMD_CTRL* cmd_t,unsigned int body_size)
{
	body_size=(body_size>2)?body_size:2;

	if(cmd_t->f_data!=NULL){
		FreeCmdBody(cmd_t);
	}

	cmd_t->f_data=mem_malloc(body_size);

	if(cmd_t->f_data!=NULL){


		cmd_t->f_data_size=body_size;

		const int low_0=cmd_t->f_data_size%256;
		const int high_0=cmd_t->f_data_size/256%256;
		const int low_1=cmd_t->f_data_size/256/256%256;
		const int high_1=cmd_t->f_data_size/256/256/256;

		cmd_t->f_header.f_data_len[0]=low_0;
		cmd_t->f_header.f_data_len[1]=high_0;

		cmd_t->f_header.f_data_len_high[0]=low_1;
		cmd_t->f_header.f_data_len_high[1]=high_1;
	}


}
/*-----------------------------------*/
/**
 *填充图片内容数据
 */
/*-----------------------------------*/
void FillImageCtrl(CMD_CTRL* _cmd,const int _data)
{
	 IplImage* img_ptr=GetIplImage( _cmd);

	 unsigned char *buff_p=(unsigned char *)(img_ptr->imageData);

	 const  int buff_sz_t=img_ptr->imageSize;

	 memset(buff_p,_data,buff_sz_t);

}
/*-----------------------------------*/
/**
 *创建并初始化图片命令（cmd_ctrl）
 */
/*-----------------------------------*/
CMD_CTRL* CreateImageCtrl(const int _ch,int _frame,int _width,int _height,int _nChs, int _seq)
{
	assert(_nChs!=0);
	assert(_width!=0);
	assert(_height!=0);
	assert(_width<=1920);
	assert(_height<=1080);

	const unsigned int UnionSize=sizeof(IplImageUI);
	const unsigned int SIZE=_width*_height*_nChs;
	const unsigned int body_size=UnionSize+SIZE;

	assert(UnionSize<=STRUCT_UNION_SIZE);

	CMD_CTRL*  cmd_t=CreateCmdCtrl(body_size);  //申请命令空间，并设置命令头和命令控制数据实体长度
	if(cmd_t!=NULL){
		InitImageCfg(cmd_t,_ch,_frame,_width,_height);  //将命令设为图片命令，并将图片相关参数记录到命令中
		SetNchannels(cmd_t,_nChs);  //设置图片的色彩通道数
		SetCmdFrameSeq(cmd_t,_seq);  //设置命令序列号

	}

	assert(IsCmdCtrl_Debug(cmd_t,"copy buff_src 2 image: image ctrl is not a valid buff"));

	return cmd_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CMD_CTRL* CreateImageMask(const int _ch,const int _w,const int _h,unsigned int _seq)
{
	const int nChs=1;
	CMD_CTRL*  cmd_t=CreateImageCtrl(_ch,FRAME_IDX_TYPE_START,_w,_h,nChs,_seq);//4 byte align
	SetImageCmd(cmd_t,CT_IMG_MASK_CHANGE);
	return cmd_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CMD_CTRL* CreateImageStart(const int _ch,unsigned int _seq)
{
	const int nChs=1;
	const int wh=4;
	CMD_CTRL*  cmd_t=CreateImageCtrl(_ch,FRAME_IDX_TYPE_START,wh,wh,nChs,_seq);//4 byte align
	SetImageCmd(cmd_t,CT_START);
	return cmd_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CMD_CTRL* CreateImageStop(int _ch,unsigned int _seq)
{
	const int nChs=1;
	const int wh=4;
	CMD_CTRL*  cmd_t=CreateImageCtrl(_ch,FRAME_IDX_TYPE_STOP,wh,wh,nChs,_seq);//4 byte align
	SetImageCmd(cmd_t,CT_STOP);
	return cmd_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CMD_CTRL* CreateImageHeartbeat(
		const int _ch,
		const unsigned int _need_resp,
		const int _seq)
{
	CMD_CTRL*  cmd_t=CreateImageCtrl(_ch,FRAME_IDX_TYPE_HEARBEAT,ALIGN_BYTE,1,1,_seq);//4 byte align
	SetHeartbeatCmd(cmd_t, _need_resp);
	SetCmdParam(cmd_t,_need_resp);
	return cmd_t;
}
/*-----------------------------------*/
/**
 *申请命令空间，并设置命令头和命令控制数据实体长度
 */
/*-----------------------------------*/
CMD_CTRL* CreateCmdCtrl(int body_size)
{
	CMD_CTRL*  cmd_t=mem_malloc(sizeof(CMD_CTRL));

	if(cmd_t!=NULL){

#if 0
		bzero(cmd_t,sizeof(CMD_CTRL));
#endif
		cmd_t->f_header.f_header[0]='Y';
		cmd_t->f_header.f_header[1]='j';
		cmd_t->f_header.f_header[2]='k';
		cmd_t->f_header.f_header[3]='j';
		cmd_t->f_data=NULL;
		cmd_t->f_data_size=0;
		CreateCmdBody(cmd_t,body_size);  //设置命令实体控制数据长度，并申请空间
		if(cmd_t->f_data!=NULL){

		}else{
			ReleaseCmdCtrl(&cmd_t);  //释放命令空间
		}

	}



	return cmd_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsCmdCtrlHeader(const CMD_CTRL* cmd_t)
{
	if(	cmd_t->f_header.f_header[0]=='Y' &&
		cmd_t->f_header.f_header[1]=='j' &&
		cmd_t->f_header.f_header[2]=='k' &&
		cmd_t->f_header.f_header[3]=='j' ){
					return TRUE;
	}
	return FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsCmdCtrl(const CMD_CTRL* cmd_t)
{

	if(IsCmdCtrlHeader(cmd_t) ){
					if(MemPoolAddrZone(cmd_t)!=-1){

								if(MemPoolAddrZone(cmd_t->f_data)!=-1){

											return TRUE;
								}
					}
	}
	return FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ReleaseCmdCtrlEx(CMD_CTRL** _cmd_ctrl)
{
	if(IsCmdCtrlHeader(*_cmd_ctrl))
	{
		ReleaseCmdCtrl(_cmd_ctrl);
	}

}
/*-----------------------------------*/
/**
 * 释放命令空间
 */
/*-----------------------------------*/
void ReleaseCmdCtrl(CMD_CTRL** _cmd_ctrl)
{
	if(*_cmd_ctrl){
			FreeCmdBody(*_cmd_ctrl);  //释放命令控制数据实体空间
			mem_free_clr((void**)_cmd_ctrl);  //释放命令空间

	}
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void initRespCmd(CMD_CTRL* cmd,int _ok)
{
	assert(CT_OK == _ok || CT_ERROR == _ok);

	cmd->f_header.f_cmd[0]=CT_RESP;
	cmd->f_header.f_cmd[1]=_ok;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int SendRespCmd(int _socketfd,int _ok,const unsigned int _body)
{
	CMD_CTRL* cmd=CreateCmdCtrl(0);

	initRespCmd(cmd,_ok);

	SetCmdParam(cmd,_body);

	return socket_write_1_cmd_release(_socketfd,cmd);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int SendHeartbeatCmd(
		const int _socketfd,
		const unsigned int _need_resp,
		const int _seq)
{

	CMD_CTRL* cmd=CreateImageHeartbeat(0,_need_resp,_seq);

	return socket_write_1_cmd_release(_socketfd,cmd);


}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int SendHeartbeatCmd_TimeCost(
		const int 	_socketfd,
		int*	_status,
		const int 	_need_resp,
		const int 	_seq,
		const char* _msg)
{
	assert(_status!=NULL);
	*_status=FALSE;
	TIME_START();
	*_status=SendHeartbeatCmd(_socketfd,_need_resp,_seq);
	TIME_END(_msg);
	return *_status;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsCmdCtrl_Debug(const CMD_CTRL* _cmd,const char* msg)
{

	const int result_t=IsCmdCtrl(_cmd);

#ifdef _DEBUG
	if(result_t==FALSE){
		PRINTF_DBG_EX(msg);
	}
#endif

return result_t;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
