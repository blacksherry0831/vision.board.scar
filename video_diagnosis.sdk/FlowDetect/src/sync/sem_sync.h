#ifndef _SEM_SYNC_H_
#define _SEM_SYNC_H_
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#include <pthread.h>
#include <semaphore.h>
/*-----------------------------------*/
#include "modules/printf_log/printf_log.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

int  post_fpga_start_sig();
int wait_fpga_cvt_down_sig();
int  post_dma_cpy_down_sig_2_fpga();
int post_dma_cpy_down_sig_2_memcpy();
int wait_mem_cpy_down_sig();
int  wait_dma_cpy_down_sig_4_memcpy();
int  post_mem_cpy_down_sig();
int  wait_dma_cpy_down_sig_4_fpga();
int  post_fpga_cvt_down_sig();
int destorySemSignal();

#endif
