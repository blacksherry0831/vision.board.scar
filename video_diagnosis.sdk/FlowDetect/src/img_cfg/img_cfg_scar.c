#include "img_cfg_scar.h"
/*-----------------------------------*/
/*
 *dma 交换蒙板图片 同步
 */
/*-----------------------------------*/
void dmac_83c1_trans_mask_img_cmd_ctrl_sync(CMD_CTRL*  _cmd)
{

	if(SUCCESS==PL_MEM_48_Lock()){
		if(SUCCESS==PS_MEM_04_Lock()){
			TIME_START();

			dmac_83c1_trans_mask_img_cmd_ctrl(_cmd);

			TIME_END("DMA83c1 mask image ");

			if(SUCCESS==PS_MEM_04_Unlock()){

			}
		}
		if(SUCCESS==PL_MEM_48_Unlock()){

		}

	}

}
/*-----------------------------------*/
/**
 *判断蒙板命令是否非法
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
 *功能：初始化蒙板文件名
 *参数：文件名，宽，高，蒙版号
 */
/*-----------------------------------*/
void SetMaskImageFileName_space_frame_scar(
		char* _filename,
		const int _w,
		const int _h,
		const int _mask_pos)
{
	const int ch_space=GetSpaceIdx_Scar(_mask_pos);  //获取蒙板空间地址序号 ？
	const int ch_frame=GetFrameIdx_Scar(_mask_pos);  //获取蒙板帧数序号 ？

	char path_cfg[1024]={0};
	initProjectCfgDirPath_Separator(path_cfg); //获取目配置文件目录：/media/sdcard/project.cfg./项目运行模式/

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
 *初始化设置蒙板文件名
 */
/*-----------------------------------*/
void SetMaskImageFileName_cmd_ctrl(
		char* _filename,
		const CMD_CTRL* const  _cmd)
{
	const int UCHAR_SIZE=8;
	const IplImageU * imgU=GetIplImageUx(_cmd);

	const int mask_pos=UChar2Int(imgU->IpAddrChannel,UCHAR_SIZE);  //蒙板号
	const int width=UChar2Int(imgU->width,UCHAR_SIZE);  //宽
	const int height=UChar2Int(imgU->height,UCHAR_SIZE);  //高
	SetMaskImageFileName_space_frame_scar(
			_filename,
			width,
			height,
			mask_pos);  //初始化蒙板文件名
}
/*-----------------------------------*/
/**
 *保存蒙版图片
 */
/*-----------------------------------*/
void SaveImgMaskMatrix_Scar(const CMD_CTRL* const  _cmd)
{
	char filename_t[1024];
	SetMaskImageFileName_cmd_ctrl(filename_t,_cmd);  //初始化设置蒙板文件名
	encodeWithState_cmd_ctrl(filename_t,_cmd);  //将cmd中的image编码成png图片并保存
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
 *读取已保存在sd卡中的蒙板图片至cmd
 */
/*-----------------------------------*/
int ReadImgMaskMatrix_Scar(const CMD_CTRL* _cmd)
{
		char filename_t[1024]={0};
		SetMaskImageFileName_cmd_ctrl(filename_t,_cmd);  //初始化设置蒙板文件名

		if(SUCCESS==fs_is_file_exist(filename_t)){
				return decodeWithState_cmd_ctrl(filename_t,_cmd);  //解码png图片为像素数据，并保存至cmd中
		}else{
				return FALSE;
		}
}
/*-----------------------------------*/
/**
 *读取已保存在sd卡中的蒙板图片并进行dma数据交互
 */
/*-----------------------------------*/
void Read_And_Dma_ImageMask_Scar(CMD_CTRL*  _cmd)
{
	if(IsImgMaskValid_Scar(_cmd)){

			if(ReadImgMaskMatrix_Scar(_cmd)){  //读取已保存在sd卡中的蒙板图片至cmd
				dmac_83c1_trans_mask_img_cmd_ctrl_sync(_cmd);  //dma 交换蒙板图片 同步
			}

	}
}
/*-----------------------------------*/
/**
 *蒙板图片的保存和dma数据交互
 */
/*-----------------------------------*/
void Save_And_Dma_ImageMask_Scar(CMD_CTRL*  _cmd)
{
	if(IsImgMaskValid_Scar(_cmd)){  //判断蒙板命令是否非法
			SaveImgMaskMatrix_Scar(_cmd); //保存蒙版图片
			dmac_83c1_trans_mask_img_cmd_ctrl_sync(_cmd);  //dma 交换蒙板图片
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
			dmac_83c1_trans_mask_img_cmd_ctrl_sync(_cmd);
	}
}
/*-----------------------------------*/
/**
 *创建并初始化_ch号蒙板图片命令
 */
/*-----------------------------------*/
CMD_CTRL* CreateImageMaskCh_Scar(const int _ch)
{
	const int  w=1920;
	const int  h=1080;
	const unsigned int seq=0;

	CMD_CTRL*  cmd_t=CreateImageMask_Scar(_ch,w,h,seq);  //创建并初始化蒙板图片命令

	return cmd_t;

}
/*-----------------------------------*/
/**
 *创建并初始化0号通道蒙板图片命令并将图片内容填充为0xff
 */
/*-----------------------------------*/
CMD_CTRL* CreateImageMaskCh_Scar_0()
{

	CMD_CTRL*  cmd_t=CreateImageMaskCh_Scar(0);  //创建并初始化0号通道蒙板图片命令

	FillImageCtrl(cmd_t,0xff);  //填充图片内容数据 为0xff

	return cmd_t;

}
/*-----------------------------------*/
/**
 *初始化0号蒙板，并进行和dma数据交互
 */
/*-----------------------------------*/
void  InitMaskImage_scar_0()
{

	CMD_CTRL* _mask_img_0=CreateImageMaskCh_Scar_0();  //创建并初始化0号蒙板图片命令并将图片内容填充为0xff

	Save_And_Dma_ImageMask_Scar(_mask_img_0);  //0号蒙板图片的保存和dma数据交互

	ReleaseCmdCtrl(&_mask_img_0);  //释放命令空间

}
/*-----------------------------------*/
/**
 *读取已保存在sd卡中的蒙板图片并进行dma数据交互
 */
/*-----------------------------------*/
void InitMaskImage_scar_0_N()
{

	TIME_START();

	int mi=0;
	const int mask_max=SCAR_IMG_MASK_SQE_MAX;

	for(mi=0;mi<mask_max;mi++){

		CMD_CTRL* mask_img_x=CreateImageMaskCh_Scar(mi);  //创建并初始化mi号蒙板图片命令
		Read_And_Dma_ImageMask_Scar(mask_img_x);  //读取已保存在sd卡中的蒙板图片并进行dma数据交互
		ReleaseCmdCtrl(&mask_img_x);  //释放命令空间

	}

	TIME_END("init scar image mask cost time:");
}
/*-----------------------------------*/
/**
 *初始化0号和已保存在sd卡中的蒙板数据，并进行dma数据交互
 */
/*-----------------------------------*/
void  InitMaskImage_scar()
{
	InitMaskImage_scar_0();  //初始化0号蒙板，并进行和dma数据交互
	InitMaskImage_scar_0_N();  //读取已保存在sd卡中的蒙板图片并进行dma数据交互
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
