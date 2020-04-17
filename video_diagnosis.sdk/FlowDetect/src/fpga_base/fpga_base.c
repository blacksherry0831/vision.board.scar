#include "fpga_base.h"
/*-----------------------------------*/
static unsigned int FPGA_ERROR=FPGA_NO_ERR;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetFpgaError()
{
	const unsigned int err_t=FPGA_ERROR;
	 FPGA_ERROR=FPGA_NO_ERR;
	return err_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int SetFpgaError(const unsigned int _err,const unsigned int _sensor)
{

	unsigned int err_t= _err<<16 |_sensor;

	FPGA_ERROR |=err_t;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4FpgaConvertDone_in()
{
    int result_t=FALSE;


    struct timeval startTime,endTime;
    float Timeuse=0;

    gettimeofday(&startTime,NULL);

		while(IsCircleTaskRunning()){

			if(fpga_is_busy()==TRUE){

				sleep_1ms_yield();
			}else{
				result_t=TRUE;//now free
				break;
			}

			gettimeofday(&endTime,NULL);
			Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);

			float TimeuseMs=Timeuse/1000;
			if(TimeuseMs>1000){
				result_t=FALSE;
				break;
				PRINTF_DBG_EX("FPGA CVT>>wait busy cost time: %f ms\n",TimeuseMs);
			}

		}

	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4FpgaConvertDone()
{
    int result_t=wait4FpgaConvertDone_in();

    if(result_t==FALSE){
       	 SetFpgaError(FPGA_ERR_BUSY,0);
    }


	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

