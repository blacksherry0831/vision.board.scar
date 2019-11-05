#include "thread_work_ctrl.h"
/*-----------------------------------*/
#include "modules_ex/cmd_scar.h"
#include "module_zynq7000_hi3516/dma_83c4_ex.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int process_cmd_ctrl(CMD_CTRL*  _cmd,int* _resp_cmd_02,int* _resp_body)
{
					const int CmdParam_t=GetCmdParam(_cmd);
					*_resp_cmd_02=CT_OK;


					if(isStartCmd(_cmd)){

						setFpgaScarCmd(_cmd);
						*_resp_cmd_02=CT_OK;

					}else if(isHeartbeatCmd(_cmd)){

						const int hb_resp=CmdParam_t;

						if(hb_resp==HB_RESP){
							*_resp_cmd_02=CT_OK;
						}else if(hb_resp==HB_NONE){
							*_resp_cmd_02=CT_OK;
						}else{
							assert(0);
						}
						PRINTF_DBG("@cmd rcv hearbeat !\n");

					}else if(IsImageRect(_cmd)){

							SetRectCutCmd(_cmd);
							*_resp_cmd_02=CT_OK;

					}else if(IsImageMaskChange(_cmd)){

						if(IsImgMaskValid(_cmd)){
							SaveImgMaskMatrix(_cmd);
						}
						sendImageMask();

					}else if(IsImageChangeWorkMode(_cmd)){

						const int StartParam=CmdParam_t;
						SetFpgaCircleWorkMode(StartParam);
						*_resp_cmd_02=CT_OK;

					}else if(IsImageChangeSigmaUp(_cmd)){

						const int Sigma=CmdParam_t;
						SetSigmaUp2FPGA(Sigma);
						StoreImgCfgJson();
						*_resp_cmd_02=CT_OK;

					}else if(IsImageQuerySigmaUp(_cmd)){

						*_resp_cmd_02=CT_OK;
						*_resp_body=GetSigmaUp();

					}else if(IsImageChangeSigmaDown(_cmd)){

						const int Sigma=CmdParam_t;
						SetSigmaDown2FPGA(Sigma);
						StoreImgCfgJson();
						*_resp_cmd_02=CT_OK;

					}else if(IsImageQuerySigmaDown(_cmd)){

						*_resp_cmd_02=CT_OK;
						*_resp_body=GetSigmaDown();

					}else if(IsImageScarSet_GlobalSigmaUp(_cmd)){
							SetScarGlobalThresholdUp2FPGA(CmdParam_t);
							StoreImgCfgJson();
					}
					else if(IsImageScarQuery_GlobalSigmaUp(_cmd)){
							*_resp_body=GetScarGlobalThresholdUp();
					}
					else if(IsImageScarSet_GlobalSigmaDown(_cmd)){
							SetScarGlobalThresholdDown2FPGA(CmdParam_t);
							StoreImgCfgJson();
					}
					else if(IsImageScarQuery_GlobalSigmaDown(_cmd)){

						*_resp_body=GetScarGlobalThresholdDown();
					}
					else if(IsImageScarSet_RowSigmaUp(_cmd)){
						SetScarRowThresholdUp2FPGA(CmdParam_t);
						StoreImgCfgJson();
					}
					else if(IsImageScarQuery_RowSigmaUp(_cmd)){

						*_resp_body=GetScarRowThresholdUp();
					}
					else if(IsImageScarSet_RowSigmaDown(_cmd)){
						SetScarRowThresholdDown2FPGA(CmdParam_t);
						StoreImgCfgJson();
					}
					else if(IsImageScarQuery_RowSigmaDown(_cmd)){

						*_resp_body=GetScarRowThresholdDown();
					}
					else if(IsImageScarSet_ColSigmaUp(_cmd)){
						SetScarColThresholdUp2FPGA(CmdParam_t);
						StoreImgCfgJson();
					}
					else if(IsImageScarQuery_ColSigmaUp(_cmd)){

						*_resp_body=GetScarColThresholdUp();
					}
					else if(IsImageScarSet_ColSigmaDown(_cmd)){
						SetScarColThresholdDown2FPGA(CmdParam_t);
						StoreImgCfgJson();
					}
					else if(IsImageScarQuery_ColSigmaDown(_cmd)){

						*_resp_body=GetScarColThresholdDown();
					}
					else if(IsImageScarSet_WorkMode(_cmd)){
						SetScarWorkMode2FPGA(CmdParam_t);
						StoreImgCfgJson();
					}
					else if(IsImageScarSet_Mask(_cmd)){

						if(IsImgMaskValid(_cmd)){
							SaveImgMaskMatrix_SCAR(_cmd);
							dmac_83c4_trans_mask_img_cmd_ctrl(_cmd);
						}

					}
					else if(IsImageScarSet_SelectMask(_cmd)){
						SetScarCurrentMask_Cmd(_cmd);
					}
					else{
							*_resp_cmd_02=CT_ERROR;
							PRINTF_DBG("cmd error !!!");
							return FALSE;
					}

					return TRUE;
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

							const int IsValidCmd_t=process_cmd_ctrl(cmd_t,&cmd_resp_status,&cmd_resp_body);

							if(IsValidCmd_t==FALSE){
											cmd_resp_status=CT_ERROR;
											PRINTF_DBG("cmd error !!!");
											goto EXIT_TASK_FLOW;
							}else{
										if(cmd_resp_status==CT_OK || cmd_resp_status==CT_ERROR){
												socket_send_stat=SendRespCmd(sock_server,cmd_resp_status,cmd_resp_body);
										}
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
