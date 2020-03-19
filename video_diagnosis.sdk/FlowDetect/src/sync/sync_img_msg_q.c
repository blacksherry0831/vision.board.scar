#include "sync_img_msg_q.h"
/*-----------------------------------*/
volatile int G_TCP_TRANS_THREADS=0;
/*-----------------------------------*/
/**
 *获取客户端交互线程数
 */
/*-----------------------------------*/
int GetTcpTransImgThreads()
{
	return G_TCP_TRANS_THREADS;  //与服务端连接的客户端交互线程数
}
/*-----------------------------------*/
/**
 *客户端交互线程数 加1
 */
/*-----------------------------------*/
void IncTcpTransImgThreads()
{
	__sync_fetch_and_add(&G_TCP_TRANS_THREADS,1);
}
/*-----------------------------------*/
/**
 *客户端交互线程数 加1
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
