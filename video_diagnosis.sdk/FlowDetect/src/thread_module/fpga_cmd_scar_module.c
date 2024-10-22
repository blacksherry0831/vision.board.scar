#include "fpga_cmd_scar_module.h"
/*-----------------------------------*/
extern MsgQueueFlame gFlameCmdQueue;
/*-----------------------------------*/
/**
 *等待FPGA一轮数据计算完成
 */
/*-----------------------------------*/
int wait4fpgaCvtDoneScar()
{
	while(IsRun()&&IsCircleTaskRunning_FpgaCvt()==TRUE){
		PRINTF_DBG_EX("FPGA CIRCLE TASK IS RUNNING NOW,wait for fpga circle done ! \n");
		init_1st_2nd_task_circle_flag();  //初始化任务标志为0
		sleepMS(100);
	}
	return TRUE;
}
/*-----------------------------------*/
/**
 *开启FPGA计算任务
 */
/*-----------------------------------*/
int  StartFpgaCircleScar(int _WorkMode,unsigned int _seq)
{

	wait4fpgaCvtDoneScar();  //等待FPGA一轮数据计算完成

	int result_t=-1;

	assert(FALSE==IsCircleTaskRunning_FpgaCvt());

	if(FALSE==IsCircleTaskRunning_FpgaCvt()){  //FPGA数据计算是否正在进行
		init_1st_2nd_task_circle_flag();  //初始化任务标志为0
		set_task_circle_start();  //开启一轮计算任务 CT_FPGA_START
		SetFpgaCircleWorkMode(_WorkMode);  //设置FPGA和DMA的工作模式（原图？原尺寸）
		SetFrameCircleSeq(_seq);  //设置序列号
		result_t= post_fpga_start_sig();  //m_sem_fpga_circle_start信号量加1
	}

	assert(printf_dbg_fpga_param());

	return result_t;
}

/*-----------------------------------*/
/**
 *依据cmd设置任务圈标志
 */
/*-----------------------------------*/
void setFpgaCircleCmdScar(const CMD_CTRL* const _cmd_ctrl)
{
	const int StartParam=GetStartCmdParam(_cmd_ctrl);  //获取startCmd的控制数据实体
	const int StartCmd01=GetCmdCmd01(_cmd_ctrl);  //获取_cmd的命令类型
	const unsigned int StartSeq=GetCmdFrameSeq(_cmd_ctrl);  //获取cmd序列号

		if(StartCmd01 == CT_START){

			PRINTF_DBG_EX("workflow@Rcv Start CMD \n");
			StartFpgaCircleScar(StartParam,StartSeq);  //开启FPGA计算任务

			if(IsProjectRun(flame_monitor))
			{
				if(get_flame_monitor_flag())
				{
					init_fire();

					gFlameCmdQueue.snd_queue_flame(1,0);  //点火
				}
			}

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

			if(IsProjectRun(flame_monitor))
			{
				gFlameCmdQueue.snd_queue_flame(0,1);  //灭火
			}

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
