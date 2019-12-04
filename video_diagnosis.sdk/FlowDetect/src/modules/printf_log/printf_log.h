#ifndef _PRINTF_LOG_H_
#define _PRINTF_LOG_H_
/*-----------------------------------*/
#include <stdio.h>
#include <stdlib.h>
/*-----------------------------------*/
#include <string.h>
#include <errno.h>
/*-----------------------------------*/
/*-----------------------------------*/
#include <sys/time.h>    // for gettimeofday()
/*-----------------------------------*/
#define _DEBUG_PRINT 1
/*-----------------------------------*/
extern void setPrintConsole(const int _p);
/*-----------------------------------*/
extern int getPrintConsole();
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#ifdef _DEBUG_PRINT

#define PRINTF_DBG_EX(x,...)    do{  if(getPrintConsole())   printf(x,##__VA_ARGS__);}while(0)
#else
#define PRINTF_DBG_EX(x,...)

#endif
/*-----------------------------------*/
#if defined(_DEBUG_PRINT)
#define DEBUG_PRINT(...)\
        do{\
        	if(getPrintConsole()){\
					fprintf(stderr,"-----DEBUG-----\n");\
					fprintf(stderr,"%s %s\n",__TIME__,__DATE__);\
					fprintf(stderr,"%s:%d:%s():",__FILE__,__LINE__,__func__);\
					fprintf(stderr,__VA_ARGS__);\
        	}\
        }while(0)
#endif
/*-----------------------------------*/
#define CK_F(x) \
if( (x) == (-1) ){ perror("-1,Failure");exit(EXIT_FAILURE);}
/*-----------------------------------*/
void printf_error();
/*-----------------------------------*/
#define TIME_START()  do{struct timeval startTime,endTime;float Timeuse;gettimeofday(&startTime,NULL);
/*-----------------------------------*/
#define TIME_END(X)		gettimeofday(&endTime,NULL);Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);	PRINTF_DBG_EX("%s = %f us,%f ms\n",X,Timeuse,Timeuse/1000);}while(0)
/*-----------------------------------*/
#endif
