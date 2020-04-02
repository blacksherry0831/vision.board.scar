#include "thread_work_ctrl.h"
/*-----------------------------------*/
#include "img_cfg/img_cfg_scar.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/dma_83c4_ex.h"
/*-----------------------------------*/
#include "modules_ex/cmd_scar.h"
#include "modules_ex/cmd_crack1_8.h"
#include "modules_ex/cmd_file.h"
#include "modules_ex/cmd_flame.h"
#include "flame_monitor.h"
/*-----------------------------------*/
#include "modules_58/cetc_flash.h"
/*-----------------------------------*/
#include "def_app.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int process_cmd_ctrl(CMD_CTRL*  _cmd,int* _resp_cmd_02,unsigned int* _resp_body)
{
	const int CMD_BODY_MAX=INT_MAX;
	const int CmdParam_t=GetCmdParam(_cmd);  //获取cmd控制数据实体

	*_resp_cmd_02=CT_OK;

	if(isStartCmd(_cmd)){  //判断是否为start命令

		setFpgaCircleCmdScar(_cmd);  //依据cmd设置任务圈标志
		*_resp_cmd_02=CT_OK;

	}else if(isHeartbeatCmd(_cmd)){  //判断是否为心跳包cmd

		const int hb_resp=CmdParam_t;

		*_resp_cmd_02=CT_OK;


#if	PRINTF_HB
		PRINTF_DBG_EX("Ctrl@Rcv hearbeat !\n");
#endif
	}else if(isLifeCircleDeadlineCmd(_cmd)){  //查询剩余服务期

		*_resp_body=flash_get_deadline();

	}else if(isVersionCmd(_cmd)){  //版本号查询

		*_resp_body=GetVersion();

	}else if(IsImageRect(_cmd)){  //剪切区命令

		SetRectCutCmd(_cmd);
		*_resp_cmd_02=CT_OK;

	}else if(IsImageMaskChange(_cmd)){  //蒙板命令

		if(IsImgMaskValid(_cmd)){

			SaveImgMaskMatrix(_cmd);  //保存蒙板图片

		}

		sendImageMask();  //将蒙板图片加入至图片队列中，发送至IPC

	}else if(IsImageChangeWorkMode(_cmd)){  //工作模式改变命令 （原图？原尺寸）

		const int StartParam=CmdParam_t;
		SetFpgaCircleWorkMode(StartParam);  //设置FPGA和DMA的工作模式（原图？原尺寸）
		*_resp_cmd_02=CT_OK;

	}else if(IsImageChangeSigmaUp(_cmd)){  //设置上限阈值命令

		const int Sigma=CmdParam_t;
		SetSigmaUp2FPGA(Sigma);  //向FPGA设置上限阈值
		StoreImgCfgJson();  //保存至配置文件
		*_resp_cmd_02=CT_OK;

	}else if(IsImageQuerySigmaUp(_cmd)){  //查询上限阈值命令

		*_resp_cmd_02=CT_OK;
		*_resp_body=GetSigmaUp();

	}else if(IsImageChangeSigmaDown(_cmd)){  //设置下限阈值命令

		const int Sigma=CmdParam_t;
		SetSigmaDown2FPGA(Sigma);
		StoreImgCfgJson();
		*_resp_cmd_02=CT_OK;

	}else if(IsImageQuerySigmaDown(_cmd)){  //查询下限阈值命令

		*_resp_cmd_02=CT_OK;
		*_resp_body=GetSigmaDown();

	}else if(IsImageScarSet_GlobalSigmaUp(_cmd)){  //设置全局上限阈值

		SetScarGlobalThresholdUp2FPGA(CmdParam_t);
		StoreImgCfgJson();

	}
	else if(IsImageScarQuery_GlobalSigmaUp(_cmd)){  //查询全局上限阈值

		*_resp_body=GetScarGlobalThresholdUp();

	}
	else if(IsImageScarSet_GlobalSigmaDown(_cmd)){  //设置全局下限阈值

		SetScarGlobalThresholdDown2FPGA(CmdParam_t);
		StoreImgCfgJson();

	}
	else if(IsImageScarQuery_GlobalSigmaDown(_cmd)){  //查询全局下限阈值

		*_resp_body=GetScarGlobalThresholdDown();

	}
	else if(IsImageScarSet_RowSigmaUp(_cmd)){   //设置行向上限阈值

		SetScarRowThresholdUp2FPGA(CmdParam_t);
		StoreImgCfgJson();

	}
	else if(IsImageScarQuery_RowSigmaUp(_cmd)){  //查询行向上限阈值

		*_resp_body=GetScarRowThresholdUp();

	}
	else if(IsImageScarSet_RowSigmaDown(_cmd)){  //设置行向下限阈值

		SetScarRowThresholdDown2FPGA(CmdParam_t);
		StoreImgCfgJson();
	}
	else if(IsImageScarQuery_RowSigmaDown(_cmd)){  //查询行向下限阈值

		*_resp_body=GetScarRowThresholdDown();

	}
	else if(IsImageScarSet_ColSigmaUp(_cmd)){  //设置列向上限阈值

		SetScarColThresholdUp2FPGA(CmdParam_t);
		StoreImgCfgJson();
	}
	else if(IsImageScarQuery_ColSigmaUp(_cmd)){  //设置列向上限阈值

		*_resp_body=GetScarColThresholdUp();

	}
	else if(IsImageScarSet_ColSigmaDown(_cmd)){  //设置列向下限阈值

		SetScarColThresholdDown2FPGA(CmdParam_t);
		StoreImgCfgJson();

	}
	else if(IsImageScarQuery_ColSigmaDown(_cmd)){  //查询列向下限阈值

		*_resp_body=GetScarColThresholdDown();

	}
	else if(IsImageScarSet_WorkMode(_cmd)){  //设工作模式（原图？原尺寸）

		SetScarWorkMode2FPGA(CmdParam_t);
		StoreImgCfgJson();

	}
	else if(IsImageScarSet_Mask(_cmd)){  //设蒙板

		Save_And_Dma_ImageMask_Scar(_cmd);

	}else if(IsImageScarClear_Mask(_cmd)){  //清蒙板

		Clear_And_Dma_ImageMask_Scar(_cmd);

	}else if(IsImageScarSet_SelectMask(_cmd)){  //设蒙版

		SetScarCurrentMask_Cmd(_cmd);

	}else if(IsImageCrack_Query_Frame_Min(_cmd)){  //查询最小帧数

		*_resp_body=GetFrameIdxMin();

	}else if(IsImageCrack_Query_Frame_Max(_cmd)){  //查询最大帧数

		*_resp_body=CMD_BODY_MAX;

	}else if(IsImageCrack_Set_Frame_Max(_cmd)){

	}else if(IsImageCrack_Set_Frame_Min(_cmd)){

	}else if(IsImageCrack_Set_out_1st_circle_frames(_cmd)){  //设第一圈采集张数

	}else if(IsImageCrack_Query_out_1st_circle_frames(_cmd)){  //获取第一圈采集张数

		*_resp_body=CMD_BODY_MAX;

	}else if(IsFileGet(_cmd)){  //文件下载至arm

		sendFile2Queue_filetran(_cmd);

	}else if(IsFilePut(_cmd)){  //文件传至IPC

		SaveFile2SdCard_filetran_TimeCost(_cmd);

	}else if(IsFileDelete(_cmd)){

		deleteFile_SdCard(_cmd);

	}else if(IsFlameMonitorCmd(_cmd)){  //设是否进行火焰监测

		set_flame_monitor_flag(CmdParam_t);

	}else if(IsFlameAreaSetCmd(_cmd)){  //设火焰监测-面积阈值

		set_thresholde_area(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsFlameAreaQueryCmd(_cmd)){  //查询火焰监测-面积阈值

		*_resp_body = get_thresholde_area();

	}else if(IsFlameDifferenceSetCmd(_cmd)){  //设火焰监测-差分阈值

		set_thresholde_difference(CmdParam_t/100.0);
		StoreImgCfgJson();

	}else if(IsFlameDifferenceQueryCmd(_cmd)){  //查询火焰监测-差分阈值

		*_resp_body = get_thresholde_difference() * 100;

	}else{  //其他未知命令

		assert(0);
		*_resp_cmd_02=CT_ERROR;
		PRINTF_DBG_EX("cmd error !!!");
		return FALSE;

	}

	return TRUE;
}
/*-----------------------------------*/
/**
 *进入cmd-客户端交互线程的准备
 */
/*-----------------------------------*/
void EnterTaskFlowCtrl()
{
	//init_1st_2nd_task_circle_flag();  //初始化任务标志为0
	PRINTF_DBG_EX("pthread start >>[task flow ctrl]\n");
}
/*-----------------------------------*/
/**
 *退出线程的清理工作
 */
/*-----------------------------------*/
void ExitTaskFlowCtrl()
{
	//init_1st_2nd_task_circle_flag();  //初始化任务标志为0
	PRINTF_DBG_EX("pthread close >>[task flow ctrl]\n");
	pthread_exit(NULL);
}
/*-----------------------------------*/
/**
 *cmd数据交互的socket客户端线程
 */
/*-----------------------------------*/
void* task_flow_ctrl_server_client(void *_data)
{

   const int sock_server=*((int*)_data);
   mem_free_clr(&_data);

	int socket_read_stat=TRUE;
	int socket_send_stat=TRUE;
	int cmd_resp_status=FALSE;
	unsigned int cmd_resp_body =0;

	EnterTaskFlowCtrl();  //进入cmd-客户端交互线程的准备

	CMD_CTRL*  cmd_t=CreateCmdCtrl(2);  //申请命令空间，并设置命令头和命令控制数据实体长度
/*-----------------------------------*/
	while(IsRun() && socket_read_stat && socket_send_stat){
		cmd_resp_status=CT_NONE;
		cmd_resp_body=0;
		socket_read_stat=socket_read_1_cmd(sock_server,cmd_t);  //从socket读取一条cmd数据

		if(socket_read_stat==TRUE){

			const int IsValidCmd_t=process_cmd_ctrl(cmd_t,&cmd_resp_status,&cmd_resp_body);  //处理命令

			if(IsValidCmd_t==FALSE){

				cmd_resp_status=CT_ERROR;
				PRINTF_DBG_EX("cmd error !!!");
				goto EXIT_TASK_FLOW;

			}else{

				if(cmd_resp_status==CT_OK || cmd_resp_status==CT_ERROR){

					socket_send_stat=SendRespCmd(sock_server,cmd_resp_status,cmd_resp_body);  //发响应命令

				}
			}
		}
	}
/*-----------------------------------*/
	EXIT_TASK_FLOW:
		close(sock_server);
		ReleaseCmdCtrl(&cmd_t);
		ExitTaskFlowCtrl();  //退出线程的清理工作

	return NULL;
}
/*-----------------------------------*/
/**
 *创建与IPC-cmd交互的服务端线程
 */
/*-----------------------------------*/
pthread_t task_flow_ctrl_server()
{
	pthread_t _thread_tid;

	 TCP_SERVER* tcp_server_data=(TCP_SERVER*) mem_malloc(sizeof(TCP_SERVER));
	 	 	 	 tcp_server_data->port=TCP_POET_CMD_CTRL;  //端口 10000
	 	 	 	 tcp_server_data->pfunClient= task_flow_ctrl_server_client;

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
