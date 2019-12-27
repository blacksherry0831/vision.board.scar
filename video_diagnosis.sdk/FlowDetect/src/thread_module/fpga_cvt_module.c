#include "fpga_cvt_module.h"
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
