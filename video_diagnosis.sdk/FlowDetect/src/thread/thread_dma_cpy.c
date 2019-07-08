#include "thread_dma_cpy.h"
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

	while(IsDMARun())
	{

								if(sem_wait_infinite(&m_sem_fpga_frame_done)!=SUCCESS) break;

								if(pthread_mutex_lock(&FPGA_mutex_cvt)==SUCCESS){

												if(pthread_mutex_lock(&DMA_mutex_trans0)==SUCCESS){

																	TIME_START();

																		dmac_trans_all_frame();

																		PRINTF_DBG("DMA:%d___",DMA_COUNT++);

																	TIME_END("2> DMA cpy cost time");

																	if(pthread_mutex_unlock(&DMA_mutex_trans0)==SUCCESS){

																			if(pthread_mutex_unlock(&FPGA_mutex_cvt)==SUCCESS){

																						sem_post(&m_sem_dma_frame_done2Mem);
																						sem_post(&m_sem_dma_frame_done2fpga);
																						sched_yield();
																						sem_wait_infinite(&m_sem_memcpy_frame_done);


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
			PRINTF_DBG(" Create print_thread1 thread error!\n");
			exit(0);
	}
 return _thread_tid;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
