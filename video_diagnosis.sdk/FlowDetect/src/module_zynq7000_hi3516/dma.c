#include "dma.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
pthread_mutex_t DMA_mutex_trans0 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t DMA_mutex_trans1 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t  DMA_cond_trans0=PTHREAD_COND_INITIALIZER;

pthread_cond_t  DMA_cond_trans1=PTHREAD_COND_INITIALIZER;

unsigned int    DMA_TransDone=FALSE;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void DmaTransDone01()
{
	pthread_mutex_lock(&DMA_mutex_trans0);//
		DMA_TransDone=TRUE;
	pthread_cond_signal(&DMA_cond_trans0);
	pthread_mutex_unlock(&DMA_mutex_trans0);//

	pthread_mutex_lock(&DMA_mutex_trans1);//
		DMA_TransDone=TRUE;
	pthread_cond_signal(&DMA_cond_trans1);
	pthread_mutex_unlock(&DMA_mutex_trans1);//

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int Wait4DmaTransDone0(long timeout_ms)
{
	int reslut_t=Wait4Signal(timeout_ms,&DMA_mutex_trans0,&DMA_cond_trans0);
	PRINTF_DBG("get DMA signal 00 \n");
	return reslut_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int SetDmaFrameByWorkMode(int _wm)
{

			if(GetProjectRun()==outside08){

					SetCurrentDmaFrame(0);

			}else if(GetProjectRun()==inside08){

			if(WM_ORG_IMG==(GetFpgaCircleWorkMode()&WM_ORG_IMG)){
					SetCurrentDmaFrame(0);
			}else if(WM_DIFF_IMG==(GetFpgaCircleWorkMode()&WM_DIFF_IMG)){
					SetCurrentDmaFrame(1);
			}else{

			}

	}else{


	}
	return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int Wait4DmaTransDone1(long timeout_ms)
{
	int reslut_t=Wait4Signal(timeout_ms,&DMA_mutex_trans1,&DMA_cond_trans1);
	PRINTF_DBG("get DMA signal 01 \n");
	return reslut_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetFrameSizeOut08(int _frame)
{

	unsigned int  MAP_SIZE=0;
		if(_frame>=0&&_frame<=7){

				MAP_SIZE=image_size_frame();
		}else	if(_frame==-1){

				MAP_SIZE=IMAGE_SIZE_AVG;
		}else{
			assert(0);
		}
	return MAP_SIZE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetFrameSizeIn08(int _frame)
{

	unsigned int  MAP_SIZE=0;
		if(_frame>=0&&_frame<=7){

				MAP_SIZE=image_size_frame();
		}else	if(_frame==-1){

				MAP_SIZE=IMAGE_SIZE_AVG;
		}else{
			assert(0);
		}
	return MAP_SIZE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetFrameSize(int _frame)
{
	enum ProjectRun pr_t=GetProjectRun();

	if(pr_t==outside08){
		return GetFrameSizeOut08(_frame);
	}else if(pr_t==inside08){
		return GetFrameSizeIn08(_frame);
	}else{

	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void dmac_trans_ex(unsigned char _ch,int _frame)
{

	if(GetGlobalChannelMask(_ch)){
			dmac_trans(_ch,_frame);
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
