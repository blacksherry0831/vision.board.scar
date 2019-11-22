#ifndef _PNG_UP_H
#define _PNG_UP_H
/*-----------------------------------*/
#include <assert.h>
/*-----------------------------------*/
#include <modules/lodepng/lodepng.h>
/*-----------------------------------*/
int decodeWithState(
		const char* filename,
		char* dst,
		int _width,
		int _height,
		int _nChannels);
/*-----------------------------------*/
void encodeWithState(
		const char* filename,
		const unsigned char* image,
		unsigned width,
		unsigned height);
/*-----------------------------------*/
#endif
