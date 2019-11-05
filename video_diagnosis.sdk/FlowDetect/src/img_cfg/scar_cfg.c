#include "scar_cfg.h"
/*-----------------------------------*/
static SCAR_PARAM  G_SCAR_PARAM={
		0,
		1,
		2,
		3,
		4,
		5,
		6,
		0,
		1};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarCurrentMask(
		const int* 	_mask_seq,
		const int	_num)
{
	memcpy(G_SCAR_PARAM.current_mask_seq,_mask_seq,_num);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarCurrentMask_Cmd(const CMD_CTRL* const  _cmd)
{
	const int UCHAR_SIZE=8;

	const IplImageU * imgU=GetIplImageUx(_cmd);

	const int CmdParam_t=GetCmdParam(_cmd);


	const int seq_num	=	GetMaskSeqNum(_cmd);
	const int* seq_ptr	=	GetMaskSeqPtr(_cmd);

	SetScarCurrentMask(seq_ptr,seq_num);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarWorkMode()
{
	return G_SCAR_PARAM.work_mode;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarGlobalThresholdUp()
{
	return G_SCAR_PARAM.global_th_up;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarGlobalThresholdDown()
{
	return G_SCAR_PARAM.global_th_down;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarRowThresholdUp()
{
	return G_SCAR_PARAM.row_th_up;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarRowThresholdDown()
{
	return G_SCAR_PARAM.row_th_down;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarColThresholdUp()
{
	return G_SCAR_PARAM.col_th_up;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarColThresholdDown()
{
	return G_SCAR_PARAM.col_th_down;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarWorkMode(const int _th)
{
	G_SCAR_PARAM.work_mode=_th;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarGlobalThresholdUp(const int _th)
{
	G_SCAR_PARAM.global_th_up=_th;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarGlobalThresholdDown(const int _th)
{
	G_SCAR_PARAM.global_th_down=_th;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarRowThresholdUp(const int _th)
{
	G_SCAR_PARAM.row_th_up=_th;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarRowThresholdDown(const int _th)
{
	G_SCAR_PARAM.row_th_down=_th;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarColThresholdUp(const int _th)
{
	G_SCAR_PARAM.col_th_up=_th;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarColThresholdDown(const int _th)
{
	G_SCAR_PARAM.col_th_down=_th;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarWorkMode2FPGA(const int _th)
{
	SetScarWorkMode(_th);
	fpga_img_scar_detect_mode(_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarGlobalThresholdUp2FPGA(const int _th)
{
	SetScarGlobalThresholdUp(_th);
	fpga_img_scar_detect_set_g_th_up(_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarGlobalThresholdDown2FPGA(const int _th)
{
	SetScarGlobalThresholdDown(_th);
	fpga_img_scar_detect_set_g_th_down(_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarRowThresholdUp2FPGA(const int _th)
{
	SetScarRowThresholdUp(_th);
	fpga_img_scar_detect_set_row_th_up(_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarRowThresholdDown2FPGA(const int _th)
{
	SetScarRowThresholdDown(_th);
	fpga_img_scar_detect_set_row_th_down(_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarColThresholdUp2FPGA(const int _th)
{
	SetScarColThresholdUp(_th);
	fpga_img_scar_detect_set_col_th_up(_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarColThresholdDown2FPGA(const int _th)
{
	SetScarColThresholdDown(_th);
	fpga_img_scar_detect_set_col_th_down(_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetMaskChannel(const int _idx)
{
	return G_SCAR_PARAM.current_mask_seq[_idx];
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
