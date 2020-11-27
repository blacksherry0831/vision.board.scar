#include "thread_mem_cpy.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ExitMemCpyThread()
{
	PRINTF_DBG_EX("pthread close>> [memcpy thread]\n");

	pthread_exit(NULL);
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
void memcpy_once_frame(
		const char* _prj,
		const int _total,
		const int _idx)
{
			CMD_CTRL*  image[SPACE_CHANNEL_NUM][SPACE_FRAME_NUM];
					memset(image,0,sizeof(image));

					const int FPGA_ERR=GetFpgaError();
					const int CIRCLE_SEQ=GetFrameCircleSeq();
					const int ViewOutputNum=img_space_frame_output_num();

					MallocImageBuff4ViewOutput(
							&image[0][0],
							CIRCLE_SEQ,
							_prj,
							_total,
							_idx);

#if 1
						int schi=0;
						int sfri=0;

						for(schi=0; schi <SPACE_CHANNEL_NUM;schi++){
							for(sfri=0;sfri<SPACE_FRAME_NUM;sfri++){
									if(image[schi][sfri]!=NULL){
										 /*****************************/
												CMD_CTRL* cmd_ctrl_pt=image[schi][sfri];
												if(cmd_ctrl_pt!=NULL){

														const int view_ch=GetCmdImgViewChannel(cmd_ctrl_pt);
														SetFpgaStatus(cmd_ctrl_pt,FPGA_ERR,view_ch);
														memcpyDMA2Mem_send2MsgQ(cmd_ctrl_pt,schi,sfri);
												}
										 /*****************************/
									}
									image[schi][sfri]=NULL;
							}
						}
#endif


}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void memcpy_once()
{
		//frame idx from 1 to N;
		const  int IMG_FRAME_IDX=getFrameIdx();
		{
				int MASK_TOTAL_FRAMES=INT_MAX;
				const char *prj=GetProjectRunStr();

				if(IsProjectRun(flame_monitor)){

				}else if(IsProjectRun(scar_detect_01)){
					MASK_TOTAL_FRAMES	= GetMaskSeqFrames();
				}else{
						assert(0);
				}

				memcpy_once_frame(prj,MASK_TOTAL_FRAMES,IMG_FRAME_IDX);
		}
		IncFrameIdx();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void memcpy_once_cost_time()
{
	static int MEMCPY_COUNT=0;

#if defined(_DEBUG) && defined(_DEBUG_WF)
		TIME_START();
#endif

		memcpy_once();

#if defined(_DEBUG) && defined(_DEBUG_WF)
		PRINTF_DBG_EX("MEMCPY:%d___",MEMCPY_COUNT++);
		TIME_END("3>MEM cpy cost time");
#endif

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void memcpy_once_sync()
{
	if(SUCCESS==wait_dma_cpy_down_sig_4_memcpy()){

								if(SUCCESS==PS_MEM_04_Lock()){

											memcpy_once_cost_time();

											 post_mem_cpy_down_sig();

											 if(SUCCESS==PS_MEM_04_Unlock()){

											 }

								}
				}
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void *memcpy_work_server(void* _pdata)
{

	while(IsRun()){

			memcpy_once_sync();

			sleep_1ms_yield();

	}

	ExitMemCpyThread();

	return EXIT_SUCCESS;

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
			PRINTF_DBG_EX(" Create print_thread1 thread error!\n");
			exit(0);
	}

 return _thread_tid;
}
