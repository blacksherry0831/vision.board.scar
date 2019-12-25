#include "task_sync.h"
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
volatile int G_Thread_Run=TRUE;
/*-----------------------------------*/
volatile int G_Thread_FPGA_Running=TRUE;
volatile int G_Thread_DMA_Running=TRUE;
volatile int G_Thread_MEMCPY_Running=TRUE;
/*-----------------------------------*/
volatile int G_Thread_TCP_TRANS_IMG_Running=FALSE;
/*-----------------------------------*/

volatile int m_buffer_size=0;
/*-----------------------------------*/
sem_t m_sem_fpga_frame_done;
sem_t m_sem_dma_frame_done2Mem;
sem_t m_sem_dma_frame_done2fpga;
sem_t m_sem_memcpy_frame_done;
/*-----------------------------------*/
static  sem_t m_sem_fpga_circle_start;
/*-----------------------------------*/
volatile int FRAME_IDX=0;
/*-----------------------------------*/
volatile unsigned int FRAME_CIRCLE_SEQ=0;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
volatile int FPGA_CIRCLE_WORK_MODE=WM_SIZE_FULL|WM_ORG_IMG;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
sem_t* SEM[]={&m_sem_fpga_frame_done,
				&m_sem_dma_frame_done2Mem,
				&m_sem_dma_frame_done2fpga,
				&m_sem_memcpy_frame_done,
				&m_sem_fpga_circle_start
};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void setFpgaCircleCmd(const CMD_CTRL* const _cmd_ctrl);
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int initSemSignal()
{

	int SEM_SIZE=sizeof(SEM)/sizeof(sem_t*);
	int i=0;
	for(i=0;i<SEM_SIZE;i++){

		sem_t* sem_ptr=SEM[i];

		int nRet = sem_init(sem_ptr, 0, 0);

		if (0 != nRet){
				 PRINTF_DBG_EX("sem_init _fail");
				 return -1;
		}

	}

	return 1;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int destorySemSignal()
{
	int SEM_SIZE=sizeof(SEM)/sizeof(sem_t*);
	int i=0;
		for(i=0;i<SEM_SIZE;i++){

			sem_t* sem_ptr=SEM[i];

			int nRet = sem_destroy(sem_ptr);

			if (0 != nRet){
					 PRINTF_DBG_EX("sem_init _fail");
					 return -1;
			}

		}

		return 1;
}

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/





/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/


/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/


/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsRun()
{
	return G_Thread_Run;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void StopRun(int _param)
{
	PRINTF_DBG_EX("###############################################################\n");
	PRINTF_DBG_EX("Process shutdown ! \n");
	PRINTF_DBG_EX("###############################################################\n");
	G_Thread_Run=FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ExitFpgaThread()
{
	 PRINTF_DBG_EX("pthread close>> [fpga thread]\n");
	 G_Thread_FPGA_Running=FALSE;
	 pthread_exit(NULL);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void EnterTaskFlowCtrl()
{
	PRINTF_DBG_EX("pthread start >>[task flow ctrl]\n");
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ExitTaskFlowCtrl()
{
	StopFpgaCircleRunning();
	PRINTF_DBG_EX("pthread close >>[task flow ctrl]\n");
	pthread_exit(NULL);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ExitTcpServer(int socket_fd,int server_port)
{
	close(socket_fd);
	PRINTF_DBG_EX("pthread close>> [TcpServer:%d]\n",server_port);
	pthread_exit(NULL);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ExitDmaThread()
{
	 PRINTF_DBG_EX("pthread close>> [dma thread]\n");
	 G_Thread_DMA_Running=FALSE;
	 pthread_exit(NULL);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ExitMemCpyThread()
{
	PRINTF_DBG_EX("pthread close>> [memcpy thread]\n");
	G_Thread_MEMCPY_Running=FALSE;
	pthread_exit(NULL);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetTcpTransImageThreadRunning(const int _v)
{
	G_Thread_TCP_TRANS_IMG_Running=_v;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsTcpTransImageThreadRunning()
{
	return G_Thread_TCP_TRANS_IMG_Running;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsDMARun()
{

	if((G_Thread_Run==FALSE) && (G_Thread_FPGA_Running==FALSE)){
					return FALSE;
	}
	return TRUE;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsMemCpyRun()
{

	if((G_Thread_Run==FALSE) &&
		(G_Thread_FPGA_Running==FALSE)&&
		(G_Thread_DMA_Running==FALSE)	){
					return FALSE;
	}
	return TRUE;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsTcpTransImageRun()
{

	if((G_Thread_Run==FALSE) &&
		(G_Thread_FPGA_Running==FALSE)&&
		(G_Thread_DMA_Running==FALSE)&&
		(G_Thread_MEMCPY_Running==FALSE)){
					return FALSE;
	}
	return TRUE;

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
int  post_fpga_start_sig()
{
	return  sem_post(&m_sem_fpga_circle_start);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait_fpga_start_sig()
{
	int result_t=sem_wait(&m_sem_fpga_circle_start);
	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4fpgaCvtDone()
{
	while(IsCircleTaskRunning_FpgaCvt()==TRUE){
		PRINTF_DBG_EX("FPGA CIRCLE TASK IS RUNNING NOW,wait for fpga circle done ! \n");
		init_1st_2nd_task_circle_flag();
		sleepMS(100);
		if(IsRun()==FALSE){
			return -1;
		}
	}
	return TRUE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  StartFpgaCircle(int _WorkMode,unsigned int _seq)
{

	wait4fpgaCvtDone();

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
void StopFpgaCircleRunning()
{
	init_1st_2nd_task_circle_flag();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void setFpgaCircleCmd(const CMD_CTRL* const _cmd_ctrl)
{
	const int StartParam=GetStartCmdParam(_cmd_ctrl);
	const int StartCmd01=GetCmdCmd01(_cmd_ctrl);
	const unsigned int StartSeq=GetCmdFrameSeq(_cmd_ctrl);

		if(StartCmd01 == CT_START){

			PRINTF_DBG_EX("workflow@Rcv Start CMD \n");
			StartFpgaCircle(StartParam,StartSeq);

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
int GetFpgaCircleWorkMode()
{
	return FPGA_CIRCLE_WORK_MODE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsWorkMode_OrgImg()
{
	return WM_ORG_IMG==(GetFpgaCircleWorkMode()&WM_ORG_IMG);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsWorkMode_DiffImg()
{
	return WM_DIFF_IMG==(GetFpgaCircleWorkMode()&WM_DIFF_IMG);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int SetFpgaCircleWorkMode(int _wm)
{

	FPGA_CIRCLE_WORK_MODE=_wm;

	SetDmaFrameByWorkMode(_wm);

	return 1;
}
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
	return FRAME_IDX=FRAME_IDX_TYPE_FIRST_IMG ;
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

