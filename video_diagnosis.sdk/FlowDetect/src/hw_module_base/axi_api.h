#ifndef _AXI_API_H
#define _AXI_API_H
/*-----------------------------------*/
#include "linux_header.h"
/*-----------------------------------*/
#include "modules/printf_log/printf_log.h"
/*-----------------------------------*/

/*-----------------------------------*/
typedef struct _MMAP_OBJECT
{
	unsigned char DEV[256];
	unsigned int  ADDR;
	unsigned int  SIZE;
	unsigned char *virtual_addr;
	unsigned int   fd;
	//int openStat;
	//int mapStat;
	pthread_mutex_t lock;
}MAP_OBJ;
/*-----------------------------------*/
extern void UsertoAXILite(
		unsigned int virtual_addr,
		unsigned int phy_addr,
		unsigned char *p_ucData,
		int Size);
/*-----------------------------------*/
extern void AXILitetoUser(
		const unsigned int virtual_addr,
		const unsigned int phy_addr,
		const unsigned char *p_ucData,
		const int Size);
/*-----------------------------------*/
extern int AXILitemmapEx(const unsigned char* _dev,unsigned int Addr,unsigned int *ptrUiFd,void **_pptr_virtual_addr,int MAP_SIZE);
/*-----------------------------------*/
extern void AXILiteunmmapEx(unsigned int *ptrUiFd,void **_pptr_virtual_addr,int MAP_SIZE);
/*-----------------------------------*/
/**
 *
 * D=0 W=0  D=0 W=1//diff image
 * D=2 W=0  D=0 W=1//org image
 *
 */
/*-----------------------------------*/

/*-----------------------------------*/
void AXILiteunmmapExS(MAP_OBJ* mapObj);
int AXILitemmapExS(MAP_OBJ* mapObj);
/*-----------------------------------*/
#endif
