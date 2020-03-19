#include "sem_sync.h"
/*-----------------------------------*/
static  sem_t m_sem_fpga_circle_start;
/*-----------------------------------*/
static  sem_t m_sem_fpga_frame_done;
static  sem_t m_sem_dma_frame_done2Mem;
static  sem_t m_sem_dma_frame_done2fpga;
static  sem_t m_sem_memcpy_frame_done;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
static sem_t* SEM[]={	&m_sem_fpga_frame_done,
				&m_sem_dma_frame_done2Mem,
				&m_sem_dma_frame_done2fpga,
				&m_sem_memcpy_frame_done,
				&m_sem_fpga_circle_start
};
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int initSemSignal()
{

	const int SEM_SIZE=sizeof(SEM)/sizeof(sem_t*);
	int i=0;
	for(i=0;i<SEM_SIZE;i++){

		sem_t* sem_ptr=SEM[i];

		int nRet = sem_init(sem_ptr, 0, 0);

		if (0 != nRet){
				 PRINTF_DBG_EX("sem_init _fail");
				 return -1;
		}

	}

	return 1;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

int destorySemSignal()
{
	const int SEM_SIZE=sizeof(SEM)/sizeof(sem_t*);
	int i=0;
		for(i=0;i<SEM_SIZE;i++){

			sem_t* sem_ptr=SEM[i];

			int nRet = sem_destroy(sem_ptr);

			if (0 != nRet){
					 PRINTF_DBG_EX("sem_init _fail");
					 return -1;
			}

		}

		return 1;
}
/*-----------------------------------*/
/**
 *m_sem_fpga_circle_start信号量加1
 */
/*-----------------------------------*/
int  post_fpga_start_sig()
{
	const int result_t=sem_post(&m_sem_fpga_circle_start);  //信号量加1
	sched_yield();  //使另一个级别等于或高于当前线程的线程先运行
	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait_fpga_start_sig()
{
	const int result_t=sem_wait(&m_sem_fpga_circle_start);
	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  post_fpga_cvt_down_sig()
{
	const int result_t=sem_post(&m_sem_fpga_frame_done);
	sched_yield();
	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait_fpga_cvt_down_sig()
{
	const int result_t=sem_wait(&m_sem_fpga_frame_done);
	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  post_dma_cpy_down_sig_2_fpga()
{
	const int result_t=sem_post(&m_sem_dma_frame_done2fpga);
	sched_yield();
	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  wait_dma_cpy_down_sig_4_fpga()
{
	const int result_t=sem_wait(&m_sem_dma_frame_done2fpga);
	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  post_dma_cpy_down_sig_2_memcpy()
{
	const int result_t=sem_post(&m_sem_dma_frame_done2Mem);
	sched_yield();
	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  wait_dma_cpy_down_sig_4_memcpy()
{
	const int result_t=sem_wait(&m_sem_dma_frame_done2Mem);
	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  post_mem_cpy_down_sig()
{
	const int result_t=sem_post(&m_sem_memcpy_frame_done);
	sched_yield();
	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait_mem_cpy_down_sig()
{
	const int result_t=sem_wait(&m_sem_memcpy_frame_done);
	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

