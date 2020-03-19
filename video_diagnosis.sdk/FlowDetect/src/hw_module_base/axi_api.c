#include "axi_api.h"
/*-----------------------------------*/
/**
 *函数说明:地址拓展，10位地址拓展成12位地址
输入:无
输出:无
 */
/*-----------------------------------*/
void UsertoAXILite(
		unsigned int virtual_addr,
		unsigned int phy_addr,
		unsigned char *p_ucData,
		int Size)
{
    if(Size > 0x10000)
    {
        PRINTF_DBG_EX("Size is out!\n");
        return;
    }

	int i;

   if((phy_addr >= 0x80000000)&&(phy_addr < 0x90000000))
   {
	   *(unsigned int*)p_ucData = *(volatile unsigned int*)(virtual_addr);
   }
   else if((phy_addr >= 0x40000000)&&(phy_addr < 0x80000000))
   {
	  for(i=0;i<Size/4;i++){
		  *(unsigned int*)(p_ucData+i*4) = *(volatile unsigned int*)(virtual_addr+i*4);
	  }

   }else{
	   PRINTF_DBG_EX("Address not used!\n");
   }
   return;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void AXILitetoUser(
		const unsigned int virtual_addr,
		const unsigned int phy_addr,
		const unsigned char *p_ucData,
		const int Size)
{
    if(Size > 0x10000)
    {
        PRINTF_DBG_EX("Size is out!\n");
        return;
    }
	int i;
   if((phy_addr >= 0x80000000)&&(phy_addr < 0x90000000))
   {
		*(unsigned int*)(virtual_addr) = 0xAAAA5555;
		*(unsigned int*)(virtual_addr) = phy_addr;
		*(unsigned int*)(virtual_addr) = *(unsigned int*)p_ucData;
		*(unsigned int*)(virtual_addr) = 0x5555AAAA;
   }
   else if((phy_addr >= 0x40000000)&&(phy_addr < 0x80000000))
   {
	  for(i=0;i<Size/4;i++){
		  *(unsigned int*)(virtual_addr+i*4) = *(unsigned int*)(p_ucData+i*4);
	  }
   }else{
	   PRINTF_DBG_EX("Address not used!\n");
   }

   return;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int AXILitemmapEx(const unsigned char* _dev,unsigned int Addr,unsigned int *ptrUiFd,void **_pptr_virtual_addr,int MAP_SIZE)
{
	*ptrUiFd = open((const char*)_dev, O_RDWR|O_SYNC);
    if(ptrUiFd < 0)
    {
        PRINTF_DBG_EX("open %s failed!\n",_dev);
        return -1;
    }
    // 按页存储，不能超过4k（1页），（ 0x1000）
    *_pptr_virtual_addr = mmap(NULL, MAP_SIZE , PROT_READ | PROT_WRITE, MAP_SHARED, *ptrUiFd, Addr);

    if(_pptr_virtual_addr == NULL)
    {
        PRINTF_DBG_EX("mmap failed!\n");
        return -1;
    }

    return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void AXILiteunmmapEx(unsigned int *ptrUiFd,void **_pptr_virtual_addr,int MAP_SIZE)
{

   if(NULL != *_pptr_virtual_addr){
	   munmap(*_pptr_virtual_addr, MAP_SIZE);
	   *_pptr_virtual_addr = NULL;
   }

   if(*ptrUiFd >= 0)
   {
	   close(*ptrUiFd);
	   *ptrUiFd=0;
   }

   return ;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int AXILitemmapExS(MAP_OBJ* mapObj)
{
	mapObj->fd = open((const char*) (mapObj->DEV), O_RDWR|O_SYNC);
    if(mapObj->fd < 0)
    {
        PRINTF_DBG_EX("open %s failed!\n",mapObj->DEV);
        return -1;
    }
    // 按页存储，不能超过4k（1页），（ 0x1000）
   mapObj->virtual_addr = (unsigned char*)mmap(NULL, mapObj->SIZE , PROT_READ | PROT_WRITE, MAP_SHARED, mapObj->fd, mapObj->ADDR);

    if(mapObj->virtual_addr == NULL)
    {
        PRINTF_DBG_EX("mmap failed!\n");
        return -1;
    }

    return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void AXILiteunmmapExS(MAP_OBJ* mapObj)
{

   if(NULL != mapObj->virtual_addr){
	   munmap(mapObj->virtual_addr, mapObj->SIZE);
	   mapObj->virtual_addr = NULL;
   }

   if(mapObj->fd >= 0)
   {
	   close(mapObj->fd);
	   mapObj->fd=-1;
   }

   return ;
}

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
//函数功能：向PL端 outside 模块发送控制参数
// 0x100: 复位 outside 模块
// 0x101: 数据模式 - 0x0正常模式 sensor的数据， 0x1内部测试模块数据， 0x2全零测试数据
// 0x102: 触发工作 - 先发 0x1 再发送 0x0
// 0x103: 工作模式 - 0x0 求和、平方和  0x1 求奇异点

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
