#include "axi_api.h"
/*-----------------------------------*/
/**
 *����˵��:��ַ��չ��10λ��ַ��չ��12λ��ַ
����:��
���:��
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
    // ��ҳ�洢�����ܳ���4k��1ҳ������ 0x1000��
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
    // ��ҳ�洢�����ܳ���4k��1ҳ������ 0x1000��
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
//�������ܣ���PL�� outside ģ�鷢�Ϳ��Ʋ���
// 0x100: ��λ outside ģ��
// 0x101: ����ģʽ - 0x0����ģʽ sensor�����ݣ� 0x1�ڲ�����ģ�����ݣ� 0x2ȫ���������
// 0x102: �������� - �ȷ� 0x1 �ٷ��� 0x0
// 0x103: ����ģʽ - 0x0 ��͡�ƽ����  0x1 �������

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
