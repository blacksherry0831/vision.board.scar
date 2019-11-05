#ifndef _CMD_SCAR_H_
#define _CMD_SCAR_H_
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
enum CMD_TYPE_02_I_SCAR{

		CT_IMG_MODE_SCAR=0x80,
		CT_IMG_MASK_SET_SCAR=0x81,
		CT_IMG_MASK_SELECT_SCAR=0x82,

};
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
enum CMD_TYPE_02_I_SCAR_SIGMA{

		CT_IMG_SCAR_GLOBAL_SIGMA_UP=0xF3,
		CT_IMG_SCAR_GLOBAL_SIGMA_DOWN=0xF4,

		CT_IMG_SCAR_ROW_SIGMA_UP=0xF5,
		CT_IMG_SCAR_ROW_SIGMA_DOWN=0xF6,

		CT_IMG_SCAR_COL_SIGMA_UP=0xF7,
		CT_IMG_SCAR_COL_SIGMA_DOWN=0xF8,

};
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
int IsImageScarSet_GlobalSigmaUp(const CMD_CTRL* _cmd_ctrl);
int IsImageScarQuery_GlobalSigmaUp(const CMD_CTRL* _cmd_ctrl);
/*-----------------------------------*/
int IsImageScarSet_GlobalSigmaDown(const CMD_CTRL* _cmd_ctrl);
int IsImageScarQuery_GlobalSigmaDown(const CMD_CTRL* _cmd_ctrl);
/*-----------------------------------*/
int IsImageScarSet_RowSigmaUp(const CMD_CTRL* _cmd_ctrl);
int IsImageScarQuery_RowSigmaUp(const CMD_CTRL* _cmd_ctrl);
/*-----------------------------------*/
int IsImageScarSet_RowSigmaDown(const CMD_CTRL* _cmd_ctrl);
int IsImageScarQuery_RowSigmaDown(const CMD_CTRL* _cmd_ctrl);
/*-----------------------------------*/
int IsImageScarSet_ColSigmaUp(const CMD_CTRL* _cmd_ctrl);
int IsImageScarQuery_ColSigmaUp(const CMD_CTRL* _cmd_ctrl);
/*-----------------------------------*/
int IsImageScarSet_ColSigmaDown(const CMD_CTRL* _cmd_ctrl);
int IsImageScarQuery_ColSigmaDown(const CMD_CTRL* _cmd_ctrl);
/*-----------------------------------*/
int IsImageScarSet_WorkMode(const CMD_CTRL* _cmd_ctrl);
int IsImageScarSet_Mask(const CMD_CTRL* _cmd_ctrl);
int IsImageScarSet_SelectMask(const CMD_CTRL* _cmd_ctrl);
/*-----------------------------------*/
int 			GetMaskSeqNum(const CMD_CTRL* const _cmd_ctrl);
unsigned int* 	GetMaskSeqPtr(const CMD_CTRL* const _cmd_ctrl);
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
#endif