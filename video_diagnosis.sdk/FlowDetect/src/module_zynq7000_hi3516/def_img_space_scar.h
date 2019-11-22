#ifndef		_DEF_IMG_SPACE_SCAR_H_
#define		_DEF_IMG_SPACE_SCAR_H_
/*-----------------------------------*/
#include <assert.h>
/*-----------------------------------*/
#define 	SCAR_IMG_MASK_CHANNEL_MAX		(8)
#define 	SCAR_IMG_MASK_FRAME_MAX			(48)
#define 	SCAR_IMG_MASK_SQE_MAX			(SCAR_IMG_MASK_CHANNEL_MAX*SCAR_IMG_MASK_FRAME_MAX)
/*-----------------------------------*/
int GetSpaceIdx_Scar(const int _mask_idx);
int GetFrameIdx_Scar(const int _mask_idx);
#endif
