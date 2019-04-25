#include "task_flow.h"

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
struct sockaddr_in init_server_addr()
{
	struct sockaddr_in saddr;
	int size = sizeof(struct sockaddr_in);
	bzero(&saddr,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(10000);
	saddr.sin_addr.s_addr = inet_addr("192.168.100.100");
	return saddr;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int connect_socket(int* status)
{
	
	struct sockaddr_in saddr=init_server_addr();
	int sockfd = socket(AF_INET,SOCK_STREAM,0); //
	const int SIZE=sizeof(struct sockaddr);

	if( connect(sockfd,(struct sockaddr*)&saddr,SIZE)< 0){
	        PRINTF_DBG("Can't Connected to %s:%u\n",inet_ntoa(saddr.sin_addr),ntohs(saddr.sin_port));
	        PRINTF_DBG("%s\n", strerror(errno));
	        *status=FALSE;
	        close(sockfd);

	 }else{
		 	PRINTF_DBG("connect to server success !\n");
		 	*status=TRUE;
	 }
	
	
	return sockfd;
	
}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
void *task_flow_server(void *_data)
{
	int restCode_t=0;
	int sock_server=0;

	CMD_CTRL*  cmd_t=CreateCmdCtrl(0);

	while(IsRun()){


				do{
					sock_server=connect_socket(&restCode_t);

				}while(restCode_t==FALSE);


				while(socket_read_1_cmd(sock_server,cmd_t)){

					if(isStartCmd(cmd_t)){

						SendRespCmd(sock_server,TRUE,0);
						PRINTF_DBG("Rcv Start CMD \n");
						//init_axi_server(NULL);

					}else if(isDoneCmd(cmd_t)){

						SendRespCmd(sock_server,TRUE,0);
						PRINTF_DBG("Rcv Stop CMD \n");
						//stop_axi_server();

					}else{
						PRINTF_DBG("cmd error !!!");
						pthread_exit(NULL);
					}


				}

				close(sock_server);
	}


	ReleaseCmdCtrl(&cmd_t);
	//stop_axi_server();

}
/*-----------------------------------*/
 /* *
  *
 */
/*-----------------------------------*/
pthread_t init_task_flow(void *_data)
{
	pthread_t _thread_tid;
	if( pthread_create(&_thread_tid, NULL, task_flow_server, _data) ){
			PRINTF_DBG(" Create flow thread error!\n");

	}
	return _thread_tid;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void Get8ChannelAverage()
{
	int chi;
	int SIZE=0;
	const int CHANNELS=8;
	CMD_CTRL* data[8];

	int i;
	for( i=0;i<CHANNELS;i++){
		data[i]=CreateCmdCtrl(1920*1080);
	}


;
	for(chi=0;chi<CHANNELS;chi++){
#if 0
		getImageAvg(chi,data[i]->f_data,1920*1080);
#else
		assert(0);
#endif
	}



	for( i=0;i<CHANNELS;i++){

		ReleaseCmdCtrl(&data[i]);

	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void* task_flow_ctrl_server_client(void *_data)
{

   	int sock_server=*((int*)_data);

   	mem_free_clr(&_data);

	int socket_read_stat=TRUE;
	int socket_send_stat=TRUE;
	int cmd_resp_status=FALSE;
	int cmd_resp_body =0;
	int fpga_ctrl_stat=SUCCESS;

	EnterTaskFlowCtrl();

	CMD_CTRL*  cmd_t=CreateCmdCtrl(2);
/*-----------------------------------*/
	while(IsRun() && socket_read_stat && socket_send_stat && (fpga_ctrl_stat==SUCCESS)){
		cmd_resp_status=CT_NONE;
		cmd_resp_body=0;
		socket_read_stat=socket_read_1_cmd(sock_server,cmd_t);
					if(socket_read_stat==TRUE){

									if(isStartCmd(cmd_t)){

										setFpgaCircleCmd(cmd_t);
										cmd_resp_status=CT_OK;

									}else if(isHeartbeatCmd(cmd_t)){

										int hb_resp=GetCmdParam(cmd_t);

										if(hb_resp==HB_RESP){
											cmd_resp_status=CT_OK;
										}else if(hb_resp==HB_NONE){
											cmd_resp_status=CT_NONE;
										}else{
											assert(0);
										}
										PRINTF_DBG("@cmd rcv hearbeat !\n");

									}else if(IsImageRect(cmd_t)){

											SetRectCutCmd(cmd_t);
											cmd_resp_status=CT_OK;

									}else if(IsImageChangeWorkMode(cmd_t)){

										const int StartParam=GetCmdParam(cmd_t);
										SetFpgaCircleWorkMode(StartParam);
										cmd_resp_status=CT_OK;

									}else if(IsImageChangeSigma(cmd_t)){

										const int Sigma=GetCmdParam(cmd_t);
										SetSigma(Sigma);
										cmd_resp_status=CT_OK;

									}else if(IsImageQuerySigma(cmd_t)){

												cmd_resp_status=CT_OK;
												cmd_resp_body=GetSigma();

									}else{
											cmd_resp_status=CT_ERROR;
											PRINTF_DBG("cmd error !!!");
											goto EXIT_TASK_FLOW;
									}


									if(cmd_resp_status==CT_OK || cmd_resp_status==CT_ERROR){
											socket_send_stat=SendRespCmd(sock_server,cmd_resp_status,cmd_resp_body);
									}

					}



	}

/*-----------------------------------*/
EXIT_TASK_FLOW:

	close(sock_server);
	ReleaseCmdCtrl(&cmd_t);

	ExitTaskFlowCtrl();

	return NULL;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
pthread_t task_flow_ctrl_server()
{
	pthread_t _thread_tid;

	 TCP_SERVER* tcp_server_data=mem_malloc(sizeof(TCP_SERVER));
	 	 	 	 tcp_server_data->port=TCP_POET_CMD_CTRL;
	 	 	 	 tcp_server_data->pfunClient= task_flow_ctrl_server_client;

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

