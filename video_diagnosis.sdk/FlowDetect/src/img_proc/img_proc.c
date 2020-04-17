/*
 * img_proc.c
 *
 *  Created on: 2020年4月10日
 *      Author: yjkj909
 */

#include "img_proc.h"

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

static int is_binary = FALSE;  //二值化
static int is_denoise = FALSE;  //去噪
static int is_blackSkin = FALSE;  //黑皮
static int is_hough = FALSE;  //hough
static int is_morphology = FALSE;  //形态学
static int is_showResult = FALSE;  //结果展示

static int blaskSkin_min_area = 0;  //黑皮最小面积
static int hough_thresold = 0;  //hough点数阈值
static int hough_min_length = 0;  //hough最小线段长度*100
static int hough_max_gap = 0;  //hough最大线段间距*100
static int hough_max_angle = 0;  //hough最大角度*100
static int crack_min_area = 0;  //裂纹最小面积
static int crack_aspect_ratio = 0;  //裂纹长宽比*100
static int crack_area_ratio = 0;  //裂纹面积比*100

static int number_of_mask = 0;  //一轮检测的蒙板图片总数，用于后期图片合成
static int processed_cnt = 0;   //一轮检测的已检测蒙板图片个数，用于后期图片合成
static enum DetectResult last_detect_result = QUALIFIED;  //最终的检测结果

/*-----------------------------------*/

//获取是否二值化
int get_is_binary()
{
	return is_binary;
}

/*-----------------------------------*/

//获取是否去噪
int get_is_denoise()
{
	return is_denoise;
}

/*-----------------------------------*/

//获取是否黑皮
int get_is_blackSkin()
{
	return is_blackSkin;
}

/*-----------------------------------*/

//获取是否hough
int get_is_hough()
{
	return is_hough;
}

/*-----------------------------------*/

//获取是否形态学
int get_is_morphology()
{
	return is_morphology;
}

/*-----------------------------------*/

//获取是否结果展示
int get_is_showResult()
{
	return is_showResult;
}

/*-----------------------------------*/

//获取黑皮最小面积
int get_blaskSkin_min_area()
{
	return blaskSkin_min_area;
}

/*-----------------------------------*/

//获取点数阈值
int get_hough_thresold()
{
	return hough_thresold;
}

/*-----------------------------------*/

//获取hough最小线段长度*100
int get_hough_min_length()
{
	return hough_min_length;
}

/*-----------------------------------*/

//获取hough最大线段间距*100
int get_hough_max_gap()
{
	return hough_max_gap;
}

/*-----------------------------------*/

//获取hough最大角度*100
int get_hough_max_angle()
{
	return hough_max_angle;
}

/*-----------------------------------*/

//获取裂纹最小面积
int get_crack_min_area()
{
	return crack_min_area;
}

/*-----------------------------------*/

//获取裂纹长宽比*100
int get_crack_aspect_ratio()
{
	return crack_aspect_ratio;
}

/*-----------------------------------*/

//获取裂纹面积比*100
int get_crack_area_ratio()
{
	return crack_area_ratio;
}

/*-----------------------------------*/

//设是否二值化
void set_is_binary(int _v)
{
	is_binary = _v;
}

/*-----------------------------------*/

//设是否去噪
void set_is_denoise(int _v)
{
	is_denoise = _v;
}

/*-----------------------------------*/

//设是否黑皮检测
void set_is_blackSkin(int _v)
{
	is_blackSkin = _v;
}

/*-----------------------------------*/

//设是否hough
void set_is_hough(int _v)
{
	is_hough = _v;
}

/*-----------------------------------*/

//设是否形态学
void set_is_morphology(int _v)
{
	is_morphology =_v;
}

/*-----------------------------------*/

//设是否形态学
void set_is_showResult(int _v)
{
	is_showResult = _v;
}

/*-----------------------------------*/

//设黑皮最小面积
void set_blaskSkin_min_area(int _v)
{
	blaskSkin_min_area = _v;
}

/*-----------------------------------*/

//设hough点数阈值
void set_hough_thresold(int _v)
{
	hough_thresold = _v;
}

