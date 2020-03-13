#include "png_up.h"
/*-----------------------------------*/
/**
 *将image编码成png图片并保存
 */
/*-----------------------------------*/
void encodeWithState(
		const char* filename,
		const unsigned char* image,
		unsigned width,
		unsigned height)
{
	unsigned error;
	unsigned char* png;
	size_t pngsize;
	LodePNGState state;

	lodepng_state_init(&state);  //png初始化
  /*optionally customize the state*/

	state.info_raw.colortype=LCT_GREY;  //色彩模式

	error = lodepng_encode(&png, &pngsize, image, width, height, &state);  //将原始的像素数据编码成一张PNG图像
	if(!error) lodepng_save_file(png, pngsize, filename);  //保存png图片

	/*if there's an error, display it*/
	if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

	lodepng_state_cleanup(&state);  //清空
	free(png);
}
/*-----------------------------------*/
/**
 *将png图片解码为像素数据
 */
/*-----------------------------------*/
int decodeWithState(const char* filename,char* dst,int _width,int _height,int _nChannels)
{
  unsigned error;
  unsigned char* image;
  unsigned width, height;
  unsigned char* png;
  size_t pngsize;
  LodePNGState state;
  int result_t=0;
  lodepng_state_init(&state);
  /*optionally customize the state*/
  state.info_raw.colortype=LCT_GREY;

  lodepng_load_file(&png, &pngsize, filename);
  error = lodepng_decode(&image, &width, &height, &state, png, pngsize);
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

  free(png);

  /*use image here*/
  /*state contains extra information about the PNG such as text chunks, ...*/
  assert(width==_width);
  assert(height==_height);
  unsigned int Size=width*height*_nChannels;
  if(error==0){

	  memcpy(dst,image,Size);
	  result_t=1;
  }

  /*free  image here*/
  lodepng_state_cleanup(&state);
  free(image);

  return  result_t;
}
/*-----------------------------------*/
/**
 *将cmd中的image编码成png图片并保存
 */
/*-----------------------------------*/
void encodeWithState_cmd_ctrl(
		const char* _filename,
		const CMD_CTRL* const  _cmd)
{

	const int UCHAR_SIZE=8;
	const IplImageU * imgU=GetIplImageUx(_cmd);
	const int width=UChar2Int(imgU->width,UCHAR_SIZE);
	const int height=UChar2Int(imgU->height,UCHAR_SIZE);
	unsigned char* data_t=(unsigned char*)GetIplImageImageData(_cmd);
	encodeWithState(_filename,data_t,width,height);  //将image编码成png图片并保存
}
/*-----------------------------------*/
/**
 *解码png图片为像素数据，并保存至cmd中
 */
/*-----------------------------------*/
int decodeWithState_cmd_ctrl(
		const char* _filename,
		const CMD_CTRL* const  _cmd)
{
	const int UCHAR_SIZE=8;
	const IplImageU * imgU=GetIplImageUx(_cmd);
	char* data_t=GetIplImageImageData(_cmd);
	assert(UChar2Int(imgU->IpAddrChannel,UCHAR_SIZE)>=0);
	const int width=UChar2Int(imgU->width,UCHAR_SIZE);
	const int height=UChar2Int(imgU->height,UCHAR_SIZE);
	const int nChannels=UChar2Int(imgU->nChannels,UCHAR_SIZE);
	return decodeWithState(_filename,data_t,width,height,nChannels);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/

