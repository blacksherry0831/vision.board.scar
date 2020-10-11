#include "cmd_scar.h"
/*-----------------------------------*/
#define MASK_SEQ_SNO_OFFSET			(0)
#define MASK_SEQ_NUM_OFFSET			(1)
#define MASK_SEQ_LOOP_OFFSET		(2)
#define MASK_SEQ_MONTAGE_OFFSET		(3)
#define MASK_SEQ_DATA_OFFSET		(4)
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageScarSet_GlobalSigmaUp(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_SCAR_GLOBAL_SIGMA_UP);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageScarQuery_GlobalSigmaUp(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_SCAR_GLOBAL_SIGMA_UP);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageScarSet_GlobalSigmaDown(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_SCAR_GLOBAL_SIGMA_DOWN);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageScarQuery_GlobalSigmaDown(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_SCAR_GLOBAL_SIGMA_DOWN);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageScarSet_RowSigmaUp(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_SCAR_ROW_SIGMA_UP);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageScarQuery_RowSigmaUp(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_SCAR_ROW_SIGMA_UP);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageScarSet_RowSigmaDown(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_SCAR_ROW_SIGMA_DOWN);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageScarQuery_RowSigmaDown(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_SCAR_ROW_SIGMA_DOWN);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageScarSet_ColSigmaUp(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_SCAR_COL_SIGMA_UP);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageScarQuery_ColSigmaUp(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_SCAR_COL_SIGMA_UP);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageScarSet_ColSigmaDown(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_SCAR_COL_SIGMA_DOWN);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageScarQuery_ColSigmaDown(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_SCAR_COL_SIGMA_DOWN);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageScarSet_WorkMode(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_MODE_SCAR);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageScarSet_Mask(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_MASK_SET_SCAR);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageScarClear_Mask(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_MASK_CLEAR_SCAR);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageScarSet_SelectMask(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_MASK_SELECT_SCAR);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int ParseMaskSeq_MaskImgNumber(const CMD_CTRL* const _cmd_ctrl)
{
	assert(_cmd_ctrl->f_data_size>=2);

	int* data_t=(int*) _cmd_ctrl->f_data;

	const int param=UChar2Int((unsigned char*) (data_t+MASK_SEQ_NUM_OFFSET),4);

	return param;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int ParseMaskSeq_SerialNumber(const CMD_CTRL* const _cmd_ctrl)
{
	assert(_cmd_ctrl->f_data_size>=2);

	int* data_t=(int*) _cmd_ctrl->f_data;

	const int param=UChar2Int((unsigned char*) (data_t+MASK_SEQ_SNO_OFFSET),4);

	return param;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int ParseMaskSeq_Loop(const CMD_CTRL* const _cmd_ctrl)
{
	assert(_cmd_ctrl->f_data_size>=2);

	int* data_t=(int*) _cmd_ctrl->f_data;

	const int param=UChar2Int((unsigned char*) (data_t+MASK_SEQ_LOOP_OFFSET),4);

	return param;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int ParseMaskSeq_Montage(const CMD_CTRL* const _cmd_ctrl)
{
	assert(_cmd_ctrl->f_data_size>=2);

	int* data_t=(int*) _cmd_ctrl->f_data;

	const int param=UChar2Int((unsigned char*) (data_t+MASK_SEQ_MONTAGE_OFFSET),4);

	return param;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int* ParseMaskSeq_Ptr(const CMD_CTRL* const _cmd_ctrl)
{
	assert(_cmd_ctrl->f_data_size>=2);

	unsigned int* data_t=(unsigned int*)_cmd_ctrl->f_data;

	return &data_t[MASK_SEQ_DATA_OFFSET];
}
/*-----------------------------------*/
/**
 *创建并初始化蒙板图片命令
 */
/*-----------------------------------*/
CMD_CTRL* CreateImageMask_Scar(const int _ch,const int _w,const int _h,unsigned int _seq)
{
	const int nChs=1;
	CMD_CTRL*  cmd_t=CreateImageCtrl(_ch,FRAME_IDX_TYPE_START,_w,_h,nChs,_seq);//4 byte align  创建并初始化图片命令（cmd_ctrl）
	SetImageCmd(cmd_t,CT_IMG_MASK_SET_SCAR);  //将此图片命令设为蒙板命令
	return cmd_t;
}
/*-----------------------------------*/
/**
 *@brief   start a mask seq to start fpga convert
 */
/*-----------------------------------*/
CMD_CTRL* CreateImageStart_Scar_DetectSno(
		const int _ch,
		const int _frame,
		const int _sno,
		const unsigned int _seq)
{
	const int nChs=1;
	const int w=4*(1+_sno);
	const int h=4;

	assert(_ch>=0);
	assert(_frame>0);
	assert(_sno>=0);

	CMD_CTRL*  cmd_t=CreateImageCtrl(_ch,_frame,w%1920,h%1080,nChs,_seq);//4 byte align
	SetImageCmd(cmd_t,CT_IMG_MASK_DETECT_START_SCAR);
	return cmd_t;
}
/*-----------------------------------*/
/**
*   判断工件是否就绪 && 判断是否为检测序列开始命令
*/
/*-----------------------------------*/
int IsImgDetStart(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_MASK_DETECT_START_SCAR);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
