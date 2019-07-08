#include "dma_base.h"
/*-----------------------------------*/
static MAP_OBJ  DMA_TRANS={0};

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned char* getDmaVirtualAddr_space_ch_fr(int _space_ch,int _space_frame)
{
	unsigned char *src_addr=get_ps_ddr_virtual_baseaddr()+image_frame_dma_offset(_space_ch,_space_frame);

	return src_addr;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int getFpgaSrcAddr_space_ch_fr(const int _space_ch,const int _space_frame)
{
		const unsigned int  PhyChBaseAddr=getPhyChBaseAddr(_space_ch);
		const unsigned int  PhyChFrameOffsetAddr=image_frame_fpga_ps_offset(_space_ch,_space_frame);
		const unsigned int 	PhySpaceFrameAddr=PhyChBaseAddr+PhyChFrameOffsetAddr;
		return PhySpaceFrameAddr;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int getDmaPhysicsAddr_space_ch_fr(const int _space_ch,const int _space_frame)
{
	assert(_space_frame>=0);

	unsigned int ps_phy_addr_dma = PS_DDR_PHYADDR_FOR_DMA +image_frame_dma_offset(_space_ch,_space_frame);//dma addr

	return ps_phy_addr_dma;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int dmac_trans_2(int _space_ch,int _space_frame)
{
	 if(pthread_mutex_lock(&DMA_TRANS.lock)==SUCCESS){

				unsigned int phy_addr_img=getFpgaSrcAddr_space_ch_fr(_space_ch,_space_frame);

				const int dma_size_t=image_frame_size(_space_ch,_space_frame);
				const unsigned int ps_phy_addr_dma=getDmaPhysicsAddr_space_ch_fr( _space_ch,_space_frame);
				dmac_config_and_transfer(ps_phy_addr_dma,phy_addr_img, dma_size_t);

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
int memcpyDMA2MemChEx(CMD_CTRL* img,const  int _space_ch,const int _space_fr)
{
	int result_t=FALSE;
#if 1
	TIME_START();
#endif

	assert(img->f_data_size<=PS_DDR_LENGTH_FOR_DMA);

	 if(pthread_mutex_lock(&DMA_TRANS.lock)==SUCCESS){

			unsigned char *src_addr=getDmaVirtualAddr_space_ch_fr(_space_ch,_space_fr);

			CopyImage(src_addr,img,_space_ch,_space_fr);

			if(pthread_mutex_unlock(&DMA_TRANS.lock)==SUCCESS){

				result_t=TRUE;
			}

	 }

#if 1
	 PRINTF_DBG("Channel:[%d] ",_space_ch);

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
