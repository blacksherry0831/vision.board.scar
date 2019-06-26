
#include "axi.h"
/*-----------------------------------*/
int FPGA_CONVERT_DONE=FALSE;
/*-----------------------------------*/
int FRAME_IDX_FIRST=0;
/*-----------------------------------*/
int FRAME_IDX_SECOND=0;
/*-----------------------------------*/
enum CircleFlag
{
	FIRST_CIRCLE_IO=0x00,
	SECOND_CIRCLE_IO=0x01,
};
/*-----------------------------------*/
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
pthread_cond_t 	mCondFpgaStartStep_1=PTHREAD_COND_INITIALIZER;
pthread_mutex_t mMutexFpga=PTHREAD_MUTEX_INITIALIZER;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsCircleTaskRunning()
{
	return IsFpgaCircleRunning() && IsRun();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
volatile int ProcessImageData=0;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4FpgaStart()
{
	PRINTF_DBG("FPGA>>wait for start cmd ! \n");

	if(Wait4StartFpgaCircle()==SUCCESS){
		return TRUE;
	}else{
		ExitFpgaThread();
	}

	return FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4Circle(const int _first_second)
{

		while(IsCircleTaskRunning()){

					if(_first_second==FIRST_CIRCLE_IO){

							if(TRUE==IsFpgaTaskFirstStart()){
								return TRUE;
							}

					}else if(_first_second==SECOND_CIRCLE_IO){

							if(TRUE==IsFpgaTaskSecondStart()){
								return TRUE;
							}
					}else{


					}

					usleep(1);

		}

	return FALSE;
}

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsCircleRunning(const int _first_second)
{
	const int IsCircleRunning=IsCircleTaskRunning();

				if(_first_second==0x00){

					 return IsCircleRunning && IsFpgaTaskFirstStart();

				}else if(_first_second==0x01){

					 return IsCircleRunning && IsFpgaTaskSecondStart();

				}else{


				}


}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int  initFirstMode()
{
	int First_Mode=0;
		if(WM_ORG_IMG==(GetFpgaCircleWorkMode()&WM_ORG_IMG)){
			First_Mode=FPGA_WORK_MODE_DATA_ZERO;
		}else if(WM_DIFF_IMG==(GetFpgaCircleWorkMode()&WM_DIFF_IMG)){
			First_Mode=FPGA_WORK_MODE_DATA_AVG;
		}else{

		}
	return First_Mode;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsFrameCollect(int _current_idx)
{

	if(_current_idx<GetFrameIdxMax()){
		return TRUE;
	}else{
		return FALSE;
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void CvtFrame(unsigned int _base_idx,unsigned int current_idx)
{
	const unsigned int relative_idx=current_idx-_base_idx;

	if(		(relative_idx>=GetFrameIdxMin())&&
			(relative_idx<=GetFrameIdxMax())
			){
			outside_second_sync(current_idx);
	}else{
			sleepMS(100);
			IncFrameIdx();
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void theFirstCircle()
{
		const int FirstCircle=FIRST_CIRCLE_IO;

		PRINTF_DBG("FPGA>>wait for start cmd 00 ! \n");

		if(wait4Circle(FirstCircle)){

			PRINTF_DBG("FPGA>>start cmd 00 ! \n");

				if(GetProjectRun()==outside08){

							do{
								FRAME_IDX_FIRST=0;
								const int First_Mode=initFirstMode();
								outside08_first_ex(First_Mode);
							}while(0);

							while(	IsCircleRunning(FirstCircle) ){
									usleep(1);
							}

				}else if(GetProjectRun()==inside08){


							for(FRAME_IDX_FIRST=0;
									IsCircleRunning(FirstCircle) && IsFrameCollect(FRAME_IDX_FIRST);
									FRAME_IDX_FIRST++){

									CvtFrame(0,FRAME_IDX_FIRST);


							}

				}else{


				}


		}

		PRINTF_DBG("FPGA>>stop cmd 00 ! \n");

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void theSecondCircle()
{
	const int SecondCircle=SECOND_CIRCLE_IO;

	PRINTF_DBG("FPGA>>wait for start cmd 01 ! \n");

	if(wait4Circle(SecondCircle)){

		PRINTF_DBG("FPGA>>start cmd 01 ! \n");

			for(FRAME_IDX_SECOND=FRAME_IDX_FIRST;
					IsCircleRunning(SecondCircle) &&  IsFrameCollect(FRAME_IDX_SECOND-FRAME_IDX_FIRST);
					FRAME_IDX_SECOND++){

					CvtFrame(FRAME_IDX_FIRST,FRAME_IDX_SECOND);

			}

		PRINTF_DBG("FPGA>>stop cmd 01 ! \n");

	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void stopThisCircle()
{
		sendImageStop();
		StopFpgaCircleRunning();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void startThisCircle()
{
	sendImageStart();
	PRINTF_DBG("FPGA>>Start FPGA Circle \n");
	sleepMS(100);
	sendImageMask();
	PRINTF_DBG("FPGA>>Send Mask Image \n");
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void *fpga_cvt_server(void* _pdata)
{

	int init_stat;
	/*-----------------------------------*/
	while(IsRun()){
		init_stat=init_fpga();
		if(init_stat==TRUE){
			break;
		}else{
			sleep(1);
		}

	}
	/*-----------------------------------*/
	while(IsRun()){

			if(wait4FpgaStart()){

					startThisCircle();

						theFirstCircle();

						theSecondCircle();

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

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void *axi_rcv_server(void* _pdata)
{
	while(IsRun()){

		if(ProcessImageData==RCV_IMAGE_BY_SELF){

				MESSAGE msg=rcv_queue_img_buff();

				if(msg.message_type==ENOMSG){
					usleep(10);
				}else{

					CMD_CTRL *img_data=msg._data;

					IplImageU* imgU=(IplImageU*)img_data;
					int ch=imgU->IpAddrChannel[0];

					PRINTF_DBG("inner rcv a image Channel:%d\n",ch);

					ReleaseCmdCtrl(&img_data);
				}




		}else{
			sleep(1);
		}

	}

	pthread_exit(NULL);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
pthread_t rcv_image_buff_axi_server(void *_data)
{
	pthread_t _thread_tid;
	if( pthread_create(&_thread_tid, NULL, axi_rcv_server, _data) ){
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
void* tcp_data_transfer_image(void *_data)
{

	int *_clientfd_p=(int*)_data;
	int sock_server=*_clientfd_p;
	int socket_status=TRUE;
	//const int time_us=0;
	time_t seconds_old = time(NULL);
	const int time_step=HEART_BEAT_FREQUENCY;
	//struct timeval startTime,endTime;
	//float Timeuse;
	mem_free_clr(&_data);

	EnterTcpTransImageThread(sock_server);

	/*-----------------------------------*/
		while(IsTcpTransImageRun() && socket_status){

									MESSAGE msg=rcv_queue_img_buff();

									CMD_CTRL *img_data=msg._data;

									if(msg.message_type==ENOMSG){

											time_t seconds_new = time(NULL);
											if(seconds_new-seconds_old>time_step){

												seconds_old=time(NULL);
												PRINTF_DBG("!hearbeat freq(s): %d ",time_step);
												TIME_START();
												 socket_status=SendHeartbeatCmd(sock_server,HB_NONE,GetFrameCircleSeq());
												TIME_END("!tcp send a Heartbeat cost :");


											}
											sleep_1ms();

									}else if(msg.message_type==EIDRM){
											break;
									}else  if(msg.message_type==msgTypeImage()){
										TIME_START();
										 	 socket_status=socket_write_1_cmd_release(sock_server,img_data);
										TIME_END("tcp send a frame cost :");
									}else{
											DEBUG_PRINT("message queue: message_type error\n");
									}



					}
	/*-----------------------------------*/
		close(sock_server);
		ExitTcpTransImageThread();

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
pthread_t tcp_image_buff_axi_server(void *_data)
{
	pthread_t _thread_tid;

	TCP_SERVER* tcp_server_data=mem_malloc(sizeof(TCP_SERVER));
		 	 	 	 tcp_server_data->port=TCP_PORT_VIDEO_TRANS;
		 	 	 	 tcp_server_data->pfunClient=tcp_data_transfer_image;

	if( pthread_create(&_thread_tid, NULL, tcp_server, tcp_server_data) ){
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
