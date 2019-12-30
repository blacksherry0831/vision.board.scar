#include "sync_pl_mem_4_8_lock.h"
/*-----------------------------------*/
static pthread_mutex_t MUTEX_PL_4_8_MEM = PTHREAD_MUTEX_INITIALIZER;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int PL_MEM_48_Lock()
{
	return pthread_mutex_lock(&MUTEX_PL_4_8_MEM);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int PL_MEM_48_Unlock()
{
	return pthread_mutex_unlock(&MUTEX_PL_4_8_MEM);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
