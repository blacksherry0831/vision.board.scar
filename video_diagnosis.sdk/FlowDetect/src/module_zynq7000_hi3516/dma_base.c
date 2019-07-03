#include "dma_base.h"
/*-----------------------------------*/
static MAP_OBJ  DMA_TRANS={0};

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned char* GetVirtualAddrDMA(int _ch)
{
	unsigned char *src_addr=NULL;

			src_addr=get_ps_ddr_virtual_baseaddr()+_ch*image_size_frame();

	return src_addr;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int getPhyFrameBaseAddr(int _ch,int _frame)
{
	unsigned int  PhyChBaseAddr=getPhyChBaseAddr(_ch);
	unsigned int  PhyChFrameAddr=0;

	if(_frame>=0&&_frame<=7){

			PhyChFrameAddr=PhyChBaseAddr+IMAGE_SIZE_AVG+_frame*image_size_frame();

	}else if(_frame==-1){
				PhyChFrameAddr=PhyChBaseAddr;
	}else{
			assert(0);
	}

	return PhyChFrameAddr;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int video_map_dmac_ch(unsigned char _ch,int _frame,unsigned int *_phyaddr)
{
	unsigned int  PhyChFrameAddr=getPhyFrameBaseAddr(_ch,_frame);
	unsigned int  MAP_SIZE=GetFrameSize(_frame);

	*_phyaddr=PhyChFrameAddr;

	SetCurrentDmaCh(_ch);

	return MAP_SIZE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int getDmaDstAddr(unsigned char _ch,int _frame)
{
	assert(_frame>=0);

	const unsigned int  MAP_SIZE=GetFrameSize(_frame);
	unsigned int ps_phy_addr_dma = PS_DDR_PHYADDR_FOR_DMA + _ch*MAP_SIZE;//dma addr
	return ps_phy_addr_dma;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int dmac_trans(unsigned char _ch,int _frame)
{
	 if(pthread_mutex_lock(&DMA_TRANS.lock)==SUCCESS){

		 		unsigned int ps_phy_addr_dma=getDmaDstAddr(_ch,_frame);
				unsigned int phy_addr_img=0;
				int Size2tran=video_map_dmac_ch(_ch,_frame,&phy_addr_img);//image phy addr
				dmac_config_and_transfer(ps_phy_addr_dma,phy_addr_img, Size2tran);

				if(pthread_mutex_unlock(&DMA_TRANS.lock)==SUCCESS){
					return TRUE;
				}

	 }
			return FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int memcpyDMA2MemChEx(CMD_CTRL* img,unsigned int _ch)
{
	int result_t=FALSE;
#if 1
	TIME_START();
#endif

	assert(img->f_data_size<=PS_DDR_LENGTH_FOR_DMA);

	 if(pthread_mutex_lock(&DMA_TRANS.lock)==SUCCESS){

			unsigned char *src_addr=GetVirtualAddrDMA(_ch);

			CopyImage(src_addr,img,_ch);

			if(pthread_mutex_unlock(&DMA_TRANS.lock)==SUCCESS){

				result_t=TRUE;
			}

	 }

#if 1
	 PRINTF_DBG("Channel:[%d] ",_ch);

	TIME_END("memcpy a channel:");

#endif

	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int dmac_addr_mmap(void)
{
	int result_t=0;
	pthread_mutex_init(&(DMA_TRANS.lock),NULL);
	result_t=dmac_addr_mmap_hw();
    return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int dmac_addr_unmap(void)
{
	int result_t=0;
	pthread_mutex_lock(&DMA_TRANS.lock);

	result_t=dmac_addr_unmap_hw();

	pthread_mutex_unlock(&DMA_TRANS.lock);
    pthread_mutex_destroy(&(DMA_TRANS.lock));

    return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
