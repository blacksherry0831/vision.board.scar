/*
 * img_proc.h
 *
 *  Created on: 2020年4月10日
 *      Author: yjkj909
 */

#ifndef IMG_PROC_H_
#define IMG_PROC_H_

#include "opencv2/opencv.hpp"
#include "Line2Point.h"

enum DetectResult
{
	QUALIFIED = 0x01,  //合格
	UNQUALIFIED = 0x02,  //不合格
	UNKNOWN = 0x03,  //未知
};

int get_is_binary();  //二值化
int get_is_denoise();  //去噪
int get_is_blackSkin();  //黑皮
int get_is_hough();  //hough
int get_is_morphology();  //形态学
int get_is_showResult();  //结果展示
int get_blaskSkin_min_area();  //黑皮最小面积
int get_hough_thresold(); //hough点数阈值
int get_hough_min_length();  //hough最小线段长度
int get_hough_max_gap(); //hough最大线段间距
int get_hough_max_angle();  //hough最大角度
int get_crack_min_area();  //裂纹最小面积
int get_crack_aspect_ratio();  //裂纹长宽比
int get_crack_area_ratio();  //裂纹面积比

void set_is_binary(int _v);  //二值化
void set_is_denoise(int _v);  //去噪
void set_is_blackSkin(int _v);  //黑皮
void set_is_hough(int _v);  //hough
void set_is_morphology(int _v);  //形态学
void set_is_showResult(int _v);  //结果展示
void set_blaskSkin_min_area(int _v);  //黑皮最小面积
void set_hough_thresold(int _v); //hough点数阈值
void set_hough_min_length(int _v);  //hough最小线段长度
void set_hough_max_gap(int _v); //hough最大线段间距
void set_hough_max_angle(int _v);  //hough最大角度
void set_crack_min_area(int _v);  //裂纹最小面积
void set_crack_aspect_ratio(int _v);  //裂纹长宽比
void set_crack_area_ratio(int _v);  //裂纹面积比

void set_last_detect_result(enum DetectResult _v);  //设最终的检测结果
enum DetectResult get_last_detect_result();   //查最终的检测结果
int get_number_of_mask();  //一轮检测的蒙板图片总数
void inc_processed_cnt();  //一轮检测的已检测蒙板图片个数自增加1
int get_processed_cnt();  //获取 一轮检测的已检测蒙板图片个数

void Binary2Smooth_Line(IplImage * _img); //去噪
IplImage* ImgProcessIpl_BlackSkin(IplImage* _img, int* posFlag); //查找黑皮

void ImgProcessIpl_Base(IplImage * _img); //二值化+去噪

unsigned int ImgProc_PixelNumber_Gray(IplImage * _img, int _p); //计算白点数 即计算异常点数目

void ImgProcessIpl(IplImage * _img,int* posFlag); //根据相应参数对图像进行相应处理  计算二值化后异常点占总图像的比重  或者  进行hogh变换并寻找相应椭圆

std::vector<Line2Point> getHoughLinesBase(IplImage * _img_bin, IplImage * _img_draw, CvScalar _color, int _thickness, const double _remove_degree,
		const int _line_th, const double _line_len_min, const double _line_gap); //调用opencv函数进行hough变换 + 删除角度在90度附近的直线

std::vector<Line2Point> Hough_Line_CV_PROBABILISTIC_GetLine(CvArr * image, double rho, double theta, int threshold,
		double _lineLenMin, double _lineGap); //调用opencv函数 进行hough变换 返回hough直线的起点与重点

std::vector<Line2Point> LineRemove(std::vector<Line2Point>&  _lines, double _theta_c,
					double _theta_r);  //删除直线角度符合条件的直线   保存直线角度符合条件的直线

void LineDraw(std::vector<Line2Point>& _lines, IplImage * img_t, CvScalar _color, int _thickness); //在图上画直线

void LineCalAngle(std::vector<Line2Point>& _lines); //计算直线的角度

void ImgProcessIpl_PredictResult(const int posFlag); //结果判定

void ImgProcessIpl_ShowResult(IplImage* _img);  //判定结果展示

void img_proc_init(int _v);
#endif /* IMG_PROC_H_ */
