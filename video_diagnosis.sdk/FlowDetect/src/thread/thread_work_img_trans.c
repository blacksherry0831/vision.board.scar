#include "thread_work_img_trans.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void EnterTcpTransImageThread(int _socket)
{
	PRINTF_DBG_EX("pthread start>> [tcp image transfer thread]\n");

	SetTcpTransImageThreadRunning(TRUE);

	setCurrentThreadHighPriority(1);

	set_socket_buf_size(_socket,16*1024*1024);

	IncTcpTransImgThreads();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ExitTcpTransImageThread()
{
	PRINTF_DBG_EX("pthread close>> [tcp image transfer thread]\n");
	SetTcpTransImageThreadRunning(FALSE);
	DecTcpTransImgThreads();
	pthread_exit(NULL);
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
#if PRINTF_HB
													PRINTF_DBG_EX("DATA@ hearbeat freq(s): %d ",time_step);

													SendHeartbeatCmd_TimeCost(
														sock_server,
														&socket_status,
														HB_NONE,
														GetFrameCircleSeq(),
														"DATA@ TCP SEND Heartbeat cost :");
#else
													socket_status=SendHeartbeatCmd(
														sock_server,
														HB_NONE,
														GetFrameCircleSeq());
#endif

											}
											sleep_1ms();

									}else if(msg.message_type==EIDRM){
											break;
									}else  if(msg.message_type==msgTypeImage()){
													socket_write_1_cmd_release_time_cost(
														sock_server,
														&socket_status,
														img_data,
														"DATA@ tcp SEND frame cost :");
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
pthread_t tcp_image_buff_trans_server(void *_data)
{
	pthread_t _thread_tid;

	TCP_SERVER* tcp_server_data=mem_malloc(sizeof(TCP_SERVER));
		 	 	 	 tcp_server_data->port=TCP_PORT_VIDEO_TRANS;
		 	 	 	 tcp_server_data->pfunClient=tcp_data_transfer_image;

	if( pthread_create(&_thread_tid, NULL, tcp_server, tcp_server_data) ){
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
