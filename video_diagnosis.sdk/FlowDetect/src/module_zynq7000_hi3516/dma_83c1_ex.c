#include "dma_83c1_ex.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int dmac_83c1_trans_mask_img_ch_fr(int _space_ch,int _space_frame,const int _sz)
{

	 if(dmac_83c1_pthread_mutex_lock()==SUCCESS){


		 	 	 	unsigned int pl_mask_PhyAddr=Get_PL_MEM_MaskImage_PhyAddr(_space_ch,_space_frame);

					const unsigned int ps_phy_addr_dma=dmac_83c1_get_mem_ps_phy_base_addr();

					dmac_83c1_config_and_transfer(pl_mask_PhyAddr,ps_phy_addr_dma, _sz);

					if(dmac_83c1_pthread_mutex_unlock()==SUCCESS){
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
void dmac_83c1_trans_mask_img_cmd_ctrl(CMD_CTRL*  _cmd)
{
		const int UCHAR_SIZE=8;
		const IplImageU * imgU=GetIplImageUx(_cmd);

		char* data_t=GetIplImageImageData(_cmd);

		const int mask_pos=UChar2Int(imgU->IpAddrChannel,UCHAR_SIZE);;

		const int ch_space=GetSpaceIdx_Scar(mask_pos);
		const int ch_frame=GetFrameIdx_Scar(mask_pos);

		const int width=UChar2Int(imgU->width,UCHAR_SIZE);
		const int height=UChar2Int(imgU->height,UCHAR_SIZE);
		const int image_size=width*height;

		void*  ps_virtual_addr_dst=dmac_83c1_get_mem_ps_virtual_base_addr();

		memcpy(ps_virtual_addr_dst,data_t,image_size);

		dmac_83c1_trans_mask_img_ch_fr(ch_space,ch_frame,image_size);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
