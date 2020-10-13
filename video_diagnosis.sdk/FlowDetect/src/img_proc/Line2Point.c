/*
 * Line2Point.c
 *
 *  Created on: 2020��4��14��
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

//��ֱ�߽Ƕ�   ��λ����
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

//��ֱ�߽Ƕ�   ��λ������
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

//��ֱ�߽Ƕ�
void Line2Point::CalTheta(void)
{
	this->GetThetaRadians();  //��ֱ�߽Ƕ�  ��λ������
	this->GetThetaDegrees();  //��ֱ�߽Ƕ�  ��λ����
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/