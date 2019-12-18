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
	return IsCircleTaskRunning_FpgaCvt() && IsRun();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4FpgaStart()
{
	PRINTF_DBG_EX("FPGA Cvt >>wait for start cmd ! \n");

	if(Wait4StartFpgaCircle()==SUCCESS){
		return TRUE;
	}else{
		ExitFpgaThread();
		exit(-1);
	}

	return FALSE;
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
int IsFrameCollect(const unsigned int _current_idx)
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

			if(wait4Circle1st()){

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

		if(wait4Circle1st()){

			PRINTF_DBG_EX("FPGA>>start cmd 00 ! \n");

				if(GetProjectRun()==outside08){

							do{
								FRAME_IDX_FIRST=0;
								const int First_Mode=initFirstMode();
								outside08_first_ex(First_Mode);
							}while(0);

							while(	IsFirstCircleRunning() ){
									usleep(1);
							}

				}else if(GetProjectRun()==inside08){


							for(FRAME_IDX_FIRST=0;
									IsFirstCircleRunning() && IsFrameCollect(FRAME_IDX_FIRST);
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
		return GetScarMaskChannel_Total_Num();
	}else{

	}

	return INT_MAX;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsScarWorkMode_Org()
{
	int is_org=FALSE;
		if(IsWorkMode_OrgImg()){
			is_org=TRUE;
		}else if(IsWorkMode_DiffImg()){
			is_org=FALSE;
		}else{
			assert(0);
		}
	return is_org;
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

	if(wait4Circle2nd()){

		PRINTF_DBG_EX("FPGA>>start cmd 01 ! \n");
#if TRUE

			int fi=0;

			for(	fi=0,FRAME_IDX_SECOND=FRAME_IDX_FIRST;
					IsSecondCircleRunning() && IsFrameCollect(FRAME_IDX_SECOND-FRAME_IDX_FIRST);
					fi++,FRAME_IDX_SECOND++){


					const int  MASK_TOTAL_FRAMES	= GetMaskSeqFrames();
					const int  MASK_LOOP			= GetScarMaskSeqChannel_Is_Loop();
					const int  MASK_SNO				= GetScarMaskSeq_SNO();

					if(fi>=MASK_TOTAL_FRAMES){
						if(MASK_LOOP==FALSE){
							break;
						}else{
							fi=0;
						}
					}

					if(fi==0){
						sendImageStart_DetectSno(MASK_TOTAL_FRAMES,MASK_SNO);
					}else{
						//normal fpga cvt
					}

					const int is_org=IsScarWorkMode_Org();

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

	if(wait4Circle2nd()){

		PRINTF_DBG_EX("FPGA>>start cmd 01 ! \n");

			for(FRAME_IDX_SECOND=FRAME_IDX_FIRST;
					IsSecondCircleRunning() &&  IsFrameCollect(FRAME_IDX_SECOND-FRAME_IDX_FIRST);
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

