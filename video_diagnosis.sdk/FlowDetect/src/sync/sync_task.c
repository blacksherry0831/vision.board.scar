#include "sync_task.h"
/*-----------------------------------*/
static volatile int FRAME_IDX=0;
static volatile unsigned int FRAME_CIRCLE_SEQ=0;
static volatile int FPGA_CIRCLE_WORK_MODE=WM_SIZE_FULL|WM_ORG_IMG;
/*-----------------------------------*/
volatile int FRAME_IDX_FIRST=0;
/*-----------------------------------*/
volatile int FRAME_IDX_SECOND=0;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void IncFrameIdx()
{
	__sync_fetch_and_add(&FRAME_IDX,1);
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
	 __sync_lock_test_and_set(&FRAME_IDX,FRAME_IDX_TYPE_FIRST_IMG);
	return  getFrameIdx();
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
 *设置FPGA工作模式（原图？原尺寸）
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
