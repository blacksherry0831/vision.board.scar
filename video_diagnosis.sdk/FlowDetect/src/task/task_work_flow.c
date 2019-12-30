#include "task_work_flow.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  initFirstMode()
{
	int First_Mode=0;
		if(WM_ORG_IMG==(getFpgaCircleWorkMode()&WM_ORG_IMG)){
			First_Mode=FPGA_WORK_MODE_DATA_ZERO;
		}else if(WM_DIFF_IMG==(getFpgaCircleWorkMode()&WM_DIFF_IMG)){
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
void scar_second_sync(int _frame_idx,const int _org,const int _fi)
{
	static int FPGA_COUNT=0;
	if(SUCCESS==PL_MEM_48_Lock()){

				TIME_START();

					scar_cvt(_org,_fi);

					PRINTF_DBG_EX("FPGA:%d___",FPGA_COUNT++);

				TIME_END("1> FPGA Convert cost time : ");

				if(SUCCESS==PL_MEM_48_Unlock()){
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
