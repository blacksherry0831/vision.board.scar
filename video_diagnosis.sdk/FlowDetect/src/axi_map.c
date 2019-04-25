#include "axi_map.h"
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
volatile unsigned char  m_current_ch=0xFF;
volatile unsigned char *m_virtual_addr   = NULL;
volatile unsigned int   m_uiFd           = -1;
volatile unsigned int   m_size			=0;

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
volatile unsigned char *g_virtual_addr     = NULL;
volatile unsigned int   g_uiFd            = -1;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void* getVirtualChBaseAddr(int _ch)
{
	assert(g_virtual_addr!=NULL);
	assert(0xFF==m_current_ch);
	unsigned char* ch_base_Addr=g_virtual_addr+_ch*CHANNEL_BLOCK_SIZE;
	return ch_base_Addr;
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
void* getVitrualChFrameAddr(int _ch,int _frame)
{
	assert(g_virtual_addr!=NULL);
	assert(0xFF==m_current_ch);
	unsigned char *BaseAddr  = getVirtualChBaseAddr(_ch);
	unsigned char *FrameAddr = BaseAddr+_frame*image_size_frame();
	return FrameAddr;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int getPhyChFrameAddr(int _ch,int _frame)
{
	unsigned int phy_ch_base_addr=getPhyChBaseAddr(_ch);

	unsigned int Img_base_Addr= phy_ch_base_addr+_frame*image_size_frame();

	return Img_base_Addr;
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
int video_map(unsigned int _addr,unsigned int _size)
{
		m_uiFd = open(MEM_DEV, O_RDWR|O_SYNC);
		m_size=_size;
		if(m_uiFd ==-1)
		{
			PRINTF_DBG("open %s failed!\n",MEM_DEV);
			return -1;
		}
		m_virtual_addr = mmap(NULL, _size , PROT_READ | PROT_WRITE, MAP_SHARED, m_uiFd,  _addr);
		if(m_virtual_addr == MAP_FAILED)
		{
			PRINTF_DBG("mmap failed!\n");
			printf_error();
			return -1;
		}else{

		}

		return 1;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int video_map_ch(unsigned char _ch,int _frame)
{
	unsigned int  PhyChBaseAddr=getPhyChBaseAddr(_ch);
	unsigned int  PhyChFrameAddr;
	unsigned int  MAP_SIZE=0;
	if(_frame>=0&&_frame<=7){
			PhyChFrameAddr=PhyChBaseAddr+IMAGE_SIZE_AVG+_frame*image_size_frame();
			MAP_SIZE=image_size_frame();
	}else	if(_frame==-1){
			PhyChFrameAddr=PhyChBaseAddr;
			MAP_SIZE=IMAGE_SIZE_AVG;
	}else{
		assert(0);
	}




	video_map(PhyChFrameAddr,MAP_SIZE);


	m_current_ch=_ch;
	return MAP_SIZE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void video_map_all_ch()
{
	const unsigned int ADDR_BASE=PL_DDR3_ADDR_BASE;
	const unsigned int SIZE=CHANNEL_BLOCK_SIZE*CHANNELS;

	video_map(ADDR_BASE,SIZE);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int memcpy_video_avg(void * _data,int _ch,int _frame,int _size)
{
	assert(_size<=m_size);
	assert(_data!=NULL);
	assert(_ch>=0&&_ch<=7);
	assert(_size==IMAGE_SIZE_AVG);

	unsigned char *ptr=m_virtual_addr+_ch*CHANNEL_BLOCK_SIZE;

	memcpy(_data,ptr,_size);

	return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int memcpy_video_frame(void * _data,int _Channel,int _frame,int _size)
{
		assert(_size<=m_size);
		assert(_data!=NULL);
		assert(_Channel>=0&&_Channel<=7);

		assert(_size==image_size_frame());

		unsigned char *ptr_ch=m_virtual_addr+_Channel*CHANNEL_BLOCK_SIZE;
		unsigned char *ptr_fr=ptr_ch+image_size_frame()*_frame;

		memcpy(_data,ptr_fr,_size);

	return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int video_unmap()
{
		munmap(m_virtual_addr, m_size);
		close(m_uiFd);
		m_virtual_addr=NULL;
		m_uiFd=-1;
		return 1;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int memcpy_video(void * _data,int _ch,int _frame,int _size)
{
	assert(_size<=m_size);
	assert(_data!=NULL);
	assert(_ch==m_current_ch);
	memcpy(_data,m_virtual_addr,_size);
	return 0;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int write_tcp_direct(int socketfd,int _size)
{



    dmac_transfer_init();

	return writen(socketfd,m_virtual_addr,_size);

}
/*-----------------------------------*/
/**
 *函数说明:地址拓展，10位地址拓展成12位地址
输入:无
输出:无
 */
/*-----------------------------------*/
int AXILitemmap(int Addr)
{
    g_uiFd = open(MEM_DEV, O_RDWR|O_SYNC);
    if(g_uiFd < 0)
    {
        PRINTF_DBG("open %s failed!\n",MEM_DEV);
        return -1;
    }
    // 按页存储，不能超过4k（1页），（ 0x1000）
    g_virtual_addr = mmap(NULL, 0x1000 , PROT_READ | PROT_WRITE, MAP_SHARED, g_uiFd, Addr);
    if(g_virtual_addr == NULL)
    {
        PRINTF_DBG("mmap failed!\n");
        return -1;
    }

    return 0;
}
/*-----------------------------------*/
/**
*函数说明:地址拓展，10位地址拓展成12位地址
*输入:无
*输出:无
*/
/*-----------------------------------*/
void AXILiteunmmap(void)
{

   if(NULL != g_virtual_addr){
	   munmap(g_virtual_addr, 0x1000);
	   g_virtual_addr = NULL;
   }

   if(g_uiFd >= 0)
   {
	   close(g_uiFd);
   }

   return ;
}
/*-----------------------------------*/
/**
 *函数说明:地址拓展，10位地址拓展成12位地址
输入:无
输出:无
 */
/*-----------------------------------*/


/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
