#include "flow_sync.h"
/*-----------------------------------*/
volatile enum ProjectRun gProjectCurrentRunning=outside08;
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
volatile unsigned int G_CHANNEL=0xff;
volatile int m_buffer_size=0;
/*-----------------------------------*/
sem_t m_sem_fpga_frame_done;
sem_t m_sem_dma_frame_done2Mem;
sem_t m_sem_dma_frame_done2fpga;
sem_t m_sem_memcpy_frame_done;
/*-----------------------------------*/
sem_t m_sem_fpga_circle_start;
sem_t m_sem_fpga_circle_done;
/*-----------------------------------*/
volatile int FRAME_IDX=0;
volatile unsigned int FRAME_IDX_MAX=0xffffffff;
volatile unsigned int FRAME_IDX_MIN=0;
volatile unsigned int FRAME_CIRCLE_SEQ=0;
volatile int FPGA_CIRCLE_TASK_RUNNING=FALSE;
volatile int FPGA_CIRCLE_TASK_FIRST_START=FALSE;
volatile int FPGA_CIRCLE_TASK_SECOND_START=FALSE;
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
				&m_sem_fpga_circle_start,
				&m_sem_fpga_circle_done
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
				 PRINTF_DBG("sem_init _fail");
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
					 PRINTF_DBG("sem_init _fail");
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
void SetProjecRun(enum ProjectRun _pr)
{
	gProjectCurrentRunning=_pr;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
enum ProjectRun GetProjectRun()
{

	return gProjectCurrentRunning;

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
	PRINTF_DBG("###############################################################\n");
	PRINTF_DBG("Process shutdown ! \n");
	PRINTF_DBG("###############################################################\n");
	G_Thread_Run=FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ExitFpgaThread()
{
	 PRINTF_DBG("pthread close>> [fpga thread]\n");
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
	PRINTF_DBG("pthread start >>[task flow ctrl]\n");
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ExitTaskFlowCtrl()
{
	StopFpgaCircleRunning();
	PRINTF_DBG("pthread close >>[task flow ctrl]\n");
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
	PRINTF_DBG("pthread close>> [TcpServer:%d]\n",server_port);
	pthread_exit(NULL);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ExitDmaThread()
{
	 PRINTF_DBG("pthread close>> [dma thread]\n");
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
	PRINTF_DBG("pthread close>> [memcpy thread]\n");
	G_Thread_MEMCPY_Running=FALSE;
	pthread_exit(NULL);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void EnterTcpTransImageThread(int _socket)
{
	PRINTF_DBG("pthread start>> [tcp image transfer thread]\n");

	G_Thread_TCP_TRANS_IMG_Running=TRUE;

	setCurrentThreadHighPriority(1);

	set_socket_buf_size(_socket,16*1024*1024);
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
void ExitTcpTransImageThread()
{
	PRINTF_DBG("pthread close>> [tcp image transfer thread]\n");
	G_Thread_TCP_TRANS_IMG_Running=FALSE;
	pthread_exit(NULL);
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
void printf_dbg_fpga_param()
{

#if _DEBUG

	PRINTF_DBG("FPGA_CIRCLE_WORK_MODE: ");
	if(FPGA_CIRCLE_WORK_MODE&WM_ORG_IMG){
		PRINTF_DBG("WM_ORG_IMG,");
	}
	if(FPGA_CIRCLE_WORK_MODE&WM_DIFF_IMG){
		PRINTF_DBG("WM_DIFF_IMG,");
	}
	if(FPGA_CIRCLE_WORK_MODE&WM_SIZE_FULL){
		PRINTF_DBG("WM_SIZE_FULL,\n");
	}
	if(FPGA_CIRCLE_WORK_MODE&WM_SIZE_CUT){
		PRINTF_DBG("WM_SIZE_CUT,");
	}
	PRINTF_DBG("\n");

#endif

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  StartFpgaCircle(int _WorkMode,unsigned int _seq)
{
	int result_t=-1;

	while(FPGA_CIRCLE_TASK_RUNNING==TRUE){
		PRINTF_DBG("FPGA CIRCLE TASK IS RUNNING NOW,wait for fpga circle done ! \n");
		FPGA_CIRCLE_TASK_FIRST_START=FPGA_CIRCLE_TASK_SECOND_START=FALSE;
		sleep(1);
		if(IsRun()==FALSE){
			return -1;
		}
	}


	if(FPGA_CIRCLE_TASK_RUNNING==FALSE){
		FPGA_CIRCLE_TASK_RUNNING=TRUE;
		FPGA_CIRCLE_TASK_FIRST_START=FPGA_CIRCLE_TASK_SECOND_START=FALSE;
		SetFpgaCircleWorkMode(_WorkMode);
		SetFrameCircleSeq(_seq);
		result_t=sem_post(&m_sem_fpga_circle_start);
	}



	printf_dbg_fpga_param();

	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void StopFpgaCircleRunning()
{
	FPGA_CIRCLE_TASK_RUNNING=FPGA_CIRCLE_TASK_FIRST_START=FPGA_CIRCLE_TASK_SECOND_START=FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsFpgaTaskFirstStart()
{
	return FPGA_CIRCLE_TASK_FIRST_START;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsFpgaTaskSecondStart()
{
	return FPGA_CIRCLE_TASK_SECOND_START;
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

			PRINTF_DBG("Rcv Start CMD \n");
			StartFpgaCircle(StartParam,StartSeq);

		}else if(StartCmd01==CT_START_00){

			PRINTF_DBG("Rcv Start CMD 00 \n");
			FPGA_CIRCLE_TASK_FIRST_START=TRUE;

		}else if(StartCmd01==CT_STOP_00){

			FPGA_CIRCLE_TASK_FIRST_START=FALSE;

		}else if(StartCmd01==CT_START_01){

			PRINTF_DBG("Rcv Start CMD 01 \n");
			FPGA_CIRCLE_TASK_SECOND_START=TRUE;

		}else if(StartCmd01==CT_STOP_01){

			FPGA_CIRCLE_TASK_SECOND_START=FALSE;

		}else if(StartCmd01==CT_STOP){

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


/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int Wait4StartFpgaCircle()
{
	int result_t=sem_wait_infinite(&m_sem_fpga_circle_start);
	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int Wait4FpgaCircleDone()
{
	return sem_wait_infinite(&m_sem_fpga_circle_done);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsFpgaCircleRunning()
{
	return FPGA_CIRCLE_TASK_RUNNING;
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
void SetGlobalChannel(unsigned int _channel)
{
	G_CHANNEL=_channel;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetGlobalChannel()
{
	return G_CHANNEL;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetFrameIdxMin(unsigned int _max)
{
	FRAME_IDX_MIN=_max;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetFrameIdxMin()
{
	return FRAME_IDX_MIN;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetFrameIdxMax(unsigned int _max)
{
	FRAME_IDX_MAX=_max;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetFrameIdxMax()
{
	return FRAME_IDX_MAX;
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
unsigned int GetGlobalChannelMask(int _ch)
{

			if(G_CHANNEL & (0x01<<_ch)){
				return TRUE;
			}else{
				return FALSE;
			}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

