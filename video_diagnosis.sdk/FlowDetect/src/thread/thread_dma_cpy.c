#include "thread_dma_cpy.h"
/*-----------------------------------*/
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ExitDmaThread()
{
	 PRINTF_DBG_EX("pthread close>> [dma thread]\n");

	 pthread_exit(NULL);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void *dma_work_server(void* _pdata)
{
	int chi=0;
	//const unsigned time_ms=30*1000;
	static int DMA_COUNT=0;

	while(IsRun())
	{

					if(wait_fpga_cvt_down_sig()==SUCCESS)
					{

									if(pthread_mutex_lock(&FPGA_mutex_cvt)==SUCCESS){

														if(pthread_mutex_lock(&DMA_mutex_trans0)==SUCCESS){

																			TIME_START();

																				dmac_trans_all_frame();

																			PRINTF_DBG_EX("DMA:%d___",DMA_COUNT++);

																			TIME_END("2> DMA cpy cost time");

																			if(pthread_mutex_unlock(&DMA_mutex_trans0)==SUCCESS){

																						if(pthread_mutex_unlock(&FPGA_mutex_cvt)==SUCCESS){

																							post_dma_cpy_down_sig_2_fpga();
																							post_dma_cpy_down_sig_2_memcpy();
																							wait_mem_cpy_down_sig();

																						}
																			}

														}

									}



					}

	}

	ExitDmaThread();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
pthread_t init_dma_server(void *_data)
{
	pthread_t _thread_tid;
	if( pthread_create(&_thread_tid, NULL, dma_work_server, _data) ){
			PRINTF_DBG_EX(" Create print_thread1 thread error!\n");
			exit(0);
	}
 return _thread_tid;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
