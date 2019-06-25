#include "opencv_base.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int IsEffectiveRect(const CvRect*  _rect)
{
	if(		(_rect->x>=0)&&
			(_rect->y>=0)&&
			(_rect->width>0)&&
			(_rect->height>0)	){
		return TRUE;
	}
	return FALSE;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
