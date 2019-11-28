#include "img_cfg_scar.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImgMaskValid_Scar(const CMD_CTRL* const  _cmd)
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
void SetMaskImageFileName_space_frame_scar(
		char* _filename,
		const int _w,
		const int _h,
		const int _mask_pos)
{
	const int ch_space=GetSpaceIdx_Scar(_mask_pos);
	const int ch_frame=GetFrameIdx_Scar(_mask_pos);

	char path_cfg[1024]={0};
	initProjectCfgDirPath_Separator(path_cfg);

	assert(ch_space<SCAR_IMG_MASK_CHANNEL_MAX);
	assert(ch_frame<SCAR_IMG_MASK_FRAME_MAX);
	sprintf(_filename,
			"%sw.%d.h.%d.mask.idx.%d.s.%d.f.%d.png",
			path_cfg,
			_w,
			_h,
			_mask_pos,
			ch_space,
			ch_frame);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetMaskImageFileName_cmd_ctrl(
		char* _filename,
		const CMD_CTRL* const  _cmd)
{
	const int UCHAR_SIZE=8;
	const IplImageU * imgU=GetIplImageUx(_cmd);

	const int mask_pos=UChar2Int(imgU->IpAddrChannel,UCHAR_SIZE);
	const int width=UChar2Int(imgU->width,UCHAR_SIZE);
	const int height=UChar2Int(imgU->height,UCHAR_SIZE);
	SetMaskImageFileName_space_frame_scar(
			_filename,
			width,
			height,
			mask_pos);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SaveImgMaskMatrix_Scar(const CMD_CTRL* const  _cmd)
{
	char filename_t[1024];
	SetMaskImageFileName_cmd_ctrl(filename_t,_cmd);
	encodeWithState_cmd_ctrl(filename_t,_cmd);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void DeleteImgMaskMatrix_Scar(const CMD_CTRL* const  _cmd)
{
	char filename_t[1024];
	SetMaskImageFileName_cmd_ctrl(filename_t,_cmd);
	remove(filename_t);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int ReadImgMaskMatrix_Scar(const CMD_CTRL* _cmd)
{
		char filename_t[1024]={0};
		SetMaskImageFileName_cmd_ctrl(filename_t,_cmd);

		if(SUCCESS==fs_is_file_exist(filename_t)){
				return decodeWithState_cmd_ctrl(filename_t,_cmd);
		}else{
				return FALSE;
		}
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void Read_And_Dma_ImageMask_Scar(CMD_CTRL*  _cmd)
{
	if(IsImgMaskValid_Scar(_cmd)){

			if(ReadImgMaskMatrix_Scar(_cmd)){
				dmac_83c1_trans_mask_img_cmd_ctrl(_cmd);
			}

	}
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void Save_And_Dma_ImageMask_Scar(CMD_CTRL*  _cmd)
{
	if(IsImgMaskValid_Scar(_cmd)){
			SaveImgMaskMatrix_Scar(_cmd);
			dmac_83c1_trans_mask_img_cmd_ctrl(_cmd);
	}
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void Clear_And_Dma_ImageMask_Scar(CMD_CTRL*  _cmd)
{
	if(IsImgMaskValid_Scar(_cmd)){
			DeleteImgMaskMatrix_Scar(_cmd);
			dmac_83c1_trans_mask_img_cmd_ctrl(_cmd);
	}
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CMD_CTRL* CreateImageMaskCh_Scar(const int _ch)
{
	const int  w=1920;
	const int  h=1080;
	const unsigned int seq=0;

	CMD_CTRL*  cmd_t=CreateImageMask_Scar(_ch,w,h,seq);

	return cmd_t;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
CMD_CTRL* CreateImageMaskCh_Scar_0()
{

	CMD_CTRL*  cmd_t=CreateImageMaskCh_Scar(0);

	FillImageCtrl(cmd_t,0xff);

	return cmd_t;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void  InitMaskImage_scar_0()
{

	CMD_CTRL* _mask_img_0=CreateImageMaskCh_Scar_0();

	Save_And_Dma_ImageMask_Scar(_mask_img_0);

	ReleaseCmdCtrl(&_mask_img_0);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void InitMaskImage_scar_0_N()
{

	TIME_START();

	int mi=0;
	const int mask_max=SCAR_IMG_MASK_SQE_MAX;

	for(mi=0;mi<mask_max;mi++){

		CMD_CTRL* mask_img_x=CreateImageMaskCh_Scar(mi);
		Read_And_Dma_ImageMask_Scar(mask_img_x);
		ReleaseCmdCtrl(&mask_img_x);

	}

	TIME_END("init scar image mask cost time:");
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void  InitMaskImage_scar()
{
	InitMaskImage_scar_0();
	InitMaskImage_scar_0_N();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void sendImageStart_DetectSno(
		const int _frame_total,
		const int _sno)
{
		int schi=0;
		int sfri=0;

			for(schi=0; schi <SPACE_CHANNEL_NUM;schi++){
				for(sfri=0;sfri<SPACE_FRAME_NUM;sfri++){

						if(is_space_frame_output(schi,sfri)){

										const int View_channel=image_view_channel(schi,sfri);
										assert(View_channel>=0);
										const unsigned int seq_t=GetFrameCircleSeq();
										snd_queue_img_buff(CreateImageStart_Scar_DetectSno(View_channel,_frame_total,_sno,seq_t));

						}
				}
			}


}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
