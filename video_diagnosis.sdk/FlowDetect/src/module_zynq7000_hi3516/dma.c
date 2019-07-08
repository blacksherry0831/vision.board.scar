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
							image_enable_output_frame_only_1();
			}else if(GetProjectRun()==inside08){

						if(WM_ORG_IMG==(GetFpgaCircleWorkMode()&WM_ORG_IMG)){
							image_enable_output_frame_only_1();
						}else if(WM_DIFF_IMG==(GetFpgaCircleWorkMode()&WM_DIFF_IMG)){
							image_enable_output_frame_only_2();
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
void dmac_trans_space_ch_fr(int _space_ch,int _space_fr)
{

	dmac_trans_2(_space_ch,_space_fr);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void dmac_trans_all_frame()
{

		int schi=0;
		int sfri=0;

		for(schi=0; schi <SPACE_CHANNEL_NUM;schi++){
			for(sfri=0;sfri<SPACE_FRAME_NUM;sfri++){
					if(is_space_frame_output(schi,sfri)){

						dmac_trans_space_ch_fr(schi,sfri);

					}
			}
		}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
