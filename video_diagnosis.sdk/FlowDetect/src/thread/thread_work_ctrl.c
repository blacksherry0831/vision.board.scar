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
#include "modules_ex/cmd_heart_time.h"
#include "modules_ex/cmd_img_proc.h"
#include "img_proc/img_proc.h"
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
int process_cmd_ctrl_file_op(CMD_CTRL*  _cmd)
{

	if(IsFileGet(_cmd)){
		sendFile2Queue_filetran(_cmd);
	}else if(IsFilePut(_cmd)){
		SaveFile2SdCard_filetran_TimeCost(_cmd);
	}else if(IsFileDelete(_cmd)){
		deleteFile_SdCard(_cmd);
	}else{
		return FALSE;
	}
		return TRUE;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int process_cmd_ctrl_img_scar_detect(CMD_CTRL*  _cmd)
{


   if(IsImageScarSet_SelectMask(_cmd)){  //���ɰ�

		SetScarCurrentMask_Cmd(_cmd);

	}else{
		return FALSE;
	}

	return TRUE;

}

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int process_cmd_ctrl(CMD_CTRL*  _cmd,int* _resp_cmd_02,unsigned int* _resp_body)
{
	int result_t=FALSE;
	const int CMD_BODY_MAX=INT_MAX;
	const int CmdParam_t=GetCmdParam(_cmd);  //��ȡcmd��������ʵ��

	*_resp_cmd_02=CT_OK;

#if 1
			 	 	 	 	 	 result_t= process_cmd_ctrl_img_scar_detect(_cmd);
			 	 	 	 	 	 if(result_t){
			 	 	 	 	 		 return result_t;
			 	 	 	 	 	 }
#endif
#if 1
			 	 	 	 	 	 result_t=process_cmd_ctrl_file_op(_cmd);
								 if(result_t){
					 	 	 		 return result_t;
					 	 	 	 }
#endif

	if(isStartCmd(_cmd)){  //�ж��Ƿ�Ϊstart����

		setFpgaCircleCmdScar(_cmd);  //����cmd��������Ȧ��־
		*_resp_cmd_02=CT_OK;

	}else if(isHeartbeatCmd(_cmd)){  //�ж��Ƿ�Ϊ������cmd

		const int hb_resp=CmdParam_t;

		*_resp_cmd_02=CT_OK;


#if	PRINTF_HB
		PRINTF_DBG_EX("Ctrl@Rcv hearbeat !\n");
#endif
	}else if(isLifeCircleDeadlineCmd(_cmd)){  //��ѯʣ�������

		*_resp_body=flash_get_deadline();

	}else if(isVersionCmd(_cmd)){  //�汾�Ų�ѯ

		*_resp_body=GetVersion();

	}else if(IsImageRect(_cmd)){  //����������

		SetRectCutCmd(_cmd);
		*_resp_cmd_02=CT_OK;

	}else if(IsImageMaskChange(_cmd)){  //�ɰ�����

		if(IsImgMaskValid(_cmd)){

			SaveImgMaskMatrix(_cmd);  //�����ɰ�ͼƬ

		}

		sendImageMask();  //���ɰ�ͼƬ������ͼƬ�����У�������IPC

	}else if(IsImageChangeWorkMode(_cmd)){  //����ģʽ�ı����� ��ԭͼ��ԭ�ߴ磩

		const int StartParam=CmdParam_t;
		SetFpgaCircleWorkMode(StartParam);  //����FPGA��DMA�Ĺ���ģʽ��ԭͼ��ԭ�ߴ磩
		*_resp_cmd_02=CT_OK;

	}else if(IsImageChangeSigmaUp(_cmd)){  //����������ֵ����

		const int Sigma=CmdParam_t;
		SetSigmaUp2FPGA(Sigma);  //��FPGA����������ֵ
		StoreImgCfgJson();  //�����������ļ�
		*_resp_cmd_02=CT_OK;

	}else if(IsImageQuerySigmaUp(_cmd)){  //��ѯ������ֵ����

		*_resp_cmd_02=CT_OK;
		*_resp_body=GetSigmaUp();

	}else if(IsImageChangeSigmaDown(_cmd)){  //����������ֵ����

		const int Sigma=CmdParam_t;
		SetSigmaDown2FPGA(Sigma);
		StoreImgCfgJson();
		*_resp_cmd_02=CT_OK;

	}else if(IsImageQuerySigmaDown(_cmd)){  //��ѯ������ֵ����

		*_resp_cmd_02=CT_OK;
		*_resp_body=GetSigmaDown();

	}else if(IsImageScarSet_GlobalSigmaUp(_cmd)){  //����ȫ��������ֵ

		SetScarGlobalThresholdUp2FPGA(CmdParam_t);
		StoreImgCfgJson();

	}
	else if(IsImageScarQuery_GlobalSigmaUp(_cmd)){  //��ѯȫ��������ֵ

		*_resp_body=GetScarGlobalThresholdUp();

	}
	else if(IsImageScarSet_GlobalSigmaDown(_cmd)){  //����ȫ��������ֵ

		SetScarGlobalThresholdDown2FPGA(CmdParam_t);
		StoreImgCfgJson();

	}
	else if(IsImageScarQuery_GlobalSigmaDown(_cmd)){  //��ѯȫ��������ֵ

		*_resp_body=GetScarGlobalThresholdDown();

	}
	else if(IsImageScarSet_RowSigmaUp(_cmd)){   //��������������ֵ

		SetScarRowThresholdUp2FPGA(CmdParam_t);
		StoreImgCfgJson();

	}
	else if(IsImageScarQuery_RowSigmaUp(_cmd)){  //��ѯ����������ֵ

		*_resp_body=GetScarRowThresholdUp();

	}
	else if(IsImageScarSet_RowSigmaDown(_cmd)){  //��������������ֵ

		SetScarRowThresholdDown2FPGA(CmdParam_t);
		StoreImgCfgJson();
	}
	else if(IsImageScarQuery_RowSigmaDown(_cmd)){  //��ѯ����������ֵ

		*_resp_body=GetScarRowThresholdDown();

	}
	else if(IsImageScarSet_ColSigmaUp(_cmd)){  //��������������ֵ

		SetScarColThresholdUp2FPGA(CmdParam_t);
		StoreImgCfgJson();
	}
	else if(IsImageScarQuery_ColSigmaUp(_cmd)){  //��������������ֵ

		*_resp_body=GetScarColThresholdUp();

	}
	else if(IsImageScarSet_ColSigmaDown(_cmd)){  //��������������ֵ

		SetScarColThresholdDown2FPGA(CmdParam_t);
		StoreImgCfgJson();

	}
	else if(IsImageScarQuery_ColSigmaDown(_cmd)){  //��ѯ����������ֵ

		*_resp_body=GetScarColThresholdDown();

	}
	else if(IsImageScarSet_WorkMode(_cmd)){  //�蹤��ģʽ��ԭͼ��ԭ�ߴ磩

		SetScarWorkMode2FPGA(CmdParam_t);
		StoreImgCfgJson();

	}
	else if(IsImageScarSet_Mask(_cmd)){  //���ɰ�

		Save_And_Dma_ImageMask_Scar(_cmd);

	}else if(IsImageScarClear_Mask(_cmd)){  //���ɰ�

		Clear_And_Dma_ImageMask_Scar(_cmd);

	}else if(IsImageCrack_Query_Frame_Min(_cmd)){  //��ѯ��С֡��

		*_resp_body=GetFrameIdxMin();

	}else if(IsImageCrack_Query_Frame_Max(_cmd)){  //��ѯ���֡��

		*_resp_body=CMD_BODY_MAX;

	}else if(IsImageCrack_Set_Frame_Max(_cmd)){

	}else if(IsImageCrack_Set_Frame_Min(_cmd)){

	}else if(IsImageCrack_Set_out_1st_circle_frames(_cmd)){  //���һȦ�ɼ�����

	}else if(IsImageCrack_Query_out_1st_circle_frames(_cmd)){  //��ȡ��һȦ�ɼ�����

		*_resp_body=CMD_BODY_MAX;

	}else if(IsFlameMonitorCmd(_cmd)){  //���Ƿ���л�����

		set_flame_monitor_flag(CmdParam_t);

	}else if(IsFlameAreaSetCmd(_cmd)){  //�������-�����ֵ

		set_thresholde_area(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsFlameAreaQueryCmd(_cmd)){  //��ѯ������-�����ֵ

		*_resp_body = get_thresholde_area();

	}else if(IsFlameDifferenceSetCmd(_cmd)){  //�������-�����ֵ

		set_thresholde_difference(CmdParam_t/100.0);
		StoreImgCfgJson();

	}else if(IsFlameDifferenceQueryCmd(_cmd)){  //��ѯ������-�����ֵ

		*_resp_body = get_thresholde_difference() * 100;

	}else if(IsHeartBeatTimeSetCmd(_cmd)){  //��������ʱ����

		SetHeartBeatTime(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsHeartBeatTimeQueryCmd(_cmd)){  //��������ʱ����

		*_resp_body = GetHeartBeatTime();

	}else if(IsNetworkCheckTimeSetCmd(_cmd)){  //��������ʱ����

		SetNetworkCheckTime(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsNetworkCheckTimeQueryCmd(_cmd)){  //��������ʱ����

		*_resp_body = GetNetworkCheckTime();

	}else if(IsBinarySetCmd(_cmd)){  //��armͼ����-�Ƿ��ֵ��

		set_is_binary(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsBinaryQueryCmd(_cmd)){  //��armͼ����-�Ƿ��ֵ��

		*_resp_body = get_is_binary();

	}else if(IsDenoiseSetCmd(_cmd)){  //��armͼ����-�Ƿ�ȥ��

		set_is_denoise(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsDenoiseQueryCmd(_cmd)){  //��armͼ����-�Ƿ�ȥ��

		*_resp_body = get_is_denoise();

	}else if(IsBlackSkinSetCmd(_cmd)){  //��armͼ����-�Ƿ��Ƥ���

		set_is_blackSkin(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsBlackSkinQueryCmd(_cmd)){  //��armͼ����-�Ƿ��Ƥ���

		*_resp_body = get_is_blackSkin();

	}else if(IsHoughSetCmd(_cmd)){  //��armͼ����-�Ƿ�hough

		set_is_hough(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsHoughQueryCmd(_cmd)){  //��armͼ����-�Ƿ�hough

		*_resp_body = get_is_hough();

	}else if(IsMorphologySetCmd(_cmd)){  //��armͼ����-�Ƿ���̬ѧ

		set_is_morphology(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsMorphologyQueryCmd(_cmd)){  //��armͼ����-�Ƿ���̬ѧ

		*_resp_body = get_is_morphology();

	}else if(IsShowResultSetCmd(_cmd)){  //��armͼ����-�Ƿ����ж�

		set_is_showResult(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsShowResultQueryCmd(_cmd)){  //��armͼ����-�Ƿ����ж�

		*_resp_body = get_is_showResult();

	}else if(IsHoughThresoldSetCmd(_cmd)){  //��armͼ����-hough������ֵ

		set_hough_thresold(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsHoughThresoldQueryCmd(_cmd)){  //��armͼ����-hough������ֵ

		*_resp_body = get_hough_thresold();

	}else if(IsHoughMinLengthSetCmd(_cmd)){  //��armͼ����-hough�߶���С����

		set_hough_min_length(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsHoughMinLengthQueryCmd(_cmd)){  //��armͼ����-hough�߶���С����

		*_resp_body = get_hough_min_length();

	}else if(IsHoughMaxGapSetCmd(_cmd)){  //��armͼ����-hough�߶������

		set_hough_max_gap(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsHoughMaxGapQueryCmd(_cmd)){  //��armͼ����-hough�߶������

		*_resp_body = get_hough_max_gap();

	}else if(IsHoughMaxAngleSetCmd(_cmd)){  //��armͼ����-hough�߶����Ƕ�

		set_hough_max_angle(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsHoughMaxAngleQueryCmd(_cmd)){  //��armͼ����-hough�߶����Ƕ�

		*_resp_body = get_hough_max_angle();

	}else if(IsCrackMinAreaSetCmd(_cmd)){  //��armͼ����-������С���

		set_crack_min_area(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsCrackMinAreaQueryCmd(_cmd)){  //��armͼ����-������С���

		*_resp_body = get_crack_min_area();

	}else if(IsCrackAspectRatioSetCmd(_cmd)){  //��armͼ����-���Ƴ����

		set_crack_aspect_ratio(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsCrackAspectRatioQueryCmd(_cmd)){  //��armͼ����-���Ƴ����

		*_resp_body = get_crack_aspect_ratio();

	}else if(IsCrackAreaRatioSetCmd(_cmd)){  //��armͼ����-���������

		set_crack_area_ratio(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsCrackAreaRatioQueryCmd(_cmd)){  //��armͼ����-���������

		*_resp_body = get_crack_area_ratio();

	}else if(IsBlackSkinMinAreaSetCmd(_cmd)){  //��armͼ����-��Ƥ��С���

		set_blaskSkin_min_area(CmdParam_t);
		StoreImgCfgJson();

	}else if(IsBlackSkinMinAreaQueryCmd(_cmd)){  //��armͼ����-��Ƥ��С���

		*_resp_body = get_blaskSkin_min_area();

	}else{  //����δ֪����

		//assert(0);
		*_resp_cmd_02=CT_ERROR;
		PRINTF_DBG_EX("cmd error !!!");
		return FALSE;

	}

	return TRUE;
}
/*-----------------------------------*/
/**
 *����cmd-�ͻ��˽����̵߳�׼��
 */
/*-----------------------------------*/
void EnterTaskFlowCtrl()
{
	//init_1st_2nd_task_circle_flag();  //��ʼ�������־Ϊ0
	PRINTF_DBG_EX("pthread start >>[task flow ctrl]\n");
}
/*-----------------------------------*/
/**
 *�˳��̵߳�������
 */
/*-----------------------------------*/
void ExitTaskFlowCtrl()
{
	//init_1st_2nd_task_circle_flag();  //��ʼ�������־Ϊ0
	PRINTF_DBG_EX("pthread close >>[task flow ctrl]\n");
	pthread_exit(NULL);
}
/*-----------------------------------*/
/**
 *cmd���ݽ�����socket�ͻ����߳�
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

	EnterTaskFlowCtrl();  //����cmd-�ͻ��˽����̵߳�׼��

	CMD_CTRL*  cmd_t=CreateCmdCtrl(2);  //��������ռ䣬����������ͷ�������������ʵ�峤��
/*-----------------------------------*/
	while(IsRun() && socket_read_stat && socket_send_stat){
		cmd_resp_status=CT_NONE;
		cmd_resp_body=0;
		socket_read_stat=socket_read_1_cmd(sock_server,cmd_t);  //��socket��ȡһ��cmd����

		if(socket_read_stat==TRUE){

			const int IsValidCmd_t=process_cmd_ctrl(cmd_t,&cmd_resp_status,&cmd_resp_body);  //��������

			if(IsValidCmd_t==FALSE){

				cmd_resp_status=CT_ERROR;
				PRINTF_DBG_EX("cmd error !!!");
				goto EXIT_TASK_FLOW;

			}else{

				if(cmd_resp_status==CT_OK || cmd_resp_status==CT_ERROR){

					socket_send_stat=SendRespCmd(sock_server,cmd_resp_status,cmd_resp_body);  //����Ӧ����

				}
			}
		}
	}
/*-----------------------------------*/
	EXIT_TASK_FLOW:
		close(sock_server);
		ReleaseCmdCtrl(&cmd_t);
		ExitTaskFlowCtrl();  //�˳��̵߳�������

	return NULL;
}
/*-----------------------------------*/
/**
 *������IPC-cmd�����ķ�����߳�
 */
/*-----------------------------------*/
pthread_t task_flow_ctrl_server()
{
	pthread_t _thread_tid;

	 TCP_SERVER* tcp_server_data=(TCP_SERVER*) mem_malloc(sizeof(TCP_SERVER));
	 	 	 	 tcp_server_data->port=TCP_POET_CMD_CTRL;  //�˿� 10000
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
