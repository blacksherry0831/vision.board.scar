#include "axi_base.h"

/*-----------------------------------*/
pthread_mutex_t FPGA_mutex_init = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t FPGA_mutex_cvt = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  FPGA_cond_cvt=PTHREAD_COND_INITIALIZER;
unsigned int    FPGA_CvtDone=0;
/*-----------------------------------*/
#define PATH_SDCARD_IMG_SIGMA_CFG   ("/media/sdcard/img_sigma.txt")
/*-----------------------------------*/
int SENSOR_STAT=0;
int G_Sigma=6;
/*-----------------------------------*/
void ReadParam4SDCard(const char* const path, int* _param,const int _size);
/*-----------------------------------*/
void FpgaSignalCvtDone()
{
	pthread_mutex_lock(&FPGA_mutex_cvt);//
		FPGA_CvtDone=TRUE;
		pthread_cond_signal(&FPGA_cond_cvt);
		PRINTF_DBG("send fpga done signal \n");
	pthread_mutex_unlock(&FPGA_mutex_cvt);//
}
/*-----------------------------------*/
int Wait4FPGADone(long timeout_ms)
{
	int reslut_t=Wait4Signal(timeout_ms,& FPGA_mutex_cvt,&FPGA_cond_cvt);

	return reslut_t;
}

void printf_binary(int n,int size)
{
	PRINTF_DBG("LSB##");
	while (size--) {
    if (n & 1)
        printf("1");
    else
        printf("0");

    n >>= 1;
	}
	PRINTF_DBG("##MSB");
	PRINTF_DBG("\n");
}


/*-----------------------------------*/
/**
* 函数功能：向PL端 outside 模块发送控制参数
* 0x100: 复位 outside 模块
* 0x101: 数据模式 - 0x0正常模式 sensor的数据， 0x1内部测试模块数据， 0x2全零测试数据
* 0x102: 触发工作 - 先发 0x1 再发送 0x0
* 0x103: 工作模式 - 0x0 求和、平方和  0x1 求奇异点
*/
/*-----------------------------------*/
int sensor_state_8()
{
	int  iTemp;
		int* piTemp=&iTemp;
		//**********************************************
		// 获取 sensor 状态，0xFF为正常，开始工作，否则退出
		//**********************************************
		FPGA_CTRL_read(ADDR_SENSOR_STATE, piTemp);

		const  unsigned char STAT=*piTemp;

		unsigned char STAT8=STAT;
		if(STAT8!=0xff)
		{
			int i=0;
			for(i=0;i<8;i++){

				int bit=STAT8&0x01;

				if(bit==0)
				PRINTF_DBG("Sensor error: %d",i);

				STAT8=STAT8>>1;
			}
			PRINTF_DBG("\n");

		}
			PRINTF_DBG("Sensor STAT: 0X %x ###",STAT);

			printf_binary(STAT,8);

			return SetSensorStat(STAT);
}

