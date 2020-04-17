/*
 * Line2Point.c
 *
 *  Created on: 2020年4月14日
 *      Author: yjkj909
 */

#include "Line2Point.h"

/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
const double Line2Point::PI_HALF=CV_PI/2;
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
Line2Point::Line2Point(CvPoint _p1, CvPoint _p2)
{
	this->mP1 = _p1;
	this->mP2 = _p2;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
Line2Point::~Line2Point(void)
{

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/

//算直线角度   单位：度
double Line2Point::GetThetaDegrees(void)
{
	mTheta_d = mTheta_r * 180 / CV_PI;
	//assert(mTheta_r > -180  && mTheta_r <= 180);
	return 0;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/

//算直线角度   单位：弧度
double Line2Point::GetThetaRadians(void)
{
	mTheta_r =atan2(mP2.y-mP1.y,mP2.x-mP1.x);
	//assert(mTheta_r > -CV_PI && mTheta_r <= CV_PI);
	return mTheta_r;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void Line2Point::SetValid()
{
	this->IsValid = 1;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void Line2Point::SetInvalid()
{
	this->IsValid = 0;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/

//算直线角度
void Line2Point::CalTheta(void)
{
	this->GetThetaRadians();  //算直线角度  单位：弧度
	this->GetThetaDegrees();  //算直线角度  单位：度
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