/*-----------------------------------*/

//设hough最小线段长度*100
void set_hough_min_length(int _v)
{
	hough_min_length = _v;
}

/*-----------------------------------*/

//设hough最大线段间距*100
void set_hough_max_gap(int _v)
{
	hough_max_gap = _v;
}

/*-----------------------------------*/

//设hough最大角度*100
void set_hough_max_angle(int _v)
{
	hough_max_angle = _v;
}

/*-----------------------------------*/

//设裂纹最小面积
void set_crack_min_area(int _v)
{
	crack_min_area = _v;
}

/*-----------------------------------*/

//设裂纹长宽比*100
void set_crack_aspect_ratio(int _v)
{
	crack_aspect_ratio = _v;
}

/*-----------------------------------*/

//设裂纹面积比*100
void set_crack_area_ratio(int _v)
{
	crack_area_ratio = _v;
}

/*-----------------------------------*/

//设最终的检测结果
void set_last_detect_result(enum DetectResult _v)
{
	last_detect_result = _v;
}

/*-----------------------------------*/

//查最终的检测结果
enum DetectResult get_last_detect_result()
{
	return last_detect_result;
}

/*-----------------------------------*/

//一轮检测的已检测蒙板图片个数自增加1
void inc_processed_cnt()
{
	processed_cnt++;
}

/*-----------------------------------*/

//获取 一轮检测的已检测蒙板图片个数
int get_processed_cnt()
{
	return processed_cnt;
}

/*-----------------------------------*/

//一轮检测的蒙板图片总数
int get_number_of_mask()
{
	return number_of_mask;
}

//一轮检测开始时，部分变量初始化
void img_proc_init(int _v)
{
	number_of_mask = _v;  //一轮检测的蒙板图片总数，用于后期图片合成
	last_detect_result = QUALIFIED;  //最终的检测结果
	processed_cnt = 0;  //一轮检测的已检测蒙板图片个数，用于后期图片合成
}

//##
//查找黑皮
IplImage* ImgProcessIpl_BlackSkin(IplImage* _img, int* _posFlag)
{
	const CvRect rect = cvGetImageROI(_img);  //获取图像的ROI坐标；如果没有ROI，则返回矩形值(cvRect(0,0,image->width,image->height))
	cvResetImageROI(_img);  //释放图像image中被设定的感兴趣区域ROI

	IplImage* resImg = cvCreateImage(cvGetSize(_img), IPL_DEPTH_8U, 1);
	cvSetZero(resImg);

	//查找黑皮
	if (get_is_blackSkin()) {

		const float Scale = 1.0F / 10.0F;
		const unsigned int num_all = _img->width*_img->height;
		const unsigned int num_255 = ImgProc_PixelNumber_Gray(_img, 255);  //计算白点数 即计算异常点数目
		if (num_255 > num_all * Scale) {
			 //如果异常点数目占图像的比重大于0.1
			 //则跳过hough

			(*_posFlag)++;

			const float threshold = 254.5;
			const float max_value = 255;
			const int threshold_type = CV_THRESH_BINARY;
			cvThreshold(_img, resImg, threshold, max_value, threshold_type);  //二值化 如果大于阈值则为max_vslue，否则为0
		}
		else
		{
			//二值化
			const float threshold = 254.5;
			const float max_value = 255;
			const int threshold_type = CV_THRESH_BINARY;
			cvThreshold(_img, resImg, threshold, max_value, threshold_type);  //二值化 如果大于阈值则为max_vslue，否则为0

//			//去噪
//			Binary2Smooth_Line(resImg);

			//找轮廓
			int mMode = CV_RETR_EXTERNAL;   //寻找轮廓的模式
			int mMethod = CV_CHAIN_APPROX_NONE;  //寻找轮廓的方法
			CvScalar mHoleColor = cvScalar(255, 255, 255, 255);  //外围轮廓颜色
			CvSeq * m_pContourHeader;  //提取轮廓的序列指针
			CvMemStorage * mStorage = cvCreateMemStorage(0);  //提取轮廓需要的储存容量 0为默认64KB
			cvFindContours(resImg, mStorage, &m_pContourHeader, sizeof(CvContour), mMode, mMethod);  //从二值图像中检索轮廓  参数意义分别为：原二值图、内存存储器、轮廓指针、轮廓字节数、mMode = CV_RETR_EXTERNAL（只提取外轮廓）、 mMethod = CV_CHAIN_APPROX_NONE（将所有点由链码形式转化为点序列形式）;

			//test cvFindContours(_img, mStorage, &m_pContourHeader, sizeof(CvContour), mMode, mMethod);  //从二值图像中检索轮廓  参数意义分别为：原二值图、内存存储器、轮廓指针、轮廓字节数、mMode = CV_RETR_EXTERNAL（只提取外轮廓）、 mMethod = CV_CHAIN_APPROX_NONE（将所有点由链码形式转化为点序列形式）;

			//画轮廓+填充轮廓
			CvSeq * pContour_t = m_pContourHeader;  //提取轮廓的序列指针
			const int max_level = 0; //绘制轮廓及在其后的相同的级别下轮廓
			const int thickness = -1;  //线的宽度  -1为内部填充
			int blackSkinArea = get_blaskSkin_min_area();

			cvSetZero(resImg);
			for (; pContour_t != 0; pContour_t = pContour_t->h_next)
			{
				if (CV_IS_SEQ_CLOSED(pContour_t) && cvContourArea(pContour_t) > blackSkinArea) {

					cvDrawContours(resImg, pContour_t, mHoleColor, mHoleColor, max_level, thickness);  //opencv函数 绘制所有轮廓  参数意义分别为原图、轮廓指针、外轮廓颜色、内轮廓颜色、轮廓绘制等级、线条粗细
					(*_posFlag)++;

				}
			}

			cvReleaseMemStorage(&mStorage);
		}
	}

	cvSetImageROI(_img, rect);   //设定ROI
	cvSetImageROI(resImg, rect);   //设定ROI

	return resImg;
}

