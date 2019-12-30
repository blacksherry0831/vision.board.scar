#include "sync_ps_mem_0_4_lock.h"
/*-----------------------------------*/
static pthread_mutex_t MUTEX_PS_0_4_MEM = PTHREAD_MUTEX_INITIALIZER;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int PS_MEM_04_Lock()
{
	return pthread_mutex_lock(&MUTEX_PS_0_4_MEM);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int PS_MEM_04_Unlock()
{
	return pthread_mutex_unlock(&MUTEX_PS_0_4_MEM);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
