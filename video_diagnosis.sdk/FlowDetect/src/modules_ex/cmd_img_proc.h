/*
 * cmd_img_proc.h
 *
 *  Created on: 2020年4月10日
 *      Author: yjkj909
 */

#ifndef CMD_IMG_PROC_H_
#define CMD_IMG_PROC_H_

#include "type.h"

//控制命令
enum CMD_TYPE_00_IMG_PROC {

	CT_ARM_IMG_PROC = 'A',  //arm图像处理相关参数

};

//ARM图像处理-控制命令“A” 补充
enum CMD_TYPE_02_A {
	CT_IS_BINARY_SET = 0x11,  //是否进行二值化-设置
	CT_IS_DENOISE_SET = 0x12,   //是否进行去噪-设置
	CT_IS_BLACKSKIN_SET = 0x13,   //是否进行黑皮检测-设置
	CT_IS_HOUGH_SET = 0x14,   //是否进行hough-设置
	CT_IS_MORPHOLOGY_SET = 0x15,  //是否进行形态学-设置
	CT_IS_RESULT_SHOW_SET = 0x16,  //是否进行结果展示-设置

	CT_IS_BINARY_QUERY = 0x21,  //是否进行二值化-查询
	CT_IS_DENOISE_QUERY = 0x22,   //是否进行去噪-查询
	CT_IS_BLACKSKIN_QUERY = 0x23,   //是否进行黑皮检测-查询
	CT_IS_HOUGH_QUERY = 0x24,   //是否进行hough-查询
	CT_IS_MORPHOLOGY_QUERY = 0x25,  //是否进行形态学-查询
	CT_IS_RESULT_SHOW_QUERY = 0x26,  //是否进行结果展示-查询

	CT_HOUGH_THRESOLD_SET = 0x31,  //hough点数阈值-设置
	CT_HOUGH_MIN_LENGTH_SET = 0x32,  //hough最小长度-设置
	CT_HOUGH_MAX_GAP_SET = 0x33,  //hough最小长度-设置
	CT_HOUGH_MAX_ANGEL_SET = 0x34,  //hough最大角度-设置

	CT_HOUGH_THRESOLD_QUERY = 0x41,  //hough点数阈值-查询
	CT_HOUGH_MIN_LENGTH_QUERY = 0x42,  //hough最小长度-查询
	CT_HOUGH_MAX_GAP_QUERY = 0x43,  //hough最小长度-查询
	CT_HOUGH_MAX_ANGEL_QUERY = 0x44,  //hough最大角度-查询

	CT_MORPHOLOGY_MIN_AREA_SET = 0x51,  //斑块最小面积-设置
	CT_MORPHOLOGY_ASPECT_RATIO_SET = 0x52,  //斑块差宽比-设置
	CT_MORPHOLOGY_AREA_RATIO_SET = 0x53,  //斑块面积比-设置

	CT_MORPHOLOGY_MIN_AREA_QUERY = 0x61,  //斑块最小面积-查询
	CT_MORPHOLOGY_ASPECT_RATIO_QUERY = 0x62,  //斑块差宽比-查询
	CT_MORPHOLOGY_AREA_RATIO_QUERY = 0x63,  //斑块面积比-查询

	CT_BLACK_SKIN_MIN_AREA_SET = 0x71,  //黑皮最小面积-设置

	CT_BLACK_SKIN_MIN_AREA_QUERY = 0x81,  //黑皮最小面积-查询
};

int IsBinarySetCmd(const CMD_CTRL* _cmd_ctrl);
int IsDenoiseSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsBlackSkinSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsHoughSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsMorphologySetCmd(const CMD_CTRL* _cmd_ctrl);
int IsShowResultSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsBlackSkinMinAreaSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsHoughThresoldSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsHoughMinLengthSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsHoughMaxGapSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsHoughMaxAngleSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsCrackMinAreaSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsCrackAspectRatioSetCmd(const CMD_CTRL* _cmd_ctrl);
int IsCrackAreaRatioSetCmd(const CMD_CTRL* _cmd_ctrl);

int IsBinaryQueryCmd(const CMD_CTRL* _cmd_ctrl);
int IsDenoiseQueryCmd(const CMD_CTRL* _cmd_ctrl);
int IsBlackSkinQueryCmd(const CMD_CTRL* _cmd_ctrl);
int IsHoughQueryCmd(const CMD_CTRL* _cmd_ctrl);
int IsMorphologyQueryCmd(const CMD_CTRL* _cmd_ctrl);
int IsShowResultQueryCmd(const CMD_CTRL* _cmd_ctrl);
int IsBlackSkinMinAreaQueryCmd(const CMD_CTRL* _cmd_ctrl);
int IsHoughThresoldQueryCmd(const CMD_CTRL* _cmd_ctrl);
int IsHoughMinLengthQueryCmd(const CMD_CTRL* _cmd_ctrl);
int IsHoughMaxGapQueryCmd(const CMD_CTRL* _cmd_ctrl);
int IsHoughMaxAngleQueryCmd(const CMD_CTRL* _cmd_ctrl);
int IsCrackMinAreaQueryCmd(const CMD_CTRL* _cmd_ctrl);
int IsCrackAspectRatioQueryCmd(const CMD_CTRL* _cmd_ctrl);
int IsCrackAreaRatioQueryCmd(const CMD_CTRL* _cmd_ctrl);

#endif /* CMD_IMG_PROC_H_ */
