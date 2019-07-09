#include "thread_mem_cpy.h"
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
int memcpyDMA2Mem_send2MsgQ(CMD_CTRL* _img,const  int _space_ch,const int _space_fr)
{



			if(_img!=NULL){
				  memcpyDMA2MemChEx(_img,_space_ch,_space_fr);

				  snd_queue_img_buff(_img);
				  return 1;
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

	CMD_CTRL*  image[SPACE_CHANNEL_NUM][SPACE_FRAME_NUM];
	memset(image,0,sizeof(image));

	setCurrentThreadHighPriority(1);

	while(IsMemCpyRun()){

			if(sem_wait_infinite(&m_sem_dma_frame_done2Mem)==SUCCESS){

							if(pthread_mutex_lock(&DMA_mutex_trans0)==SUCCESS){

										TIME_START();
														IncFrameIdx();

														const unsigned int IMG_FRAME_IDX=getFrameIdx();
														const int SENSOR_STATUS=GetSensorStat_T();
														const int CIRCLE_SEQ=GetFrameCircleSeq();
														const int ViewOutputNum=img_space_frame_output_num();

														MallocImageBuff4ViewOutput(image,CIRCLE_SEQ,IMG_FRAME_IDX);

															int schi=0;
															int sfri=0;

															for(schi=0; schi <SPACE_CHANNEL_NUM;schi++){
																for(sfri=0;sfri<SPACE_FRAME_NUM;sfri++){
																		if(image[schi][sfri]!=NULL){
																			 /*****************************/
																					CMD_CTRL* cmd_ctrl_pt=image[schi][sfri];
																					if(cmd_ctrl_pt!=NULL){

																							const int view_ch=GetCmdImgViewChannel(cmd_ctrl_pt);

																							SetSensorStatus(cmd_ctrl_pt,SENSOR_STATUS,view_ch);
																							memcpyDMA2Mem_send2MsgQ(cmd_ctrl_pt,schi,sfri);
																					}
																			 /*****************************/
																		}
																		image[schi][sfri]=NULL;
																}
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
