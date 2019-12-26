#include "sync_task.h"
/*-----------------------------------*/
static volatile int FRAME_IDX=0;
static volatile unsigned int FRAME_CIRCLE_SEQ=0;
static volatile int FPGA_CIRCLE_WORK_MODE=WM_SIZE_FULL|WM_ORG_IMG;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void IncFrameIdx()
{
	FRAME_IDX++;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int getFrameIdx()
{
	return FRAME_IDX;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int initFrameIdx()
{
	return FRAME_IDX=FRAME_IDX_TYPE_FIRST_IMG;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetFrameCircleSeq(unsigned int _seq)
{
	FRAME_CIRCLE_SEQ=_seq;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetFrameCircleSeq()
{
	return FRAME_CIRCLE_SEQ;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsWorkMode_OrgImg()
{
	return WM_ORG_IMG==(getFpgaCircleWorkMode()&WM_ORG_IMG);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsWorkMode_DiffImg()
{
	return WM_DIFF_IMG==(getFpgaCircleWorkMode()&WM_DIFF_IMG);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int printf_dbg_fpga_param()
{
#ifdef _DEBUG

	PRINTF_DBG_EX("FPGA_CIRCLE_WORK_MODE: ");
	if(FPGA_CIRCLE_WORK_MODE&WM_ORG_IMG){
		PRINTF_DBG_EX("WM_ORG_IMG,");
	}
	if(FPGA_CIRCLE_WORK_MODE&WM_DIFF_IMG){
		PRINTF_DBG_EX("WM_DIFF_IMG,");
	}
	if(FPGA_CIRCLE_WORK_MODE&WM_SIZE_FULL){
		PRINTF_DBG_EX("WM_SIZE_FULL,\n");
	}
	if(FPGA_CIRCLE_WORK_MODE&WM_SIZE_CUT){
		PRINTF_DBG_EX("WM_SIZE_CUT,");
	}
	PRINTF_DBG_EX("\n");

#endif
	return TRUE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int getFpgaCircleWorkMode()
{
	return FPGA_CIRCLE_WORK_MODE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void setFpgaCircleWorkMode(const int _wm)
{
	FPGA_CIRCLE_WORK_MODE=_wm;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
