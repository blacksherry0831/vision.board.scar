#include "axi_fpga_ctrl.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
MAP_OBJ  MAP_PL_PARA={0};

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void FPGA_CTRL_init()
{

	MAP_PL_PARA.ADDR=PL_PARA_ADDR_BASE;
	MAP_PL_PARA.SIZE=PL_PARA_ADDR_SIZE;

	MAP_PL_PARA.virtual_addr=NULL;
	MAP_PL_PARA.fd=-1;

	assert(strlen(MEM_DEV)<256);

	strcpy( (char *)MAP_PL_PARA.DEV , MEM_DEV);

	pthread_mutex_init(&(MAP_PL_PARA.lock),NULL);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void FPGA_CTRL_destory()
{
	pthread_mutex_destroy(&(MAP_PL_PARA.lock));
}
/*-----------------------------------*/
/**
 *判断FPGA是否初始化
 */
/*-----------------------------------*/
int is_FPGA_CTRL_init()
{
	if(MAP_PL_PARA.virtual_addr!=NULL){
		if(MAP_PL_PARA.fd>0){
			return TRUE;
		}
	}

	return FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int FPGA_CTRL_mmap()
{
	FPGA_CTRL_init();

		 pthread_mutex_lock(&MAP_PL_PARA.lock);

		 	 int stat_t=AXILitemmapExS(&MAP_PL_PARA);

		 pthread_mutex_unlock(&MAP_PL_PARA.lock);

	return  stat_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void FPGA_CTRL_unmmap()
{
	 pthread_mutex_lock(&MAP_PL_PARA.lock);

	 	 AXILiteunmmapExS(&MAP_PL_PARA);

	 pthread_mutex_unlock(&MAP_PL_PARA.lock);

	 FPGA_CTRL_destory();
}
/*-----------------------------------*/
/**
 *向FPGA发送命令 （向指定地址写入数据）
 */
/*-----------------------------------*/
int FPGA_CTRL_send(unsigned int _addr, int* pidata)
{

		if(is_FPGA_CTRL_init()){

				if( pthread_mutex_lock(&MAP_PL_PARA.lock)==SUCCESS){

						//向指定地址内存写入数据
						 AXILitetoUser((unsigned int)(MAP_PL_PARA.virtual_addr+_addr),
								PL_PARA_ADDR_BASE+_addr/4,
								(unsigned char *)pidata,
								sizeof(int));

						 if(pthread_mutex_unlock(&MAP_PL_PARA.lock)==SUCCESS){
							 return TRUE;
						 }

				}

		}

		return FALSE;
}
/*-----------------------------------*/
/**
 **向FPGA发送命令 （向指定地址写入（整数型）数据）
 */
/*-----------------------------------*/
int FPGA_CTRL_send_int(unsigned int _addr,const  int _data)
{

	int  iTemp=_data;
	int* piTemp=&iTemp;

	return FPGA_CTRL_send(_addr, piTemp);

}
/*-----------------------------------*/
/**
 *向FPGA发送命令1和0 （向指定地址写入（整数型）数据）
 */
/*-----------------------------------*/
int FPGA_CTRL_send_int_1_0(unsigned int _addr)
{
		FPGA_CTRL_send_int(_addr,1);
		return FPGA_CTRL_send_int(_addr,0);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int FPGA_CTRL_send_unit(unsigned int _addr,unsigned int* pidata)
{

		if(is_FPGA_CTRL_init()){


				if( pthread_mutex_lock(&MAP_PL_PARA.lock)==SUCCESS){

						 AXILitetoUser((unsigned int)(MAP_PL_PARA.virtual_addr+_addr),
								PL_PARA_ADDR_BASE+_addr/4,
								(unsigned char *)pidata,
								sizeof(unsigned int));

						 if(pthread_mutex_unlock(&MAP_PL_PARA.lock)==SUCCESS){
							 return TRUE;
						 }

				}

		}

		return FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int FPGA_CTRL_read(unsigned int _addr, int* pidata)
{
	  if(is_FPGA_CTRL_init()){


				if( pthread_mutex_lock(&MAP_PL_PARA.lock)==SUCCESS){

					UsertoAXILite((unsigned int)(MAP_PL_PARA.virtual_addr+_addr),
										PL_PARA_ADDR_BASE+_addr/4,
										(unsigned char*)pidata,
										sizeof(int));

						 if(pthread_mutex_unlock(&MAP_PL_PARA.lock)==SUCCESS){
							 return TRUE;
						 }

				}

		}

		return FALSE;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
//函数功能：向PL端 outside 模块发送控制参数
// 0x100: 复位 outside 模块
// 0x101: 数据模式 - 0x0正常模式 sensor的数据， 0x1内部测试模块数据， 0x2全零测试数据
// 0x102: 触发工作 - 先发 0x1 再发送 0x0
// 0x103: 工作模式 - 0x0 求和、平方和  0x1 求奇异点
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
