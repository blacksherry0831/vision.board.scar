#include "thread_fpga_cvt.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ExitFpgaThread()
{
	 PRINTF_DBG_EX("pthread close>> [fpga thread]\n");

	 pthread_exit(NULL);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void CheckFpgaStatus()
{
		int init_stat;
		int count_t=0;

		while(IsRun()){

			init_stat=init_fpga();
			if(init_stat==TRUE){
				break;
			}else{
				sleep(1);
			}
			if(count_t++>10)
			{
				break;
			}
		}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void *fpga_cvt_server(void* _pdata)
{

	CheckFpgaStatus();

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
pthread_t init_fpga_cvt_server(void *_data)
{
	pthread_t _thread_tid;
	if( pthread_create(&_thread_tid, NULL, fpga_cvt_server, _data) ){
			PRINTF_DBG_EX(" Create print_thread1 thread error!\n");
			exit(0);
	}
 return _thread_tid;
}
