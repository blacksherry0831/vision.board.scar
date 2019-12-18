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

#ifdef _DEBUG

	PRINTF_DBG_EX("FPGA_CIRCLE_WORK_MODE: ");
	if(work_mode&SCAR_DETECT_MODE_GLOBAL){
		PRINTF_DBG_EX("global \n");
	}
	if(work_mode&SCAR_DETECT_MODE_ROW){
		PRINTF_DBG_EX("row,\n");
	}
	if(work_mode&SCAR_DETECT_MODE_COL){
		PRINTF_DBG_EX("col,\n");
	}
	if(work_mode==SCAR_DETECT_MODE_ORG){
		PRINTF_DBG_EX("org,");
	}
	PRINTF_DBG_EX("\n");

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



	while(TRUE==IsCircleTaskRunning_FpgaCvt()){
		PRINTF_DBG_EX("FPGA CIRCLE TASK IS RUNNING NOW,wait for fpga circle done ! \n");

		init_1st_2nd_circle_flag();

		sleep(1);
		if(IsRun()==FALSE){
			return -1;
		}
	}


	if(FALSE==IsCircleTaskRunning_FpgaCvt()){
		init_1st_2nd_circle_flag();
		set_task_circle_start();

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
	const int StartCmd01=GetCmdCmd01(_cmd_ctrl);
	const unsigned int StartSeq=GetCmdFrameSeq(_cmd_ctrl);

		if(StartCmd01 == CT_START){

			PRINTF_DBG_EX("Rcv Start CMD \n");
			StartFpgaScarCircle(StartParam,StartSeq);

		}else if(StartCmd01==CT_START_00){

			PRINTF_DBG_EX("Rcv Start CMD 00 \n");
			set_1st_circle_start();

		}else if(StartCmd01==CT_STOP_00){

			set_1st_circle_end();


		}else if(StartCmd01==CT_START_01){

			PRINTF_DBG_EX("Rcv Start CMD 01 \n");
			set_2nd_circle_start();

		}else if(StartCmd01==CT_STOP_01){

			set_2nd_circle_end();

		}else if(StartCmd01==CT_STOP){

			PRINTF_DBG_EX("Rcv Stop CMD \n");
			set_task_circle_end();


		}else{
			assert(0);
			PRINTF_DBG_EX("Rcv Error Cmd \n");

		}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

