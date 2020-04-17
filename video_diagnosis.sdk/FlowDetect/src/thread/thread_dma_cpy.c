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
void dmac_trans_all_frame_cost_time()
{
	static int DMA_COUNT=0;
#if defined(_DEBUG) && defined(_DEBUG_WF)
					TIME_START();
#endif
					dmac_trans_all_frame();
#if defined(_DEBUG) && defined(_DEBUG_WF)
					TIME_END("2> DMA cpy cost time");
#endif
#if defined(_DEBUG) && defined(_DEBUG_WF)
					PRINTF_DBG_EX("DMA:%d___",DMA_COUNT++);
#endif
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void dmac_trans_all_frame_sync()
{
	if(wait_fpga_cvt_down_sig()==SUCCESS){

										if(SUCCESS==PL_MEM_48_Lock()){

																				if(SUCCESS==PS_MEM_04_Lock()){

																					dmac_trans_all_frame_cost_time();

																					if(SUCCESS==PS_MEM_04_Unlock()){


																					}
																				}

											if(SUCCESS==PL_MEM_48_Unlock()){

												post_dma_cpy_down_sig_2_fpga();
												post_dma_cpy_down_sig_2_memcpy();
												wait_mem_cpy_down_sig();

											}

										}

	}
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void *dma_work_server(void* _pdata)
{

	while(IsRun())
	{

		 dmac_trans_all_frame_sync();
		 sleep_1ms_yield();

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