int sensor_state_1()
{
			int _ch;
			int error_t=FALSE;
			int  iTemp;
			int* piTemp=&iTemp;
			//**********************************************
			// 获取 sensor 状态，0xFF为正常，开始工作，否则退出
			//**********************************************
			FPGA_CTRL_read(ADDR_SENSOR_STATE, piTemp);

			const  unsigned char STAT=*piTemp;

			for(_ch=0;_ch<8;_ch++){

							if(GetGlobalChannelMask(_ch)){

										if(STAT & (0x01<<_ch)){

										}else{
												PRINTF_DBG("Sensor error: %d",_ch);
												error_t=TRUE;
										}
							}
			}


			printf_binary(STAT,8);

			if(error_t==TRUE){
				return SetSensorStat(0x00);
			}else{
				return SetSensorStat(0xff);
			}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int sensor_state()
{
	if(GetGlobalChannel()==0xff){
		return sensor_state_8();
	}else{
		return sensor_state_1();
	}
}
/*-----------------------------------*/
/**
 *0==disable
 *1==enable
 */
/*-----------------------------------*/
void svm_enable(int _enable)
{
	assert(_enable==0x00 || _enable==0x01);
#if 0
	FPGA_CTRL_send(SVM_ENABLE_CTRL, &_enable);
#endif
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetSigma4SDCard()
{
	int param[1]={0};
	if(is_file_exist(PATH_SDCARD_IMG_SIGMA_CFG)==SUCCESS){
		ReadParam4SDCard(PATH_SDCARD_IMG_SIGMA_CFG,param, 1);
		G_Sigma=param[0];
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetSigma()
{
	return G_Sigma;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetSigma(int _sigma)
{
	G_Sigma=_sigma;
	int param[1]={_sigma};
	SaveParam2SDCard(PATH_SDCARD_IMG_SIGMA_CFG,param,1);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetoutsideSigma(int _sigma)
{
	SetSigma(_sigma);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetinsideSigma(int _sigma)
{
	SetSigma(_sigma);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int SetSensorStat(int _sensor_stat)
{
	SENSOR_STAT=_sensor_stat;
	return SENSOR_STAT;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SaveParam2SDCard(const char* const path,const int* _param,const int _size)
{
		char buff[1024];
		FILE *fp = fopen(path,"wt+");

	 	int i=0;

	 	if (NULL == fp){
	 		return ;
	 	}

	 	for(i=0;i<_size;i++){
	 		snprintf(buff,sizeof(buff),"%d,%d\n",i,_param[i]);
	 		fputs(buff,fp);
	 	}

	 	 fclose(fp);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ReadParam4SDCard(const char* const path, int* _param,const int _size)
{
			char buff[1024]={0};
			int i=0;
			FILE *fp = fopen(path,"r");

						if (NULL == fp){
							return ;
						}

						for(i=0;i<_size;i++){

							memset(buff,0,sizeof(buff));
							fgets(buff,sizeof(buff),fp);

							 char*token=strtok(buff,",");

							 while(token!=NULL){

								 _param[i]= atoi(token);

								 token=strtok(NULL,",");

							 }

						}

		 fclose(fp);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetSensorStat()
{
	return SENSOR_STAT;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_reset()
{
	int  iTemp=0;
	//**********************************************
	// 复位
	//**********************************************
	// 2.1 复位
	 iTemp=1;
	 FPGA_CTRL_send(ADDR_OUTSIDE_RESET,&iTemp);
	 iTemp=0;
	 FPGA_CTRL_send(ADDR_OUTSIDE_RESET,&iTemp);

	return TRUE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int fpga_start()
{
	int  iTemp=0;
	int* piTemp=&iTemp;
	*piTemp=1;
	FPGA_CTRL_send(ADDR_OUTSIDE_START_EN,piTemp);
	*piTemp=0;
	FPGA_CTRL_send(ADDR_OUTSIDE_START_EN,piTemp);

	return TRUE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4FpgaConvertDone()
{

		int  iTemp=1;
		int* piTemp=&iTemp;

		while(*piTemp==1){
			if(FPGA_CTRL_read(ADDR_OUTSIDE_BUSY, piTemp)){
				sleep_1ms();
			}else{
				return FALSE;//read error
			}
#if TRUE
			if(IsRun()==FALSE){
				return FALSE;
			}
#endif
		}

	return TRUE;
}
/*-----------------------------------*/
/**
 *FPGA初始化
 */
/*-----------------------------------*/
int init_fpga()
{
	int  iTemp=0;
	iTemp=sensor_state();

	if(iTemp!=0xFF)
	{
		return FALSE;
	}else{
		return fpga_reset();
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetFLowDetectThd(const int sigma)
{
	int  iTemp=sigma;
	int* piTemp=&iTemp;

	FPGA_CTRL_send(FLOW_DETECT_THD,piTemp);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int set_fpga_data_mode(int _WORK,int _DATA)
{
	int  iTemp;
	int* piTemp=&iTemp;
	*piTemp=_DATA;	//原始图像
	FPGA_CTRL_send(ADDR_OUTSIDE_DATA_MODE,piTemp);

	//	*piTemp=0;	// 求奇异值
	*piTemp=_WORK;	// 求奇异值
	FPGA_CTRL_send(ADDR_OUTSIDE_WORK_MODE,piTemp);

	return TRUE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int set_fpga_work_mode(int _WORK,int _DATA)
{

	if(sensor_state()!=0xff){
		return FALSE;
	}

	if(wait4FpgaConvertDone()==FALSE){
		return FALSE;
	}

	if(fpga_reset()==FALSE){
		return FALSE;
	}

	set_fpga_data_mode(_WORK,_DATA);

	fpga_start();

	// 等待完成


	return wait4FpgaConvertDone();
}


//**********************************************
// 第一圈 -  求均值图
//**********************************************
void outside_first_m()
{
    PRINTF_DBG("outside_first!\n");

    set_fpga_work_mode(FPGA_WORK_MODE_AVG,
    		 FPGA_WORK_MODE_DATA_AVG);

}


//**********************************************
// 第二圈 -  求奇异值图
//**********************************************
void outside_second_m()
{
    PRINTF_DBG("outside_second!\n");
	set_fpga_work_mode(FPGA_WORK_MODE_DIFF,
			FPGA_WORK_MODE_DATA_DIFF);

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
//**********************************************
// 第一圈 -  求均值图
//**********************************************
void outside_first(int DATA_MODE)
{
	int  iTemp;
	int* piTemp=&iTemp;

	// 数据模式
//	*piTemp=1;	//递增数
//	*piTemp=0;	//求和
//	*piTemp=2;	//全0
	*piTemp=DATA_MODE;
	FPGA_CTRL_send(ADDR_OUTSIDE_DATA_MODE,piTemp);
	// 工作模式
	*piTemp=0;	// 正常图像
	FPGA_CTRL_send(ADDR_OUTSIDE_WORK_MODE,piTemp);
	// 3.3 触发工作
	*piTemp=1;
	FPGA_CTRL_send(ADDR_OUTSIDE_START_EN,piTemp);
	*piTemp=0;
	FPGA_CTRL_send(ADDR_OUTSIDE_START_EN,piTemp);
	// 3.4 等待完成
	wait4FpgaConvertDone();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void outside08_first_ex(int DATA_MODE)
{
	TIME_START();
	if(GetProjectRun()==outside08){
		outside_first(DATA_MODE);
	}
	TIME_END("");
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
//**********************************************
// 第二圈 -  求奇异值图
//**********************************************
void outside_second()
{
	FPGA_CvtDone=FALSE;

	int  iTemp;
	int* piTemp=&iTemp;


	//**********************************************
	// 1 - 获取 sensor 状态，0xFF为正常
	//**********************************************

	if(sensor_state()!=0xff)
	{
		return;
	}




	//**********************************************
	// 2 - 等待空闲
	//**********************************************
	wait4FpgaConvertDone();

	//**********************************************
	// 3 - 复位
	//**********************************************
	*piTemp=1;
	FPGA_CTRL_send(ADDR_OUTSIDE_RESET,piTemp);
	*piTemp=0;
	FPGA_CTRL_send(ADDR_OUTSIDE_RESET,piTemp);

//**********************************************
// 4 - 设置工作模式
//**********************************************
	// 正常模式
//	*piTemp=1;	//递增数
	*piTemp=0;	//原始图像
	FPGA_CTRL_send(ADDR_OUTSIDE_DATA_MODE,piTemp);

//	*piTemp=0;	// 求奇异值
	*piTemp=1;	// 求奇异值
	FPGA_CTRL_send(ADDR_OUTSIDE_WORK_MODE,piTemp);


	SetFLowDetectThd(G_Sigma);

//**********************************************
// 5 - 触发工作 （脉冲）
//**********************************************
	*piTemp=1;
	FPGA_CTRL_send(ADDR_OUTSIDE_START_EN,piTemp);
	*piTemp=0;
	FPGA_CTRL_send(ADDR_OUTSIDE_START_EN,piTemp);
	// 等待完成


	wait4FpgaConvertDone();



	return;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void outside_inside_second_ex()
{
	if(GetProjectRun()==outside08){

				outside_second();

	}else if(GetProjectRun()==outside08){

				outside_second();

	}else{


	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void outside_second_sync(int _frame_idx)
{
	static int FPGA_COUNT=0;
	if(pthread_mutex_lock(&FPGA_mutex_cvt)==SUCCESS){

				TIME_START();

					outside_second();
					__sync_lock_test_and_set(&FPGA_CvtDone,TRUE);
					PRINTF_DBG("FPGA:%d___",FPGA_COUNT++);

				TIME_END("1> FPGA Convert cost time : ");

				if(pthread_mutex_unlock(&FPGA_mutex_cvt)==SUCCESS){
						sem_post(&m_sem_fpga_frame_done);
						sched_yield();
						sem_wait_infinite(&m_sem_dma_frame_done2fpga);

				}
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void sendImageStart()
{
	initFrameIdx();

	const unsigned int seq_t=GetFrameCircleSeq();

	int chi=0;
	for(chi=0;chi<8;chi++){
		if(GetGlobalChannelMask(chi)){
			snd_queue_img_buff(CreateImageStart(chi,seq_t));
		}
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void sendImageStop()
{
	const unsigned int seq_t=GetFrameCircleSeq();
	int chi=0;
		for(chi=0;chi<8;chi++){
			if(GetGlobalChannelMask(chi)){
				snd_queue_img_buff(CreateImageStop(chi,seq_t));
			}
		}

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
void send_image_2_queue(int _frameIdx,int MAP_WHAT)
{
	unsigned char Chn_num=0;
	int nChannels=(MAP_WHAT==AXI_MAP_AVERAGE)?8:1;
	int sensor_stat=sensor_state();

	wait4MemFree();

	for(Chn_num=0;Chn_num< CHANNELS;Chn_num++){
		video_map_ch(Chn_num,MAP_WHAT);
		{
/*****************************/
			 CMD_CTRL*  cmd_t;

			cmd_t=CreateImageCtrl(Chn_num,_frameIdx,1920,1080,nChannels,GetFrameCircleSeq());

			SetSensorStatus(cmd_t,sensor_stat,Chn_num);
    		 if(cmd_t!=NULL){
    			  IplImageU * image=(IplImageU*) cmd_t->f_data;
    			  IplImage*   IplImg=&(image->Iplimg);

    			  memcpy_video(IplImg->imageData,Chn_num,0,IplImg->imageSize);

    			  snd_queue_img_buff(cmd_t);
    		 }
/*****************************/
		}
		video_unmap();
	}




}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
