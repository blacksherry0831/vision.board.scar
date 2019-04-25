#ifndef AXI_API_H
#define AXI_API_H
/*-----------------------------------*/
#include "../linux_header.h"
#include "../outside_process.h"
#include "../def.h"
#include "../type.h"
/*-----------------------------------*/
typedef struct _MMAP_OBJECT
{
	unsigned int  ADDR;
	unsigned int  SIZE;
	unsigned char *virtual_addr;
	unsigned int   fd;
	//int openStat;
	//int mapStat;
	pthread_mutex_t lock;
}MAP_OBJ;
/*-----------------------------------*/
void UsertoAXILite(int virtual_addr,int phy_addr,unsigned char *p_ucData,int Size);
/*-----------------------------------*/
extern void AXILitetoUser(int virtual_addr,int phy_addr,unsigned char *p_ucData,int Size);
/*-----------------------------------*/
extern int AXILitemmapEx(int Addr,unsigned int *ptrUiFd,void **_pptr_virtual_addr,int MAP_SIZE);
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
