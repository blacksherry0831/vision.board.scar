#include "task_fpga_cvt.h"
/*-----------------------------------*/
#include "img_cfg/scar_cfg.h"
/*-----------------------------------*/
int FPGA_CONVERT_DONE=FALSE;
/*-----------------------------------*/
int FRAME_IDX_FIRST=0;
/*-----------------------------------*/
int FRAME_IDX_SECOND=0;
/*-----------------------------------*/
enum CircleFlag
{
	FIRST_CIRCLE_IO=0x00,
	SECOND_CIRCLE_IO=0x01,
};
/*-----------------------------------*/
unsigned int    FPGA_CvtDone=0;
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
pthread_cond_t 	mCondFpgaStartStep_1=PTHREAD_COND_INITIALIZER;
pthread_mutex_t mMutexFpga=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t FPGA_mutex_cvt = PTHREAD_MUTEX_INITIALIZER;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsCircleTaskRunning()
{
	return IsFpgaCircleRunning() && IsRun();
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
volatile int ProcessImageData=0;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4FpgaStart()
{
	PRINTF_DBG_EX("FPGA>>wait for start cmd ! \n");

	if(Wait4StartFpgaCircle()==SUCCESS){
		return TRUE;
	}else{
		ExitFpgaThread();
	}

	return FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4Circle(const int _first_second)
{

		while(IsCircleTaskRunning()){

					if(_first_second==FIRST_CIRCLE_IO){

							if(TRUE==IsFpgaTaskFirstStart()){
								return TRUE;
							}

					}else if(_first_second==SECOND_CIRCLE_IO){

							if(TRUE==IsFpgaTaskSecondStart()){
								return TRUE;
							}
					}else{


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
int IsCircleRunning(const int _first_second)
{
	const int IsCircleRunning=IsCircleTaskRunning();

				if(_first_second==0x00){

					 return IsCircleRunning && IsFpgaTaskFirstStart();

				}else if(_first_second==0x01){

					 return IsCircleRunning && IsFpgaTaskSecondStart();

				}else{


				}


}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  initFirstMode()
{
	int First_Mode=0;
		if(WM_ORG_IMG==(GetFpgaCircleWorkMode()&WM_ORG_IMG)){
			First_Mode=FPGA_WORK_MODE_DATA_ZERO;
		}else if(WM_DIFF_IMG==(GetFpgaCircleWorkMode()&WM_DIFF_IMG)){
			First_Mode=FPGA_WORK_MODE_DATA_AVG;
		}else{

		}
	return First_Mode;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsFrameCollect(int _current_idx)
{

	if(_current_idx<GetFrameIdxMax()){
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
void scar_inside_second_ex(const int _org,const int _fi)
{
	FPGA_CvtDone=FALSE;

	scar_cvt(_org,_fi);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void outside_inside_second_ex()
{
	FPGA_CvtDone=FALSE;

	outside_second();

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void scar_second_sync(int _frame_idx,const int _org,const int _fi)
{
	static int FPGA_COUNT=0;
	if(pthread_mutex_lock(&FPGA_mutex_cvt)==SUCCESS){

				TIME_START();

					scar_inside_second_ex(_org,_fi);
					__sync_lock_test_and_set(&FPGA_CvtDone,TRUE);
					PRINTF_DBG_EX("FPGA:%d___",FPGA_COUNT++);

				TIME_END("1> FPGA Convert cost time : ");

				if(pthread_mutex_unlock(&FPGA_mutex_cvt)==SUCCESS){
						sem_post(&m_sem_fpga_frame_done);
						sched_yield();
						sem_wait_infinite(&m_sem_dma_frame_done2fpga);

				}
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void outside_second_sync(int _frame_idx)
{
	static int FPGA_COUNT=0;
	if(pthread_mutex_lock(&FPGA_mutex_cvt)==SUCCESS){

				TIME_START();
					outside_inside_second_ex();
					__sync_lock_test_and_set(&FPGA_CvtDone,TRUE);
					PRINTF_DBG_EX("FPGA:%d___",FPGA_COUNT++);

				TIME_END("1> FPGA Convert cost time : ");

				if(pthread_mutex_unlock(&FPGA_mutex_cvt)==SUCCESS){
						sem_post(&m_sem_fpga_frame_done);
						sched_yield();
						sem_wait_infinite(&m_sem_dma_frame_done2fpga);

				}
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void CvtFrameScar(unsigned int _base_idx,unsigned int current_idx,const int _org,const int _fi)
{
	const unsigned int relative_idx=current_idx-_base_idx;

	if(		(relative_idx>=GetFrameIdxMin())&&
			(relative_idx<=GetFrameIdxMax())
			){
			scar_second_sync(current_idx,_org,_fi);
	}else{
			sleepMS(100);
			IncFrameIdx();
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void CvtFrame(unsigned int _base_idx,unsigned int current_idx)
{
	const unsigned int relative_idx=current_idx-_base_idx;

	if(		(relative_idx>=GetFrameIdxMin())&&
			(relative_idx<=GetFrameIdxMax())
			){
			outside_second_sync(current_idx);
	}else{
			sleepMS(100);
			IncFrameIdx();
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void theFirstCircleScar()
{
	const int FirstCircle=FIRST_CIRCLE_IO;

			PRINTF_DBG_EX("FPGA>>wait for start cmd 00 ! \n");

			if(wait4Circle(FirstCircle)){

				PRINTF_DBG_EX("FPGA>>start cmd 00 ! \n");

					if(GetProjectRun()==scar_detect_01){

					}else{

					}


			}

			PRINTF_DBG_EX("FPGA>>stop cmd 00 ! \n");

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void theFirstCircle()
{
		const int FirstCircle=FIRST_CIRCLE_IO;

		PRINTF_DBG_EX("FPGA>>wait for start cmd 00 ! \n");

		if(wait4Circle(FirstCircle)){

			PRINTF_DBG_EX("FPGA>>start cmd 00 ! \n");

				if(GetProjectRun()==outside08){

							do{
								FRAME_IDX_FIRST=0;
								const int First_Mode=initFirstMode();
								outside08_first_ex(First_Mode);
							}while(0);

							while(	IsCircleRunning(FirstCircle) ){
									usleep(1);
							}

				}else if(GetProjectRun()==inside08){


							for(FRAME_IDX_FIRST=0;
									IsCircleRunning(FirstCircle) && IsFrameCollect(FRAME_IDX_FIRST);
									FRAME_IDX_FIRST++){

									CvtFrame(0,FRAME_IDX_FIRST);


							}

				}else{


				}


		}

		PRINTF_DBG_EX("FPGA>>stop cmd 00 ! \n");

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetMaskSeqFrames()
{
	if(IsWorkMode_OrgImg()){

	}else if(IsWorkMode_DiffImg()){
		return GetMaskSeqChannel_Total_Num();
	}else{

	}

	return INT_MAX;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void theSecondCircleScar()
{
	const int SecondCircle=SECOND_CIRCLE_IO;

	PRINTF_DBG_EX("FPGA>>wait for start cmd 01 ! \n");

	if(wait4Circle(SecondCircle)){

		PRINTF_DBG_EX("FPGA>>start cmd 01 ! \n");
#if TRUE

			const int  MASK_TOTAL_CHANNELS= GetMaskSeqFrames();
			int fi=0;

			for(	fi=0,FRAME_IDX_SECOND=FRAME_IDX_FIRST;
					fi<MASK_TOTAL_CHANNELS && IsCircleRunning(SecondCircle) && IsFrameCollect(FRAME_IDX_SECOND-FRAME_IDX_FIRST);
					fi++,FRAME_IDX_SECOND++){

					int is_org=FALSE;
					if(IsWorkMode_OrgImg()){
						is_org=TRUE;
					}else if(IsWorkMode_DiffImg()){
						is_org=FALSE;
					}else{
						assert(0);
					}

					CvtFrameScar(FRAME_IDX_FIRST,FRAME_IDX_SECOND,is_org,fi);



			}
#endif
		PRINTF_DBG_EX("FPGA>>stop cmd 01 ! \n");

	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void theSecondCircle()
{
	const int SecondCircle=SECOND_CIRCLE_IO;

	PRINTF_DBG_EX("FPGA>>wait for start cmd 01 ! \n");

	if(wait4Circle(SecondCircle)){

		PRINTF_DBG_EX("FPGA>>start cmd 01 ! \n");

			for(FRAME_IDX_SECOND=FRAME_IDX_FIRST;
					IsCircleRunning(SecondCircle) &&  IsFrameCollect(FRAME_IDX_SECOND-FRAME_IDX_FIRST);
					FRAME_IDX_SECOND++){

					CvtFrame(FRAME_IDX_FIRST,FRAME_IDX_SECOND);

			}

		PRINTF_DBG_EX("FPGA>>stop cmd 01 ! \n");

	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void stopThisCircle()
{
		sendImageStop();
		StopFpgaCircleRunning();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void startThisCircle()
{
	sendImageStart();
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
void *fpga_cvt_server(void* _pdata)
{

	int init_stat;
	/*-----------------------------------*/
	while(IsRun()){
		init_stat=init_fpga();
		if(init_stat==TRUE){
			break;
		}else{
			sleep(1);
		}

	}
	/*-----------------------------------*/
	while(IsRun()){

			if(wait4FpgaStart()){

					startThisCircle();

						theFirstCircleScar();

						theSecondCircleScar();

					stopThisCircle();
			}
	}


	ExitFpgaThread();

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
void *axi_rcv_server(void* _pdata)
{
	while(IsRun()){

		if(ProcessImageData==RCV_IMAGE_BY_SELF){

				MESSAGE msg=rcv_queue_img_buff();

				if(msg.message_type==ENOMSG){
					usleep(10);
				}else{

					CMD_CTRL *img_data=msg._data;

					IplImageU* imgU=(IplImageU*)img_data;
					int ch=imgU->IpAddrChannel[0];

					PRINTF_DBG_EX("inner rcv a image Channel:%d\n",ch);

					ReleaseCmdCtrl(&img_data);
				}




		}else{
			sleep(1);
		}

	}

	pthread_exit(NULL);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
pthread_t rcv_image_buff_axi_server(void *_data)
{
	pthread_t _thread_tid;
	if( pthread_create(&_thread_tid, NULL, axi_rcv_server, _data) ){
			PRINTF_DBG_EX(" Create print_thread1 thread error!\n");
			exit(0);
	}
 return _thread_tid;
}
