#include "fpga_cvt_module.h"
/*-----------------------------------*/
int FRAME_IDX_FIRST=0;
/*-----------------------------------*/
int FRAME_IDX_SECOND=0;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4fpgaCvtDone()
{
	while(IsRun()&&IsCircleTaskRunning_FpgaCvt()==TRUE){
		PRINTF_DBG_EX("FPGA CIRCLE TASK IS RUNNING NOW,wait for fpga circle done ! \n");
		init_1st_2nd_task_circle_flag();
		sleepMS(100);
	}
	return TRUE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int SetFpgaCircleWorkMode(int _wm)
{

	setFpgaCircleWorkMode(_wm);

	SetDmaFrameByWorkMode(_wm);

	return 1;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4FpgaStart()
{
	PRINTF_DBG_EX("............FFFFFFFFFFFFF...............\n");
	PRINTF_DBG_EX("FPGA Cvt >>wait start  sig ! \n");

	if(SUCCESS==wait_fpga_start_sig()){
		return TRUE;
	}else{
		PRINTF_DBG_EX("FPGA Cvt >>sem error! \n");
	}

	return FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void stopThisCircle()
{
		sendImageStop();
		PRINTF_DBG_EX("FPGA>>Stop FPGA Circle \n");
		PRINTF_DBG_EX("___________FFFFFFFFFFFFF___________\n");
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void startThisCircle()
{
	sendImageStart();
	PRINTF_DBG_EX("++++++++++++++FFFFFFFFFFFFF++++++++++++++\n");
	PRINTF_DBG_EX("FPGA>>Start FPGA Circle \n");
	sleepMS(100);
	sendImageMask();
	PRINTF_DBG_EX("FPGA>>Send Mask Image \n");
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsCircleTaskRunning()
{
	return IsCircleTaskRunning_FpgaCvt() && IsRun();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4Circle1st()
{
	while(IsCircleTaskRunning()){

		const int start_1st=get_1st_circle_start();

		if(TRUE==start_1st){
			return TRUE;
		}

		usleep(1);

	}

	return FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4Circle2nd()
{
	while(IsCircleTaskRunning()){

			const int start_status=get_2nd_circle_start();

			if(TRUE==start_status){
				return TRUE;
			}

			usleep(1);

		}

		return FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsFirstCircleRunning()
{
		const int IsCircleRunning=IsCircleTaskRunning();
		return IsCircleRunning && get_1st_circle_running();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsSecondCircleRunning()
{
		const int IsCircleRunning=IsCircleTaskRunning();
		return IsCircleRunning && get_2nd_circle_running();

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
