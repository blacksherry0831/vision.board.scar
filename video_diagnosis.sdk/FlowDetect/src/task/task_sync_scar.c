#include "task_sync_scar.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/axi_fpga_ctrl_img_scar.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void printf_dbg_fpga_scar_param()
{

	const int work_mode=GetFpgaCircleWorkMode();

#if _DEBUG

	PRINTF_DBG("FPGA_CIRCLE_WORK_MODE: ");
	if(work_mode&SCAR_DETECT_MODE_GLOBAL){
		PRINTF_DBG("global \n");
	}
	if(work_mode&SCAR_DETECT_MODE_ROW){
		PRINTF_DBG("row,\n");
	}
	if(work_mode&SCAR_DETECT_MODE_COL){
		PRINTF_DBG("col,\n");
	}
	if(work_mode==SCAR_DETECT_MODE_ORG){
		PRINTF_DBG("org,");
	}
	PRINTF_DBG("\n");

#endif

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  StartFpgaScarCircle(int _WorkMode,unsigned int _seq)
{
	int result_t=-1;

	while(IsFpgaCircleRunning()==TRUE){
		PRINTF_DBG("FPGA CIRCLE TASK IS RUNNING NOW,wait for fpga circle done ! \n");

		SetFpgaTaskFirstStart(FALSE);
		SetFpgaTaskSecondStart(FALSE);

		sleep(1);
		if(IsRun()==FALSE){
			return -1;
		}
	}


	if( IsFpgaCircleRunning()==FALSE){
		SetFpgaCircleRunning(TRUE);

		SetFpgaTaskFirstStart(FALSE);
		SetFpgaTaskSecondStart(FALSE);

		fpga_img_scar_detect_mode(_WorkMode);

		SetFrameCircleSeq(_seq);
		result_t=post_Start_sig();
	}

	printf_dbg_fpga_scar_param();

	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void setFpgaScarCmd(const CMD_CTRL* const _cmd_ctrl)
{
	const int StartParam=GetStartCmdParam(_cmd_ctrl);
	const int StartCmd02=GetCmdCmd02(_cmd_ctrl);
	const unsigned int StartSeq=GetCmdFrameSeq(_cmd_ctrl);

		if(StartCmd02 == CT_START){

			PRINTF_DBG("Rcv Start CMD \n");
			StartFpgaScarCircle(StartParam,StartSeq);

		}else if(StartCmd02==CT_START_00){

			PRINTF_DBG("Rcv Start CMD 00 \n");
			SetFpgaTaskFirstStart(TRUE);

		}else if(StartCmd02==CT_STOP_00){

			SetFpgaTaskFirstStart(FALSE);


		}else if(StartCmd02==CT_START_01){

			PRINTF_DBG("Rcv Start CMD 01 \n");
			SetFpgaTaskSecondStart(TRUE);

		}else if(StartCmd02==CT_STOP_01){

			SetFpgaTaskSecondStart(FALSE);

		}else if(StartCmd02==CT_STOP){

			PRINTF_DBG("Rcv Stop CMD \n");
			StopFpgaCircleRunning();


		}else{

			PRINTF_DBG("Rcv Stop CMD \n");

		}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

