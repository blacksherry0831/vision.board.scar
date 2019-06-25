#include "dma2mem.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
pthread_mutex_t MEM_mutex_cpy = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  MEM_cond_cpy=PTHREAD_COND_INITIALIZER;
unsigned int    MEM_CpyDone=FALSE;

volatile unsigned int    MEM_CpyDone00=FALSE;
volatile unsigned int    MEM_CpyDone01=FALSE;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void MemCpyDone()
{
	pthread_mutex_lock(&MEM_mutex_cpy);//
	MEM_CpyDone=TRUE;
	pthread_cond_broadcast(&MEM_cond_cpy);
	pthread_mutex_unlock(&MEM_mutex_cpy);//
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int Wait4MemCpyDone(long timeout_ms)
{
	int reslut_t=Wait4Signal(timeout_ms,&MEM_mutex_cpy,&MEM_cond_cpy);

	return reslut_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int memcpyDMA2Mem_send2MsgQ(CMD_CTRL* _img,unsigned int _ch)
{

		if(GetGlobalChannelMask(_ch)){

			if(_img!=NULL){
				  memcpyDMA2MemChEx(_img,_ch);

				  snd_queue_img_buff(_img);
				  return 1;
			}

		}

		return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void *memcpy_work_server(void* _pdata)
{
	static int MEMCPY_COUNT=0;
	int Chn_num=0;



	CMD_CTRL*  image[8];

	setCurrentThreadHighPriority(1);

	while(IsMemCpyRun()){

			if(sem_wait_infinite(&m_sem_dma_frame_done2Mem)==SUCCESS){

							if(pthread_mutex_lock(&DMA_mutex_trans0)==SUCCESS){

										TIME_START();
												IncFrameIdx();
												const unsigned int IMG_FRAME_IDX=getFrameIdx();
												int sensor_stat=GetSensorStat();
												MallocImageBuff(image,IMG_FRAME_IDX,8);
												for(Chn_num=0;Chn_num<8;Chn_num++){
													 /*****************************/
																CMD_CTRL* cmd_ctrl_pt=image[Chn_num];
																SetSensorStatus(cmd_ctrl_pt,sensor_stat,Chn_num);
																memcpyDMA2Mem_send2MsgQ(cmd_ctrl_pt,Chn_num);
													 /*****************************/
												  }
										 PRINTF_DBG("MEMCPY:%d___",MEMCPY_COUNT++);
										 TIME_END("3>MEM cpy cost time");

										 sem_post(&m_sem_memcpy_frame_done);
										 pthread_mutex_unlock(&DMA_mutex_trans0);


							}
			}

			 sched_yield();

	}

	ExitMemCpyThread();

}

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
pthread_t init_memcpy_server(void *_data)
{
	pthread_t _thread_tid;
	if( pthread_create(&_thread_tid, NULL,memcpy_work_server, _data) ){
			PRINTF_DBG(" Create print_thread1 thread error!\n");
			exit(0);
	}

 return _thread_tid;
}
