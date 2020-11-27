#ifndef IMG_CFG_H
#define IMG_CFG_H
/*-----------------------------------*/
#include "linux_header.h"
#include "cfg.h"
/*-----------------------------------*/
#include "modules_ex/type.h"
/*-----------------------------------*/
#include <opencv2/core/types_c.h>
/*-----------------------------------*/
#include <modules_up/png_up.h>
/*-----------------------------------*/
#include "modules/cJSON/cJSON.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/def_hw_zynq7000_hi3516.h"
/*-----------------------------------*/
#include "scar_cfg.h"
/*-----------------------------------*/
#include "modules_ex/def_work_mode.h"

#include "sync/sync_task.h"
#include "modules_ex/type.h"
#include "img_cfg/img_cfg.h"
#include "status.h"
#include "flame_monitor.h"
#include "img_proc/img_proc.h"
/*-----------------------------------*/
struct ViewInfo{

	int SpaceCh;/**<*/
	int SpaceFrame;/**<*/
	int SpaceUsed;/**<space reserve*/

	int ViewCh;/**video  channel<*/
	int ViewOutput;/**< output this video */
	int nChannels;/**<*/
	int ImageMask;
	CvRect CutSize;/**<*/
	CvRect OrgSize;/**<*/
	char colorModel[64];/**<*/
	float Intrinsics[3][3];
	float Distortion[5][1];
};
/*-----------------------------------*/
extern const size_t IMAGE_SIZE_FRAME;
extern const size_t IMAGE_SIZE_AVG;
extern const size_t CHANNEL_BLOCK_SIZE;
extern const size_t CHANNELS;
/*-----------------------------------*/
CMD_CTRL* CreateImageCtrlLocal(int _ch,int _frame, int _seq);

void  MallocImageBuff(CMD_CTRL** _buff,const int _frame,const int _Chs);
/*-----------------------------------*/
void  SetRectCutCmd(CMD_CTRL*  cmd_t);
void  ClearRectCut();
/*-----------------------------------*/
void SaveImgMaskMatrix(const CMD_CTRL* const  _cmd);
/*-----------------------------------*/
void init_image_cfg(const int _width,const int _height);
/*-----------------------------------*/
unsigned int image_frame_dma_offset(const int _space_ch,const int _space_frame);
char* image_view_colorModel(int _space_ch,int _space_frame);
/*-----------------------------------*/
int image_width(int _space_ch,int _space_frame);
int image_height(int _space_ch,int _space_frame);
int image_nchannels(int _space_ch,int _space_frame);
int image_frame_size(int _space_ch,int _space_frame);
/*-----------------------------------*/
int IsImgMaskValid(const CMD_CTRL* const  _cmd);
int is_space_frame_output(const int _space_ch,const int _space_fr);
/*-----------------------------------*/
void 	set_img_cut_rect(const CvRect _cut,const int _ViewCh);
/*-----------------------------------*/
CvRect 	GetRectSpaceChannelFrame(const int _si,const int _fi);
/*-----------------------------------*/
void saveImgCfgJsonDefault();
void LoadImgCfgJson();
/*-----------------------------------*/
int GetMaskChannel_Number();
/*-----------------------------------*/

int img_space_frame_output_num();

void  MallocImageBuff4ViewOutput(
		CMD_CTRL** _buff,
		const int _seq,
		const char* _prj,
		const int _total,
		const int _idx);

void StoreImgCfgJson();

int image_view_channel(int _space_ch,int _space_frame);
int ReadImgMaskMatrix(const CMD_CTRL* _cmd);
unsigned int image_frame_fpga_ps_offset(const int _space_ch,const int _space_frame);
void image_enable_output_frame_only_1();
void image_enable_output_frame_only_2();
void CopyImage(void* const buff_src,CMD_CTRL* img_dst,const  int _space_ch,const int _space_fr);
void initViewInfo_basic(const int _width,const int _height,const int _space_frame);

#endif
