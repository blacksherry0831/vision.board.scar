#include "mem_pl.h"
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int PL_MEM_getChStartPhyAddr(const int _ch)
{
	const unsigned int Img_base_Addr=PL_DDR3_ADDR_BASE+_ch*CHANNEL_BLOCK_SIZE;
	return Img_base_Addr;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
