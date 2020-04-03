#include "thread_work_img_trans.h"
/*-----------------------------------*/
/**
 *向socket写入心跳包命令并发送
 */
/*-----------------------------------*/
int SendHeartbeatCmd_Ex(
		const int 	_socketfd,
		int*		_status,
		const int 	_need_resp,
		const int 	_seq,
		const char* _msg)
{
#if PRINTF_HB
				SendHeartbeatCmd_TimeCost(
											_socketfd,
											_status,
											_need_resp,
											_seq,
											_msg);
#else
				*_status=SendHeartbeatCmd(
										_socketfd,
										_need_resp,
										GetFrameCircleSeq());  //向socket写入心跳包命令并发送
#endif
}
/*-----------------------------------*/
/**
 *进入客户端交互线程的准备
 */
/*-----------------------------------*/
void EnterTcpTransImageThread()
{
	PRINTF_DBG_EX("pthread start>> [tcp image transfer thread]\n");
	IncTcpTransImgThreads();  //客户端交互线程数 加1
}
/*-----------------------------------*/
/**
 *退出客户端交互线程的清理
 */
/*-----------------------------------*/
void ExitTcpTransImageThread()
{
	PRINTF_DBG_EX("pthread close>> [tcp image transfer thread]\n");
	DecTcpTransImgThreads();
	pthread_exit(NULL);  //客户端交互线程数 减1
}
/*-----------------------------------*/
/**
 *客户端交互线程-起始函数
 */
/*-----------------------------------*/
void* tcp_data_transfer_image(void *_data)
{
	int *_clientfd_p=(int*)_data;  //客户端交互线程描述符
	const int sock_server=*_clientfd_p;
	int socket_status=TRUE;
	int socket_read_stat=TRUE;
	//const int time_us=0;
	time_t seconds_old = time(NULL);
	const int time_step=HEART_BEAT_FREQUENCY;
	//struct timeval startTime,endTime;
	//float Timeuse;
	struct timeval oldTime,newTime;
	gettimeofday(&oldTime, NULL);
	int oldTime_ms = (double)oldTime.tv_sec * 1000 + (double)oldTime.tv_usec / 1000;

	mem_free_clr(&_data);

	CMD_CTRL*  cmd_resp_t=CreateCmdCtrl(2);
	EnterTcpTransImageThread();  //进入客户端交互线程的准备

	/*-----------------------------------*/
	while(IsRun() && socket_status && socket_read_stat){
		MESSAGE msg=rcv_queue_img_buff_ex();  //从图片消息队列中，读取第一个图片数据

		CMD_CTRL *img_data=(CMD_CTRL *) msg._data;

		if(msg.message_type==ENOMSG){  //队列中无数据
			//time_t seconds_new = time(NULL);
			gettimeofday(&newTime, NULL);
			int newTime_ms = (double)newTime.tv_sec * 1000 + (double)newTime.tv_usec / 1000;

			//5秒发送一次心跳包
			//if(seconds_new-seconds_old>time_step){
			int heart_beat_time = GetHeartBeatTime();
			if(heart_beat_time <= 0)
			{
				heart_beat_time = 5000;
				SetHeartBeatTime(heart_beat_time);
				StoreImgCfgJson();
			}

			if(newTime_ms-oldTime_ms>heart_beat_time){
				//seconds_old=time(NULL);
				oldTime_ms = newTime_ms;
#if PRINTF_HB
				PRINTF_DBG_EX("DATA@ hearbeat freq(ms): %d ",heart_beat_time);
#endif
			//向socket写入心跳包命令并发送
			SendHeartbeatCmd_Ex(
					sock_server,
					&socket_status,
					HB_RESP,
					GetFrameCircleSeq(),
					"DATA@ TCP SEND Heartbeat cost :");

			socket_read_stat=socket_read_1_cmd(sock_server,cmd_resp_t);  //从socket读取一条cmd数据


			}

			sleep_1ms();
		}else if(msg.message_type==EIDRM){  //标识符为msqid的消息队列已被删除
			break;
		}else  if(msg.message_type==msgTypeImage()){

			//向socket写入一条cmd并释放空间，并计时
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
	ReleaseCmdCtrl(&cmd_resp_t);
	ExitTcpTransImageThread();  //退出客户端交互线程的清理

}
/*-----------------------------------*/
/**
 *创建与IPC交互的服务端线程
 */
/*-----------------------------------*/
pthread_t tcp_image_buff_trans_server(void *_data)
{
	pthread_t _thread_tid;

	TCP_SERVER* tcp_server_data=(TCP_SERVER*) mem_malloc(sizeof(TCP_SERVER));  //申请空间
	tcp_server_data->port=TCP_PORT_VIDEO_TRANS;  //端口 10001
	tcp_server_data->pfunClient=tcp_data_transfer_image;

	if( pthread_create(&_thread_tid, NULL, tcp_server, tcp_server_data) ){  //服务端线程
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