/*-------------------------------------*/

//图像去噪
void Binary2Smooth_Line(IplImage * _img)
{
	uchar* const ImgData = (uchar *)_img->imageData;
	const int STEP = _img->widthStep / sizeof(uchar);
	const int Width = _img->width;
	const int Height = _img->height;
	const int border_size = 1;
	const int border_w_min = border_size;
	const int border_h_min = 0;
	//const int border_w_max = Width - border_size - 1;
	//const int border_h_max = Height;

#if 1

	const unsigned int WidthB = Width;
	const unsigned int HeightB = Height - border_size;

	const int x_offset[] = { -1,1};
	const int y_offset[] = {0,0 };
	const int SIEZ_OFFSET = sizeof(x_offset) / sizeof(int);
	for (size_t wi = border_w_min; wi <WidthB; wi++)
	{
		for (size_t hi = border_h_min; hi <HeightB; hi++)
		{
			int img_data = ImgData[wi + hi*STEP];
			if (img_data == 255)
			{
				int isPoint = 0;
				for (size_t gi = 0; gi < SIEZ_OFFSET ; gi++)
				{
					int gwi = wi + x_offset[gi];
					int ghi = hi + y_offset[gi];
					int img_data_g = ImgData[gwi + ghi*STEP];
					if (img_data_g == 255) {
						isPoint++;
						break;
					}
				}

				if (isPoint == 0) {
					ImgData[wi + hi*STEP] = 0;
				}
			}

		}

	}

#endif
}

/*-----------------------------------------*/

