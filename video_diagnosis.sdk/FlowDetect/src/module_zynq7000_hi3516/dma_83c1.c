#include "dma_83c1.h"
/*-----------------------------------*/
static DMA_PS_PL_OBJ DMA_PL2PS_83c1;
/*-----------------------------------*/
unsigned char *dmac_83c1_get_mem_ps_phy_base_addr()
{
	return (unsigned char *)DMA_PL2PS_83c1.MEM_PS_Base_Addr_Phy;
}
/*-----------------------------------*/
unsigned char *dmac_83c1_get_mem_ps_virtual_base_addr()
{
	return DMA_PL2PS_83c1.MEM_PS_Base_Addr_Virtual;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int dmac_83c1_pthread_mutex_lock()
{
	return pthread_mutex_lock(&DMA_PL2PS_83c1.lock);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int dmac_83c1_pthread_mutex_unlock()
{
	return pthread_mutex_unlock(&DMA_PL2PS_83c1.lock);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int		dmac_83c1_init_pl2ps_obj(void)
{

		DMA_PL2PS_83c1.DMA_Base_Addr_Phy=PL_2_PS_DMA_BASEADDR_83C1;
		DMA_PL2PS_83c1.DMA_Space_size=PL_RX_DMA_MMAP_LENGTH;

		DMA_PL2PS_83c1.MEM_PS_Base_Addr_Phy=PS_DDR_PHYADDR_FOR_DMA_83C1;
		DMA_PL2PS_83c1.MEM_PS_Space_size=PS_DDR_LENGTH_FOR_DMA_83C1;

		assert(strlen(MEM_DEV)<256);

		strcpy( (char *)DMA_PL2PS_83c1.DEV , MEM_DEV);

		pthread_mutex_init(&(DMA_PL2PS_83c1.lock),NULL);

	return 1;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int		dmac_83c1_destory_pl2ps_obj(void)
{

		pthread_mutex_destroy(&(DMA_PL2PS_83c1.lock));
		memset(&DMA_PL2PS_83c1,0,sizeof(DMA_PS_PL_OBJ));
		return 1;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int		dmac_83c1_addr_mmap_hw(void)
{
		dmac_83c1_init_pl2ps_obj();
		return dmac_addr_mmap_hw_base(&DMA_PL2PS_83c1);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int		dmac_83c1_addr_unmap_hw(void)
{

		int result_t=0;

		dmac_83c1_pthread_mutex_lock();

				result_t=dmac_addr_unmap_hw_base(&DMA_PL2PS_83c1);

		dmac_83c1_pthread_mutex_unlock();

		dmac_83c1_destory_pl2ps_obj();

	    return result_t;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

int 	dmac_83c1_config_and_transfer(
		unsigned int dst_phyaddr,
		unsigned int src_phyaddr,
		unsigned int len)
{
	return dmac_config_and_transfer_base(&DMA_PL2PS_83c1,
									dst_phyaddr,
									src_phyaddr,
									len);
}
