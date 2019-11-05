#include "cmd_scar.h"
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
int IsImageScarSet_SelectMask(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_MASK_SELECT_SCAR);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetMaskSeqNum(const CMD_CTRL* const _cmd_ctrl)
{
	assert(_cmd_ctrl->f_data_size>=2);

	unsigned char* data_t=_cmd_ctrl->f_data;

	const int param=UChar2Int(data_t,4);

	return param;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int* GetMaskSeqPtr(const CMD_CTRL* const _cmd_ctrl)
{
	assert(_cmd_ctrl->f_data_size>=2);

	unsigned int* data_t=(unsigned int*)_cmd_ctrl->f_data;

	return data_t[1];
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
