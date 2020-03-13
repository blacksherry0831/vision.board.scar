#include "img_cfg_scar.h"
/*-----------------------------------*/
/*
 *dma �����ɰ�ͼƬ ͬ��
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
 *�ж��ɰ������Ƿ�Ƿ�
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
 *���ܣ���ʼ���ɰ��ļ���
 *�������ļ��������ߣ��ɰ��
 */
/*-----------------------------------*/
void SetMaskImageFileName_space_frame_scar(
		char* _filename,
		const int _w,
		const int _h,
		const int _mask_pos)
{
	const int ch_space=GetSpaceIdx_Scar(_mask_pos);  //��ȡ�ɰ�ռ��ַ��� ��
	const int ch_frame=GetFrameIdx_Scar(_mask_pos);  //��ȡ�ɰ�֡����� ��

	char path_cfg[1024]={0};
	initProjectCfgDirPath_Separator(path_cfg); //��ȡĿ�����ļ�Ŀ¼��/media/sdcard/project.cfg./��Ŀ����ģʽ/

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
 *��ʼ�������ɰ��ļ���
 */
/*-----------------------------------*/
void SetMaskImageFileName_cmd_ctrl(
		char* _filename,
		const CMD_CTRL* const  _cmd)
{
	const int UCHAR_SIZE=8;
	const IplImageU * imgU=GetIplImageUx(_cmd);

	const int mask_pos=UChar2Int(imgU->IpAddrChannel,UCHAR_SIZE);  //�ɰ��
	const int width=UChar2Int(imgU->width,UCHAR_SIZE);  //��
	const int height=UChar2Int(imgU->height,UCHAR_SIZE);  //��
	SetMaskImageFileName_space_frame_scar(
			_filename,
			width,
			height,
			mask_pos);  //��ʼ���ɰ��ļ���
}
/*-----------------------------------*/
/**
 *�����ɰ�ͼƬ
 */
/*-----------------------------------*/
void SaveImgMaskMatrix_Scar(const CMD_CTRL* const  _cmd)
{
	char filename_t[1024];
	SetMaskImageFileName_cmd_ctrl(filename_t,_cmd);  //��ʼ�������ɰ��ļ���
	encodeWithState_cmd_ctrl(filename_t,_cmd);  //��cmd�е�image�����pngͼƬ������
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
 *��ȡ�ѱ�����sd���е��ɰ�ͼƬ��cmd
 */
/*-----------------------------------*/
int ReadImgMaskMatrix_Scar(const CMD_CTRL* _cmd)
{
		char filename_t[1024]={0};
		SetMaskImageFileName_cmd_ctrl(filename_t,_cmd);  //��ʼ�������ɰ��ļ���

		if(SUCCESS==fs_is_file_exist(filename_t)){
				return decodeWithState_cmd_ctrl(filename_t,_cmd);  //����pngͼƬΪ�������ݣ���������cmd��
		}else{
				return FALSE;
		}
}
/*-----------------------------------*/
/**
 *��ȡ�ѱ�����sd���е��ɰ�ͼƬ������dma���ݽ���
 */
/*-----------------------------------*/
void Read_And_Dma_ImageMask_Scar(CMD_CTRL*  _cmd)
{
	if(IsImgMaskValid_Scar(_cmd)){

			if(ReadImgMaskMatrix_Scar(_cmd)){  //��ȡ�ѱ�����sd���е��ɰ�ͼƬ��cmd
				dmac_83c1_trans_mask_img_cmd_ctrl_sync(_cmd);  //dma �����ɰ�ͼƬ ͬ��
			}

	}
}
/*-----------------------------------*/
/**
 *�ɰ�ͼƬ�ı����dma���ݽ���
 */
/*-----------------------------------*/
void Save_And_Dma_ImageMask_Scar(CMD_CTRL*  _cmd)
{
	if(IsImgMaskValid_Scar(_cmd)){  //�ж��ɰ������Ƿ�Ƿ�
			SaveImgMaskMatrix_Scar(_cmd); //�����ɰ�ͼƬ
			dmac_83c1_trans_mask_img_cmd_ctrl_sync(_cmd);  //dma �����ɰ�ͼƬ
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
 *��������ʼ��_ch���ɰ�ͼƬ����
 */
/*-----------------------------------*/
CMD_CTRL* CreateImageMaskCh_Scar(const int _ch)
{
	const int  w=1920;
	const int  h=1080;
	const unsigned int seq=0;

	CMD_CTRL*  cmd_t=CreateImageMask_Scar(_ch,w,h,seq);  //��������ʼ���ɰ�ͼƬ����

	return cmd_t;

}
/*-----------------------------------*/
/**
 *��������ʼ��0��ͨ���ɰ�ͼƬ�����ͼƬ�������Ϊ0xff
 */
/*-----------------------------------*/
CMD_CTRL* CreateImageMaskCh_Scar_0()
{

	CMD_CTRL*  cmd_t=CreateImageMaskCh_Scar(0);  //��������ʼ��0��ͨ���ɰ�ͼƬ����

	FillImageCtrl(cmd_t,0xff);  //���ͼƬ�������� Ϊ0xff

	return cmd_t;

}
/*-----------------------------------*/
/**
 *��ʼ��0���ɰ壬�����к�dma���ݽ���
 */
/*-----------------------------------*/
void  InitMaskImage_scar_0()
{

	CMD_CTRL* _mask_img_0=CreateImageMaskCh_Scar_0();  //��������ʼ��0���ɰ�ͼƬ�����ͼƬ�������Ϊ0xff

	Save_And_Dma_ImageMask_Scar(_mask_img_0);  //0���ɰ�ͼƬ�ı����dma���ݽ���

	ReleaseCmdCtrl(&_mask_img_0);  //�ͷ�����ռ�

}
/*-----------------------------------*/
/**
 *��ȡ�ѱ�����sd���е��ɰ�ͼƬ������dma���ݽ���
 */
/*-----------------------------------*/
void InitMaskImage_scar_0_N()
{

	TIME_START();

	int mi=0;
	const int mask_max=SCAR_IMG_MASK_SQE_MAX;

	for(mi=0;mi<mask_max;mi++){

		CMD_CTRL* mask_img_x=CreateImageMaskCh_Scar(mi);  //��������ʼ��mi���ɰ�ͼƬ����
		Read_And_Dma_ImageMask_Scar(mask_img_x);  //��ȡ�ѱ�����sd���е��ɰ�ͼƬ������dma���ݽ���
		ReleaseCmdCtrl(&mask_img_x);  //�ͷ�����ռ�

	}

	TIME_END("init scar image mask cost time:");
}
/*-----------------------------------*/
/**
 *��ʼ��0�ź��ѱ�����sd���е��ɰ����ݣ�������dma���ݽ���
 */
/*-----------------------------------*/
void  InitMaskImage_scar()
{
	InitMaskImage_scar_0();  //��ʼ��0���ɰ壬�����к�dma���ݽ���
	InitMaskImage_scar_0_N();  //��ȡ�ѱ�����sd���е��ɰ�ͼƬ������dma���ݽ���
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
