#include "def_img_space_scar.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetSpaceIdx_Scar(const int _mask_idx)
{
	assert(_mask_idx>=0 && _mask_idx<SCAR_IMG_MASK_SQE_MAX);
	const int ch_space=_mask_idx%SCAR_IMG_MASK_CHANNEL_MAX;
	return ch_space;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetFrameIdx_Scar(const int _mask_idx)
{
	assert(_mask_idx>=0 && _mask_idx<SCAR_IMG_MASK_SQE_MAX);
	const int ch_frame=_mask_idx/SCAR_IMG_MASK_CHANNEL_MAX;
	return ch_frame;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
