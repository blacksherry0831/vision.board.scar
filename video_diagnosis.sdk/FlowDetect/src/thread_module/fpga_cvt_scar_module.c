#include "fpga_cvt_scar_module.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4FpgaScarConvertDone()
{
    int result_t=FALSE;

#ifdef _DEBUG
    struct timeval startTime,endTime;
    float Timeuse=0;
    int print_count=1;
    gettimeofday(&startTime,NULL);
#endif
		while(IsCircleTaskRunning()){

			if(fpga_scar_is_busy()==TRUE){

				sleep_1ms();
			}else{
				result_t=TRUE;//now free
				break;
			}
#ifdef _DEBUG
			gettimeofday(&endTime,NULL);
			Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);

			float TimeuseMs=Timeuse/1000;
			if(TimeuseMs>1000*print_count){
				print_count++;
				PRINTF_DBG_EX("FPGA CVT>>wait busy cost time: %f ms\n",TimeuseMs);
			}
#endif
		}

	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void scar_cvt(int _org,const int _fi)
{
	wait4FpgaScarConvertDone();
	{
		fpga_img_scar_detect_reset();

			if(_org){
				fpga_img_scar_detect_mode(0);
				fpga_img_scar_detect_set_mask_addr_1(0);
			}else{
				set_mask_seq_param(_fi);
			}

		fpga_img_scar_detect_start_en();
	}
	wait4FpgaScarConvertDone();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void printf_dbg_fpga_scar_param()
{

	const int work_mode=getFpgaCircleWorkMode();

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
		result_t=post_fpga_start_sig();
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
void theFirstCircleScar()
{


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
void scar_second_sync(int _frame_idx,const int _org,const int _fi)
{
	static int FPGA_COUNT=0;
	if(pthread_mutex_lock(&FPGA_mutex_cvt)==SUCCESS){

				TIME_START();

					scar_cvt(_org,_fi);

					PRINTF_DBG_EX("FPGA:%d___",FPGA_COUNT++);

				TIME_END("1> FPGA Convert cost time : ");

				if(pthread_mutex_unlock(&FPGA_mutex_cvt)==SUCCESS){
						post_fpga_cvt_down_sig();
						wait_dma_cpy_down_sig_4_fpga();

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


	PRINTF_DBG_EX("FPGA>>wait for start cmd 01 ! \n");

	if(wait4Circle2nd()){
		PRINTF_DBG_EX("FPGA>>start cmd 01 ! \n");
				if(GetProjectRun()==scar_detect_01){

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
				}
		PRINTF_DBG_EX("FPGA>>stop cmd 01 ! \n");
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
