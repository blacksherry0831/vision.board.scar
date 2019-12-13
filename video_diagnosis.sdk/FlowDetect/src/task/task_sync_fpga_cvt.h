#ifndef _TASK_SYNC_FPGA_CVT_H_
#define _TASK_SYNC_FPGA_CVT_H_
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void init_1st_2nd_circle_flag();
void init_1st_2nd_task_circle_flag();
/*-----------------------------------*/
int IsCircleTaskRunning_FpgaCvt();
/*-----------------------------------*/
void set_task_circle_start();
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void	set_1st_circle_start();
void	set_1st_circle_end();
int		get_1st_circle_start();
int		get_1st_circle_end();
int		get_1st_circle_running();
/*-----------------------------------*/
void	set_2nd_circle_start();
void	set_2nd_circle_end();
int		get_2nd_circle_start();
int		get_2nd_circle_end();
int		get_2nd_circle_running();
/*-----------------------------------*/
void	set_task_circle_start();
void	set_task_circle_end();
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#endif
