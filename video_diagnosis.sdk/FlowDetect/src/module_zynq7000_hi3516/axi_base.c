#include "axi_base.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void printf_binary(int n,int size)
{
	PRINTF_DBG("LSB##");
	while (size--) {
    if (n & 1)
    	PRINTF_DBG("1");
    else
    	PRINTF_DBG("0");

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
		const  unsigned char STAT=fpga_img_read_sensor_status();

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
			PRINTF_DBG("Sensor STAT: 0X%x\n",STAT);

			printf_binary(STAT,8);

			return SetSensorStat_T(STAT);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int sensor_state_1()
{
			int _ch;
			int error_t=FALSE;
			const  unsigned char STAT=fpga_img_read_sensor_status();


			for(_ch=0;_ch<8;_ch++){

							if(GetGlobalSensorMask(_ch)){

										if(STAT & (0x01<<_ch)){

										}else{
												PRINTF_DBG("Sensor error: %d",_ch);
												error_t=TRUE;
										}
							}
			}


			printf_binary(STAT,8);

			if(error_t==TRUE){
				return SetSensorStat_T(0x00);
			}else{
				return SetSensorStat_T(0xff);
			}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int sensor_state()
{
	if(GetGlobalSensor()==0xff){
		return sensor_state_8();
	}else{
		return sensor_state_1();
	}
}



/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int wait4FpgaConvertDone()
{
    int result_t=FALSE;

		while(IsRun()){

			if(fpga_is_busy()==TRUE){

				sleep_1ms();
			}else{
				result_t=TRUE;//now free
				break;
			}

		}

	return result_t;
}
/*-----------------------------------*/
/**
 *FPGA初始化
 */
/*-----------------------------------*/
int init_fpga()
{
	const int  iTemp=sensor_state();

	if(iTemp==0x00)
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
int set_fpga_work_mode(int _WORK,int _DATA)
{
	if(wait4FpgaConvertDone()==FALSE){
		return FALSE;
	}

	fpga_set_work_mode(_WORK,_DATA);


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
//**********************************************
// 第一圈 -  求均值图
//**********************************************
void outside_first(int DATA_MODE)
{
	fpga_set_outside_first(DATA_MODE);
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
	TIME_END("outside cost time :");
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


	wait4FpgaConvertDone();

	fpga_set_second_part();

	fpga_set_sigma_up(GetSigmaUp());
	fpga_set_sigma_down(GetSigmaDown());

//**********************************************
// 5 - 触发工作 （脉冲）
//**********************************************
	fpga_start();


	wait4FpgaConvertDone();



	return;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void sendImageStart()
{
		initFrameIdx();

		int schi=0;
		int sfri=0;

			for(schi=0; schi <SPACE_CHANNEL_NUM;schi++){
				for(sfri=0;sfri<SPACE_FRAME_NUM;sfri++){

						if(is_space_frame_output(schi,sfri)){

										const int View_channel=image_view_channel(schi,sfri);
										assert(View_channel>=0);
										const unsigned int seq_t=GetFrameCircleSeq();
										snd_queue_img_buff(CreateImageStart(View_channel,seq_t));

						}
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
	int schi=0;
	int sfri=0;

	for(schi=0; schi <SPACE_CHANNEL_NUM;schi++){
		for(sfri=0;sfri<SPACE_FRAME_NUM;sfri++){

					if(is_space_frame_output(schi,sfri)){

									const int View_channel=image_view_channel(schi,sfri);
									assert(View_channel>=0);
									const unsigned int seq_t=GetFrameCircleSeq();
									snd_queue_img_buff(CreateImageStop(View_channel,seq_t));


					}

		}
	}
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void sendImageMask()
{
			int schi=0;
			int sfri=0;

			for(schi=0; schi <SPACE_CHANNEL_NUM;schi++){
				for(sfri=0;sfri<SPACE_FRAME_NUM;sfri++){

							if(is_space_frame_output(schi,sfri)){

											const int View_channel=image_view_channel(schi,sfri);
											assert(View_channel>=0);
											CvRect rect=GetRectSpaceChannelFrame(schi,sfri);

											CMD_CTRL* cmd_t=CreateImageMask(View_channel,rect.width,rect.height,0);

											if(ReadImgMaskMatrix(cmd_t)){
												snd_queue_img_buff(cmd_t);
											}else{
												ReleaseCmdCtrl(&cmd_t);
											}

							}

				}
			}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
