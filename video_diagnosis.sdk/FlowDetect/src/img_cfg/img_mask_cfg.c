#include "img_mask_cfg.h"
/*-----------------------------------*/
#include "module_zynq7000_hi3516/mem_pl.h"
/*-----------------------------------*/
const int mMask_width=1920;
const int mMask_height=1080;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int 	Get_PL_MEM_MaskImage_PhyAddr_offset(const int _mask_frame)
{
	const unsigned int imgSize=image_mask_size();

	const unsigned int blank_area=imgSize*8;
	const unsigned int result_area=imgSize*2;

	const unsigned int offset=_mask_frame*imgSize;
	const unsigned int mask_offset= blank_area+result_area+offset;
	return mask_offset;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int 	Get_PL_MEM_MaskImage_PhyAddr(
		const int _space_ch,
		const int _space_frame)
{
			assert(_space_ch<SCAR_IMG_MASK_CHANNEL_MAX);
			assert(_space_frame<SCAR_IMG_MASK_FRAME_MAX);

			const unsigned int  PhyChBaseAddr=PL_MEM_getChStartPhyAddr(_space_ch);
			const unsigned int  PhyChFrameOffsetAddr=Get_PL_MEM_MaskImage_PhyAddr_offset(_space_frame);
			const unsigned int 	PhySpaceFrameAddr=PhyChBaseAddr+PhyChFrameOffsetAddr;
			return PhySpaceFrameAddr;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int image_mask_size()
{
	const unsigned int imgSize=mMask_width*mMask_height;
	return imgSize;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
