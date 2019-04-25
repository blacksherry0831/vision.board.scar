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
 *
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
 *
 */
/*-----------------------------------*/
int FPGA_CTRL_send(int addr, int* pidata)
{

		if(is_FPGA_CTRL_init()){


				if( pthread_mutex_lock(&MAP_PL_PARA.lock)==SUCCESS){

						 AXILitetoUser(MAP_PL_PARA.virtual_addr+addr,
								PL_PARA_ADDR_BASE+addr/4,
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
 *
 */
/*-----------------------------------*/
int FPGA_CTRL_read(int addr, int* pidata)
{
	  if(is_FPGA_CTRL_init()){


				if( pthread_mutex_lock(&MAP_PL_PARA.lock)==SUCCESS){

					UsertoAXILite(MAP_PL_PARA.virtual_addr+addr,
										PL_PARA_ADDR_BASE+addr/4,
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