//二值化+去噪
void ImgProcessIpl_Base(IplImage * _img)
{
	const CvRect rect = cvGetImageROI(_img);  //获取图像的ROI坐标；如果没有ROI，则返回矩形值(cvRect(0,0,image->width,image->height))
	cvResetImageROI(_img);  //释放图像image中被设定的感兴趣区域ROI

	//二值化
	if (get_is_binary()) {

#if 0
		const float threshold = 0.5;
		const float max_value = 255;
		const int threshold_type = CV_THRESH_BINARY;
		IplImage * erImg1 = cvCreateImage(cvGetSize(_img), IPL_DEPTH_8U, 1);
		cvThreshold(_img, erImg1, threshold, max_value, threshold_type);  //二值化 如果大于0.5则为max_value，否则为0

		//##
		const float threshold2 = 224.5;
		IplImage * erImg2 = cvCreateImage(cvGetSize(_img), IPL_DEPTH_8U, 1);
		cvThreshold(_img, erImg2, threshold2, max_value, threshold_type);  //二值化 如果大于224.5则为max_value，否则为0

		cvAbsDiff(erImg1, erImg2, _img);

		//##
		cvReleaseImage(&erImg1);
		cvReleaseImage(&erImg2);
#else
		const float threshold = 224.5;
		const float max_value = 255;
		const int threshold_type = CV_THRESH_TOZERO_INV;
		cvThreshold(_img, _img, threshold, max_value, threshold_type);  //二值化 如果大于224.5则为0，否则为src

		const float threshold2 = 0.5;
		const int threshold_type2 = CV_THRESH_BINARY;
		cvThreshold(_img, _img, threshold2, max_value, threshold_type2);  //二值化 如果大于0.5则为max_value，否则为0

#endif

	}

	//去噪
	if (get_is_denoise()) {
		Binary2Smooth_Line(_img);
	}

	cvSetImageROI(_img, rect);   //设定ROI
}

/*-------------------------------------*/

//根据相应参数对图像进行相应处理  计算二值化后异常点占总图像的比重  或者  进行hogh变换并寻找相应椭圆
void ImgProcessIpl(IplImage * _img,int* _posFlag)
{
	const CvRect rect = cvGetImageROI(_img);
	cvResetImageROI(_img);

	if (get_is_hough())
	{
		const float Scale = 1.0F / 10.0F;
		const unsigned int num_all = _img->width*_img->height;
		const unsigned int num_255 = ImgProc_PixelNumber_Gray(_img, 255);  //计算白点数 即计算异常点数目
		if (num_255 > num_all * Scale) {
			 //如果异常点数目占图像的比重大于0.1
			 //则跳过hough

			(*_posFlag)++;
		}
		else
		{   //如果异常点数目占图像的比重小于0.1
			const int hough_thickness = 3;
			const CvScalar hough_color = CV_RGB(255, 255, 255);
			std::vector<Line2Point> lines_t;

			int mLineTh = get_hough_thresold();
			double mLineLenMin = get_hough_min_length()/100.0;
			double mLineGap = get_hough_max_gap()/100.0;
			double mRemoveDegree = 90.0 - get_hough_max_gap()/100.0;

			// hough变换
			//调用opencv函数进行hough变换 + 删除角度在90度附近的直线  结果图为_img
			lines_t = getHoughLinesBase(
				_img,
				_img,
				hough_color,
				hough_thickness,
				mRemoveDegree,
				mLineTh,
				mLineLenMin,
				mLineGap);
		}
	}

	if (get_is_morphology())
	{
		const float Scale = 1.0F / 10.0F;
		const unsigned int num_all = _img->width*_img->height;
		const unsigned int num_255 = ImgProc_PixelNumber_Gray(_img, 255);  //计算白点数 即计算异常点数目
		if (num_255 > num_all * Scale) {  //如果异常点数目占图像的比重大于0.1  ？？******
			//如果异常点数目占图像的比重大于0.1
			//跳过形态学分析

			(*_posFlag)++;
		}
		else
		{
			CvMemStorage * mStorage = cvCreateMemStorage(0);
			CvSeq * m_pContourHeader;
			int mMode = CV_RETR_EXTERNAL;   //寻找轮廓的模式
			int mMethod = CV_CHAIN_APPROX_NONE;  //寻找轮廓的方法
			cvFindContours(_img, mStorage, &m_pContourHeader, sizeof(CvContour), mMode, mMethod);  //从二值图像中检索轮廓  参数意义分别为：原二值图、内存存储器、轮廓指针、轮廓字节数、mMode = CV_RETR_EXTERNAL（只提取外轮廓）、 mMethod = CV_CHAIN_APPROX_NONE（将所有点由链码形式转化为点序列形式）;

			CvSeq * pContour_t = m_pContourHeader;  //提取轮廓的序列指针
			const int max_level = 0; //绘制轮廓及在其后的相同的级别下轮廓
			CvScalar mExternalColor = cvScalar(255, 255, 255, 255);  //内围轮廓颜色

			int minArea = get_crack_min_area();
			double wh = get_crack_aspect_ratio()/100.0;
			double ar = get_crack_area_ratio()/100.0;

			cvSetZero(_img);

			for (; pContour_t != 0; pContour_t = pContour_t->h_next)
			{
				float area_t = cvContourArea(pContour_t);
				CvBox2D mBox = cvMinAreaRect2(pContour_t);  //对给定的 2D 点集，寻找最小面积的包围矩形
				float boxArea = mBox.size.height*mBox.size.width;

				if (area_t < minArea)
					continue;

				if ((std::fabs(mBox.size.height-mBox.size.width)) / std::max(mBox.size.height, mBox.size.width) > wh)
				{
					cvDrawContours(_img, pContour_t, mExternalColor, mExternalColor, max_level, -1);  //opencv函数 绘制所有轮廓  参数意义分别为原图、轮廓指针、外轮廓颜色、内轮廓颜色、轮廓绘制等级、线条粗细

					(*_posFlag)++;

					continue;
				}

				if ((boxArea - area_t) / boxArea > ar)
				{
					cvDrawContours(_img, pContour_t, mExternalColor, mExternalColor, max_level, -1);  //opencv函数 绘制所有轮廓  参数意义分别为原图、轮廓指针、外轮廓颜色、内轮廓颜色、轮廓绘制等级、线条粗细

					(*_posFlag)++;

					continue;
				}
			}

			cvReleaseMemStorage(&mStorage);
		}
	}

	cvSetImageROI(_img, rect);
}

