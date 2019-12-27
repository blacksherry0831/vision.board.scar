#include "fpga_base.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4FpgaConvertDone()
{
    int result_t=FALSE;

#ifdef _DEBUG
    struct timeval startTime,endTime;
    float Timeuse=0;
    int print_count=1;
    gettimeofday(&startTime,NULL);
#endif
		while(IsCircleTaskRunning()){

			if(fpga_is_busy()==TRUE){

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
