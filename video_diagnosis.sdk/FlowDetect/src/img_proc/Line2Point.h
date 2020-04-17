/*
 * Line2Point.h
 *
 *  Created on: 2020Äê4ÔÂ14ÈÕ
 *      Author: yjkj909
 */

#ifndef _LINE2POINT_H_
#define _LINE2POINT_H_

#include "opencv2/opencv.hpp"

class Line2Point
{
public:
	Line2Point(CvPoint _p1,	CvPoint _p2);
	~Line2Point();
public:
	static const double PI_HALF;
public:
	CvPoint mP1;
	CvPoint mP2;

	double mTheta_r;
	double mTheta_d;
private:
	int IsValid;
public:
	void	CalTheta();
	double	GetThetaDegrees();
	double	GetThetaRadians();
	void    SetValid();
	void    SetInvalid();
public:

};

#endif /* _LINE2POINT_H_ */
