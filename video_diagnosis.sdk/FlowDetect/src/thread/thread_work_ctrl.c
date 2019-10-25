#include "thread_work_ctrl.h"
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

									}else if(IsImageMaskChange(cmd_t)){

										if(IsImgMaskValid(cmd_t)){
											SaveImgMaskMatrix(cmd_t);
										}
										cmd_resp_status=CT_OK;
										sendImageMask();

									}else if(IsImageChangeWorkMode(cmd_t)){

										const int StartParam=GetCmdParam(cmd_t);
										SetFpgaCircleWorkMode(StartParam);
										cmd_resp_status=CT_OK;

									}else if(IsImageChangeSigmaUp(cmd_t)){

										const int Sigma=GetCmdParam(cmd_t);
										SetSigmaUp2FPGA(Sigma);
										StoreImgCfgJson();
										cmd_resp_status=CT_OK;

									}else if(IsImageQuerySigmaUp(cmd_t)){

												cmd_resp_status=CT_OK;
												cmd_resp_body=GetSigmaUp();

									}else if(IsImageChangeSigmaDown(cmd_t)){

										const int Sigma=GetCmdParam(cmd_t);
										SetSigmaDown2FPGA(Sigma);
										StoreImgCfgJson();
										cmd_resp_status=CT_OK;

									}else if(IsImageQuerySigmaDown(cmd_t)){

												cmd_resp_status=CT_OK;
												cmd_resp_body=GetSigmaDown();

									}

									else{
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
