#include "fpga_cmd_scar_module.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4fpgaCvtDoneScar()
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
int  StartFpgaCircleScar(int _WorkMode,unsigned int _seq)
{

	wait4fpgaCvtDoneScar();

	int result_t=-1;

	assert(FALSE==IsCircleTaskRunning_FpgaCvt());

	if(FALSE==IsCircleTaskRunning_FpgaCvt()){
		init_1st_2nd_task_circle_flag();
		set_task_circle_start();
		SetFpgaCircleWorkMode(_WorkMode);
		SetFrameCircleSeq(_seq);
		result_t= post_fpga_start_sig();
	}

	assert(printf_dbg_fpga_param());

	return result_t;
}

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void setFpgaCircleCmdScar(const CMD_CTRL* const _cmd_ctrl)
{
	const int StartParam=GetStartCmdParam(_cmd_ctrl);
	const int StartCmd01=GetCmdCmd01(_cmd_ctrl);
	const unsigned int StartSeq=GetCmdFrameSeq(_cmd_ctrl);

		if(StartCmd01 == CT_START){

			PRINTF_DBG_EX("workflow@Rcv Start CMD \n");
			StartFpgaCircleScar(StartParam,StartSeq);

		}else if(StartCmd01==CT_START_00){

			PRINTF_DBG_EX("workflow@Rcv Start CMD 00 \n");
			set_1st_circle_start();

		}else if(StartCmd01==CT_STOP_00){

			PRINTF_DBG_EX("workflow@Rcv Stop  CMD 00\n");
			set_1st_circle_end();

		}else if(StartCmd01==CT_START_01){

			PRINTF_DBG_EX("workflow@Rcv Start CMD 01 \n");
			set_2nd_circle_start();

		}else if(StartCmd01==CT_STOP_01){

			PRINTF_DBG_EX("workflow@Rcv Stop  CMD 	01\n");
			set_2nd_circle_end();

		}else if(StartCmd01==CT_STOP){

			PRINTF_DBG_EX("workflow@Rcv Stop CMD \n");
			set_task_circle_end();

		}else{

			PRINTF_DBG_EX("workflow@Rcv Error CMD \n");
			assert(0);
		}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