/*-------------------------------------*/

//计算白点数 即计算异常点数目
unsigned int ImgProc_PixelNumber_Gray(IplImage * _img, int _p)
{
	const int WIDTH = _img->width;
	const int HEIGHT = _img->height;
	unsigned int sum = 0;

	assert(_img->nChannels == 1);

	for (int i = 0; i <HEIGHT; i++){
		for (int j = 0; j <WIDTH; j++){

			unsigned char pixel =_img->imageData [ i*_img->widthStep + j];
			if (pixel==_p){
				sum++;
			}

		}
	}

	return sum;
}

/*-------------------------------------*/

//调用opencv函数进行hough变换 + 删除角度在90度附近的直线
std::vector<Line2Point> getHoughLinesBase(IplImage * _img_bin,
		IplImage * _img_draw,
		CvScalar _color,
		int _thickness,
		const double _remove_degree,
		const int _line_th,
		const double _line_len_min,
		const double _line_gap)
{
	//调用opencv函数 进行hough变换 返回hough直线的起点与终点
	std::vector<Line2Point> lines_t = Hough_Line_CV_PROBABILISTIC_GetLine(_img_bin,
																				1,
																		CV_PI / 180,
																		_line_th,
																		_line_len_min,
																		_line_gap);

	//计算直线角度并保存
	LineCalAngle(lines_t);

	std::vector<Line2Point> lines_remove0_t = LineRemove(lines_t, 90, _remove_degree);  //删除[90-d,90+d]和[-90-d,-90+d]的直线
	//std::vector<Line2Point> lines_remove1_t = LineRemove(lines_remove0_t, -90, _remove_degree);  //删除[-90-d,-90+d]的直线

	if (_img_bin == _img_draw) {
		cvSetZero(_img_draw);   //获取与_img_bin同样大小的全黑图
	}

	if (_img_draw != NULL) {
		LineDraw(lines_remove0_t, _img_draw, _color, _thickness);  //在图上画出符合条件的直线
	}

	return lines_remove0_t;
}

/*-------------------------------------*/

