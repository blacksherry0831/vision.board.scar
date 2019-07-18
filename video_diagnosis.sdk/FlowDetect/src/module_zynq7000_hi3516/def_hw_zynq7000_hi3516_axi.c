#include "def_hw_zynq7000_hi3516_axi.h"
/*-----------------------------------*/
static const float SCALE_INTRINSIC_INV_R1C1=SCALE_24_bit;
static const float SCALE_INTRINSIC_INV_R1C3=SCALE_16_bit;
static const float SCALE_INTRINSIC_INV_R2C2=SCALE_24_bit;
static const float SCALE_INTRINSIC_INV_R2C3=SCALE_16_bit;
/*-----------------------------------*/
const float SCALE_INTRINSIC=16;
/*-----------------------------------*/
const float SCALE_DISTORTION=SCALE_16_bit;
/*-----------------------------------*/
const unsigned int  ADDR_INTRINSIC_INV[3][3]={
				{ADDR_INTRINSIC_INV_R1C1,	0,							ADDR_INTRINSIC_INV_R1C3},
				{0,							ADDR_INTRINSIC_INV_R2C2,	ADDR_INTRINSIC_INV_R2C3},
				{0,							0,							0}
};
/*-----------------------------------*/
const unsigned int  ADDR_INTRINSIC[3][3]={
				{ADDR_INTRINSIC_FX,		0,						ADDR_INTRINSIC_CX},
				{0,						ADDR_INTRINSIC_FY,		ADDR_INTRINSIC_CY},
				{0,						0,						0}
};
/*-----------------------------------*/
const unsigned int  ADDR_DISTORTION[5][1]={
			{ADDR_DISTORTION_K1},
			{ADDR_DISTORTION_K2},
			{ADDR_DISTORTION_P1},
			{ADDR_DISTORTION_P2},
			{ADDR_DISTORTION_K3}
};
/*-----------------------------------*/
const unsigned int  SCALE_INTRINSIC_INV[3][3]={
						{SCALE_24_bit,		0,							SCALE_16_bit},
						{0,					SCALE_24_bit,				SCALE_16_bit},
						{0,					0,							0}
};
/*-----------------------------------*/
