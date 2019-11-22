#ifndef _PNG_UP_H
#define _PNG_UP_H
/*-----------------------------------*/
#include <assert.h>
/*-----------------------------------*/
#include "modules_ex/type.h"
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
void encodeWithState_cmd_ctrl(
		const char* _filename,
		const CMD_CTRL* const  _cmd);
/*-----------------------------------*/
int decodeWithState_cmd_ctrl(
		const char* filename,
		const CMD_CTRL* const  _cmd);
/*-----------------------------------*/
#endif