//调用opencv函数 进行hough变换 返回hough直线的起点与重点
std::vector<Line2Point> Hough_Line_CV_PROBABILISTIC_GetLine(
	CvArr * image,
	double rho,
	double theta,
	int threshold,
	double _lineLenMin,
	double _lineGap)
{
	std::vector<Line2Point> line_t;
	CvMemStorage *storage = cvCreateMemStorage();  //用来创建一个内存存储器，来统一管理各种动态对象的内存 用于储存直线
	CvSeq *lines = 0;
	lines = cvHoughLines2(image, storage, CV_HOUGH_PROBABILISTIC, rho, theta, threshold, _lineLenMin, _lineGap);  //opencv函数-（概率）hough变换  倒数5个参数意义分别为像素点精度、单位角度、直线上最大像素点数、最小线段长度、最大线段距离

	for (int i = 0; i<lines->total; i++)
	{
		CvPoint *line = (CvPoint *)cvGetSeqElem(lines, i);

		line_t.push_back(Line2Point(line[0], line[1]));  //记录每条线的起点与终点
	}

	cvReleaseMemStorage(&storage);  //释放内存

	return line_t;

}

/*----------------------------------------------------------------*/

//删除直线角度符合条件的直线   保存直线角度符合条件的直线
std::vector<Line2Point> LineRemove(
					std::vector<Line2Point>&  _lines,
					double _theta_c,
					double _theta_r)
{
	std::vector<Line2Point> lines_t;

	double theta_min1 = _theta_c - _theta_r;  //90-r或-90-r
	double theta_max1= _theta_c + _theta_r;  //90+r或9-0+r
	double theta_min2 = (-1)*_theta_c - _theta_r;  //90-r或-90-r
	double theta_max2 = (-1)*_theta_c + _theta_r;  //90+r或9-0+r

	for (unsigned int i = 0; i < _lines.size();i++)
	{
		Line2Point line_t = _lines[i];
		double theta_d = line_t.mTheta_d;

		if ((theta_d>theta_min1 && theta_d<theta_max1) || (theta_d>theta_min2 && theta_d<theta_max2)) {

		}
		else
		{
			lines_t.push_back(line_t);   //保存符合条件的直线
		}

	}

	return lines_t;
}

/*----------------------------------------------------------------*/

//计算直线的角度
void LineCalAngle(std::vector<Line2Point>& _lines)
{
	for (int i = 0; i < (int)_lines.size();i++)
	{
		Line2Point line_t = _lines[i];
		line_t.CalTheta();
	}
}

/*----------------------------------------------------------------*/

//在图上画直线
void LineDraw(std::vector<Line2Point>& _lines,
	IplImage * img_t,
	CvScalar _color,
	int _thickness)
{
	for (unsigned int i = 0; i < _lines.size();i++)
	{
		Line2Point line_t = _lines[i];
		cvLine(img_t,line_t.mP1,line_t.mP2,_color, _thickness);
	}

}

/*----------------------------------------------------------------*/

//结果判定 （结果默认为合格）
void ImgProcessIpl_PredictResult(const int posFlag)
{
	if(get_is_blackSkin() || get_is_morphology())
	{
		if(posFlag > 0)
		{
			set_last_detect_result(UNQUALIFIED);
		}
	}
	else
	{
		set_last_detect_result(UNKNOWN);
	}

}

/*----------------------------------------------------------------*/

//判定结果展示
void ImgProcessIpl_ShowResult(IplImage* _img)
{
	if(get_last_detect_result() == QUALIFIED)
	{
		cvCircle(_img,cvPoint(_img->width-100,_img->height-100), 50,CV_RGB(255,255,255),3);
	}
	else if(get_last_detect_result() == UNQUALIFIED)
	{
		cvLine(_img,cvPoint(_img->width,_img->height),cvPoint(_img->width-150,_img->height-150),CV_RGB(255,255,255),3);
		cvLine(_img,cvPoint(_img->width,_img->height-150),cvPoint(_img->width-150,_img->height),CV_RGB(255,255,255),3);
	}
	else
	{
		cvRectangle(_img, cvPoint(_img->width-10, _img->height-10), cvPoint(_img->width-150, _img->height-150), cvScalar(255, 255, 255), 3, 4, 0 );
	}
}
