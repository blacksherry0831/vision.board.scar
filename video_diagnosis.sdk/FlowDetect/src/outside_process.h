#ifndef OUTSIDE_PROCESS_H
#define OUTSIDE_PROCESS_H
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
/**
 *
 *0x4000,0000|0x0000,0000----------------------------------1Ch-Gray-----| 1920*1080*8==16588800==0x00FD,2000
 *			 |0x00FD,2000=1920*1080*(8+0)------------------1Ch-Frame-0--| 1920*1080*1== 2073600==0x001F,A400‬
 *			 |------------1920*1080*(8+1)------------------1Ch-Frame-1--| 1920*1080*1== 2073600
 *			 |------------1920*1080*(8+2)------------------1Ch-Frame-2--|
 *			 |------------1920*1080*(8+n)------------------1Ch-Frame-n--|
 *			 |----------------------blank----------------(0x0800,0000-1)| 0x0800,0000==128MB
 *			 @@Channel(N)@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 *		 	 |0x0800,0000*(N-1)----------------------------NCh-Gray-----| 1920*1080*8==16588800==0x00FD,2000
 *			 |------------1920*1080*(8+0)------------------1Ch-Frame-0--| 1920*1080*1== 2073600==0x001F,A400‬
 *			 |------------1920*1080*(8+1)------------------1Ch-Frame-1--| 1920*1080*1== 2073600
 *			 |------------1920*1080*(8+2)------------------1Ch-Frame-2--|
 *			 |------------1920*1080*(8+n)------------------1Ch-Frame-n--|
 *			 |----------blank----------------------(0x8,000,000*(N-1)-1)|
 *
 */
/*-----------------------------------------------------------------------------------------------*/
#define PL_DDR3_ADDR_BASE 		 (0x40000000)
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
#define PL_PARA_ADDR_BASE   	 (0x80000000)
#define PL_PARA_ADDR_SIZE   	 (0x00001000)
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

#endif