#include "dma_83c0_ex.h"
/*-----------------------------------*/

/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned char* getDmaVirtualAddr_space_ch_fr(int _space_ch,int _space_frame)
{
	unsigned char *src_addr=dmac_83c0_get_mem_ps_virtual_base_addr()+image_frame_dma_offset(_space_ch,_space_frame);

	return src_addr;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int getFpgaSrcAddr_space_ch_fr(const int _space_ch,const int _space_frame)
{
		const unsigned int  PhyChBaseAddr=PL_MEM_getChStartPhyAddr(_space_ch);
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

	unsigned int ps_phy_addr_dma = PS_DDR_PHYADDR_FOR_DMA_83C0 +image_frame_dma_offset(_space_ch,_space_frame);//dma addr

	return ps_phy_addr_dma;

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void dmac_trans_space_ch_fr(int _space_ch,int _space_frame)
{

	 if(dmac_83c0_pthread_mutex_lock()==SUCCESS){

					unsigned int phy_addr_img=getFpgaSrcAddr_space_ch_fr(_space_ch,_space_frame);

					const int dma_size_t=image_frame_size(_space_ch,_space_frame);
					const unsigned int ps_phy_addr_dma=getDmaPhysicsAddr_space_ch_fr( _space_ch,_space_frame);
					dmac_83c0_config_and_transfer(ps_phy_addr_dma,phy_addr_img, dma_size_t);

					if(dmac_83c0_pthread_mutex_unlock()==SUCCESS){
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
void dmac_trans_all_frame()
{

		int schi=0;
		int sfri=0;

		for(schi=0; schi <SPACE_CHANNEL_NUM;schi++){
			for(sfri=0;sfri<SPACE_FRAME_NUM;sfri++){
					if(is_space_frame_output(schi,sfri)){

						dmac_trans_space_ch_fr(schi,sfri);

					}
			}
		}

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
int SetDmaFrameByWorkMode(int _wm)
{

			if(GetProjectRun()==outside08){
							image_enable_output_frame_only_1();
			}else if(GetProjectRun()==inside08){

						if(WM_ORG_IMG==(getFpgaCircleWorkMode()&WM_ORG_IMG)){
							image_enable_output_frame_only_1();
						}else if(WM_DIFF_IMG==(getFpgaCircleWorkMode()&WM_DIFF_IMG)){
							image_enable_output_frame_only_2();
						}else{

						}

			}else if(GetProjectRun()==scar_detect_01){

						if(IsWorkMode_OrgImg()){
							image_enable_output_frame_only_1();
						}else if(IsWorkMode_DiffImg()){
							image_enable_output_frame_only_2();
						}else{

						}

			}else{

			}


	return 0;
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

	assert(img->f_data_size<=PS_DDR_LENGTH_FOR_DMA_83C0);

	 if(dmac_83c0_pthread_mutex_lock()==SUCCESS){

			unsigned char *src_addr=getDmaVirtualAddr_space_ch_fr(_space_ch,_space_fr);

			CopyImage(src_addr,img,_space_ch,_space_fr);

			if(dmac_83c0_pthread_mutex_unlock()==SUCCESS){

				result_t=TRUE;
			}

	 }

#if 1
	 PRINTF_DBG_EX("Channel:[%d] ",_space_ch);

	 TIME_END("memcpy a channel:");

#endif

	return result_t;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
