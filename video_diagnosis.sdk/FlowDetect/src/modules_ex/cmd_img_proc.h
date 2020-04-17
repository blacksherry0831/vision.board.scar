/*
 * cmd_img_proc.h
 *
 *  Created on: 2020��4��10��
 *      Author: yjkj909
 */

#ifndef CMD_IMG_PROC_H_
#define CMD_IMG_PROC_H_

#include "type.h"

//��������
enum CMD_TYPE_00_IMG_PROC {

	CT_ARM_IMG_PROC = 'A',  //armͼ������ز���

};

//ARMͼ����-�������A�� ����
enum CMD_TYPE_02_A {
	CT_IS_BINARY_SET = 0x11,  //�Ƿ���ж�ֵ��-����
	CT_IS_DENOISE_SET = 0x12,   //�Ƿ����ȥ��-����
	CT_IS_BLACKSKIN_SET = 0x13,   //�Ƿ���к�Ƥ���-����
	CT_IS_HOUGH_SET = 0x14,   //�Ƿ����hough-����
	CT_IS_MORPHOLOGY_SET = 0x15,  //�Ƿ������̬ѧ-����
	CT_IS_RESULT_SHOW_SET = 0x16,  //�Ƿ���н��չʾ-����

	CT_IS_BINARY_QUERY = 0x21,  //�Ƿ���ж�ֵ��-��ѯ
	CT_IS_DENOISE_QUERY = 0x22,   //�Ƿ����ȥ��-��ѯ
	CT_IS_BLACKSKIN_QUERY = 0x23,   //�Ƿ���к�Ƥ���-��ѯ
	CT_IS_HOUGH_QUERY = 0x24,   //�Ƿ����hough-��ѯ
	CT_IS_MORPHOLOGY_QUERY = 0x25,  //�Ƿ������̬ѧ-��ѯ
	CT_IS_RESULT_SHOW_QUERY = 0x26,  //�Ƿ���н��չʾ-��ѯ

	CT_HOUGH_THRESOLD_SET = 0x31,  //hough������ֵ-����
	CT_HOUGH_MIN_LENGTH_SET = 0x32,  //hough��С����-����
	CT_HOUGH_MAX_GAP_SET = 0x33,  //hough��С����-����
	CT_HOUGH_MAX_ANGEL_SET = 0x34,  //hough���Ƕ�-����

	CT_HOUGH_THRESOLD_QUERY = 0x41,  //hough������ֵ-��ѯ
	CT_HOUGH_MIN_LENGTH_QUERY = 0x42,  //hough��С����-��ѯ
	CT_HOUGH_MAX_GAP_QUERY = 0x43,  //hough��С����-��ѯ
	CT_HOUGH_MAX_ANGEL_QUERY = 0x44,  //hough���Ƕ�-��ѯ

	CT_MORPHOLOGY_MIN_AREA_SET = 0x51,  //�߿���С���-����
	CT_MORPHOLOGY_ASPECT_RATIO_SET = 0x52,  //�߿����-����
	CT_MORPHOLOGY_AREA_RATIO_SET = 0x53,  //�߿������-����

	CT_MORPHOLOGY_MIN_AREA_QUERY = 0x61,  //�߿���С���-��ѯ
	CT_MORPHOLOGY_ASPECT_RATIO_QUERY = 0x62,  //�߿����-��ѯ
	CT_MORPHOLOGY_AREA_RATIO_QUERY = 0x63,  //�߿������-��ѯ

	CT_BLACK_SKIN_MIN_AREA_SET = 0x71,  //��Ƥ��С���-����

	CT_BLACK_SKIN_MIN_AREA_QUERY = 0x81,  //��Ƥ��С���-��ѯ
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
