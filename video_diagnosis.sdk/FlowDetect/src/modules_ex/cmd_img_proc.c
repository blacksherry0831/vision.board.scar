/*
 * cmd_img_proc.c
 *
 *  Created on: 2020Äê4ÔÂ10ÈÕ
 *      Author: yjkj909
 */

#include "cmd_img_proc.h"

int IsBinarySetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_IS_BINARY_SET);
}

int IsDenoiseSetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_IS_DENOISE_SET);
}

int IsBlackSkinSetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_IS_BLACKSKIN_SET);
}
int IsHoughSetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_IS_HOUGH_SET);
}

int IsMorphologySetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_IS_MORPHOLOGY_SET);
}

int IsShowResultSetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_IS_RESULT_SHOW_SET);
}

int IsBlackSkinMinAreaSetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_BLACK_SKIN_MIN_AREA_SET);
}

int IsHoughThresoldSetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_HOUGH_THRESOLD_SET);
}

int IsHoughMinLengthSetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_HOUGH_MIN_LENGTH_SET);
}

int IsHoughMaxGapSetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_HOUGH_MAX_GAP_SET);
}

int IsHoughMaxAngleSetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_HOUGH_MAX_ANGEL_SET);
}

int IsCrackMinAreaSetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_MORPHOLOGY_MIN_AREA_SET);
}

int IsCrackAspectRatioSetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_MORPHOLOGY_ASPECT_RATIO_SET);
}

int IsCrackAreaRatioSetCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_MORPHOLOGY_AREA_RATIO_SET);
}

int IsBinaryQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_IS_BINARY_QUERY);
}

int IsDenoiseQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_IS_DENOISE_QUERY);
}

int IsBlackSkinQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_IS_BLACKSKIN_QUERY);
}

int IsHoughQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_IS_HOUGH_QUERY);
}

int IsMorphologyQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_IS_MORPHOLOGY_QUERY);
}

int IsShowResultQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_IS_RESULT_SHOW_QUERY);
}

int IsBlackSkinMinAreaQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_BLACK_SKIN_MIN_AREA_QUERY);
}

int IsHoughThresoldQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_HOUGH_THRESOLD_QUERY);
}

int IsHoughMinLengthQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_HOUGH_MIN_LENGTH_QUERY);
}

int IsHoughMaxGapQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_HOUGH_MAX_GAP_QUERY);
}

int IsHoughMaxAngleQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_HOUGH_MAX_ANGEL_QUERY);
}

int IsCrackMinAreaQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_MORPHOLOGY_MIN_AREA_QUERY);
}

int IsCrackAspectRatioQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_MORPHOLOGY_ASPECT_RATIO_QUERY);
}

int IsCrackAreaRatioQueryCmd(const CMD_CTRL* _cmd_ctrl)
{
	return IsCmdCtrlCmd(_cmd_ctrl,CT_ARM_IMG_PROC,CT_MORPHOLOGY_AREA_RATIO_QUERY);
}

