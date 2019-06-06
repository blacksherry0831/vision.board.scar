#ifndef PRINTF_LOG_H
#define PRINTF_LOG_H
#include "linux_header.h"
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
//#define PRINTF_DBG(x,...) printf ("FILE:"__FILE__",LINE:%05d:"x"/n",__LINE__,##__VA_ARGS__)
#define PRINTF_DBG(x,...)      if(getPrintConsole())   printf (x,##__VA_ARGS__)
#else
#define PRINTF_DBG(x,...)
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
void printf_error();
/*-----------------------------------*/

#endif
