#ifndef _CMD_CRACK_1_8_H_
#define _CMD_CRACK_1_8_H_
/*-----------------------------------*/
#include "linux_header.h"
#include "def.h"
#include "base.h"
#include <modules_ex/opencv_base.h>
/*-----------------------------------*/
#include <modules/uCOS/mem_pool_fixed.h>
/*-----------------------------------*/
#include "type.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
enum 	CMD_TYPE_02_1_and_8_CRACK_SIGMA{

		CT_IMG_SEQ_FRAME_MIN=0xE1,
		CT_IMG_SEQ_FRAME_MAX=0xE2,

};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
enum 	CMD_TYPE_02_1_and_8_CRACK_PROPERTY{

		CT_IMG_OUTSIDE_FIRST_FRAME_NUM=0xD1,
};
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
int IsImageCrack_Set_Frame_Min(const CMD_CTRL* _cmd_ctrl);
int IsImageCrack_Query_Frame_Min(const CMD_CTRL* _cmd_ctrl);
/*-----------------------------------*/
int IsImageCrack_Set_Frame_Max(const CMD_CTRL* _cmd_ctrl);
int IsImageCrack_Query_Frame_Max(const CMD_CTRL* _cmd_ctrl);
/*-----------------------------------*/
int IsImageCrack_Set_out_1st_circle_frames(const CMD_CTRL* _cmd_ctrl);
int IsImageCrack_Query_out_1st_circle_frames(const CMD_CTRL* _cmd_ctrl);
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
#endif
