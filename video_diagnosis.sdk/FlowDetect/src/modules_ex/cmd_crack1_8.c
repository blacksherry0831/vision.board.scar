#include "cmd_crack1_8.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageCrack_Set_Frame_Min(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_SEQ_FRAME_MIN);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageCrack_Query_Frame_Min(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_QUERY,CT_IMG_SEQ_FRAME_MIN);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageCrack_Set_Frame_Max(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_SEQ_FRAME_MAX);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageCrack_Query_Frame_Max(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_QUERY,CT_IMG_SEQ_FRAME_MAX);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageCrack_Set_out_1st_circle_frames(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_IMG,CT_IMG_OUTSIDE_FIRST_FRAME_NUM);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsImageCrack_Query_out_1st_circle_frames(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_QUERY,CT_IMG_OUTSIDE_FIRST_FRAME_NUM);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
