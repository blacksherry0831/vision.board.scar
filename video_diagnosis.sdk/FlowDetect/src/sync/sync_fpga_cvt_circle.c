#include "sync_fpga_cvt_circle.h"
/*-----------------------------------*/
static volatile int G_FPGA_CIRCLE_TASK_RUNNING[2]={0};
static volatile int G_FPGA_CIRCLE_TASK_1st_START[2]={0};
static volatile int G_FPGA_CIRCLE_TASK_2nd_START[2]={0};
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *设置第一圈的标志
 */
/*-----------------------------------*/
void set_1st_circle_flag(const int _idx,const int _v)
{
	G_FPGA_CIRCLE_TASK_1st_START[_idx]=_v;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void set_1st_circle_start()
{
	set_1st_circle_flag(0,1);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void set_1st_circle_end()
{
	set_1st_circle_flag(1,1);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int get_1st_circle_start()
{
	return G_FPGA_CIRCLE_TASK_1st_START[0];
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int get_1st_circle_end()
{
	return G_FPGA_CIRCLE_TASK_1st_START[1];
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int get_1st_circle_running()
{
	return 	get_1st_circle_start()==1 &&
			get_1st_circle_end()==0;
}
/*-----------------------------------*/
/**
 *设置第2圈标志
 */
/*-----------------------------------*/
void set_2nd_circle_flag(const int _idx,const int _v)
{
	G_FPGA_CIRCLE_TASK_2nd_START[_idx]=_v;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void set_2nd_circle_start()
{
	set_2nd_circle_flag(0,1);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void set_2nd_circle_end()
{
	set_2nd_circle_flag(1,1);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int get_2nd_circle_start()
{
	return G_FPGA_CIRCLE_TASK_2nd_START[0];
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int get_2nd_circle_end()
{
	return G_FPGA_CIRCLE_TASK_2nd_START[1];
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int get_2nd_circle_running()
{
	return 	get_2nd_circle_start()==1 &&
			get_2nd_circle_end()==0;
}
/*-----------------------------------*/
/**
 *初始化第一圈标志为0
 */
/*-----------------------------------*/
void init_1st_circle_flag()
{
	const int SZ=sizeof(G_FPGA_CIRCLE_TASK_1st_START)/sizeof(int);
	int i=0;
	for(i=0;i<SZ;i++){
		set_1st_circle_flag(i,0);
	}
}
/*-----------------------------------*/
/**
 *初始化第2圈标志为0
 */
/*-----------------------------------*/
void init_2nd_circle_flag()
{
	const int SZ=sizeof(G_FPGA_CIRCLE_TASK_2nd_START)/sizeof(int);
		int i=0;
		for(i=0;i<SZ;i++){
			set_2nd_circle_flag(i,0);
		}
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsFpgaCvtCircleTaskRunning()
{
	return  (1==G_FPGA_CIRCLE_TASK_RUNNING[0]) &&
			(0==G_FPGA_CIRCLE_TASK_RUNNING[1]);
}
/*-----------------------------------*/
/**
 *设置总任务圈标志
 */
/*-----------------------------------*/
void set_task_circle_flag(const int _idx,const int _v)
{
	G_FPGA_CIRCLE_TASK_RUNNING[_idx]=_v;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void set_task_circle_start()
{
	set_task_circle_flag(0,1);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void set_task_circle_end()
{
	set_task_circle_flag(1,1);
}
/*-----------------------------------*/
/**
 *初始总任务圈标志为0
 */
/*-----------------------------------*/
void init_task_circle_flag()
{
	const int SZ=sizeof(G_FPGA_CIRCLE_TASK_1st_START)/sizeof(int);
	int i=0;
	for(i=0;i<SZ;i++){
		set_task_circle_flag(i,0);
	}
}

/*-----------------------------------*/
/**
 *FPGA数据计算是否正在进行
 */
/*-----------------------------------*/
int IsCircleTaskRunning_FpgaCvt()
{
	return  (1==G_FPGA_CIRCLE_TASK_RUNNING[0]) &&
			(0==G_FPGA_CIRCLE_TASK_RUNNING[1]);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void init_1st_2nd_circle_flag()
{
	init_1st_circle_flag();
	init_2nd_circle_flag();
}
/*-----------------------------------*/
/**
 *初始化任务标志为0
 */
/*-----------------------------------*/
void init_1st_2nd_task_circle_flag()
{
	init_1st_circle_flag();  //初始化第一圈标志为0
	init_2nd_circle_flag();  //初始化第二圈标志为0
	init_task_circle_flag(); //初始总任务圈标志为0
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
