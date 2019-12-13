#include "sync_img_msg_q.h"
/*-----------------------------------*/
volatile int G_TCP_TRANS_THREADS=0;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetTcpTransImgThreads()
{
	return G_TCP_TRANS_THREADS;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void IncTcpTransImgThreads()
{
	__sync_fetch_and_add(&G_TCP_TRANS_THREADS,1);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void DecTcpTransImgThreads()
{
	__sync_fetch_and_sub(&G_TCP_TRANS_THREADS,1);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
