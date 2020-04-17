/*
 * img_proc.c
 *
 *  Created on: 2020��4��10��
 *      Author: yjkj909
 */

#include "img_proc.h"

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

static int is_binary = FALSE;  //��ֵ��
static int is_denoise = FALSE;  //ȥ��
static int is_blackSkin = FALSE;  //��Ƥ
static int is_hough = FALSE;  //hough
static int is_morphology = FALSE;  //��̬ѧ
static int is_showResult = FALSE;  //���չʾ

static int blaskSkin_min_area = 0;  //��Ƥ��С���
static int hough_thresold = 0;  //hough������ֵ
static int hough_min_length = 0;  //hough��С�߶γ���*100
static int hough_max_gap = 0;  //hough����߶μ��*100
static int hough_max_angle = 0;  //hough���Ƕ�*100
static int crack_min_area = 0;  //������С���
static int crack_aspect_ratio = 0;  //���Ƴ����*100
static int crack_area_ratio = 0;  //���������*100

static int number_of_mask = 0;  //һ�ּ����ɰ�ͼƬ���������ں���ͼƬ�ϳ�
static int processed_cnt = 0;   //һ�ּ����Ѽ���ɰ�ͼƬ���������ں���ͼƬ�ϳ�
static enum DetectResult last_detect_result = QUALIFIED;  //���յļ����

/*-----------------------------------*/

//��ȡ�Ƿ��ֵ��
int get_is_binary()
{
	return is_binary;
}

/*-----------------------------------*/

//��ȡ�Ƿ�ȥ��
int get_is_denoise()
{
	return is_denoise;
}

/*-----------------------------------*/

//��ȡ�Ƿ��Ƥ
int get_is_blackSkin()
{
	return is_blackSkin;
}

/*-----------------------------------*/

//��ȡ�Ƿ�hough
int get_is_hough()
{
	return is_hough;
}

/*-----------------------------------*/

//��ȡ�Ƿ���̬ѧ
int get_is_morphology()
{
	return is_morphology;
}

/*-----------------------------------*/

//��ȡ�Ƿ���չʾ
int get_is_showResult()
{
	return is_showResult;
}

/*-----------------------------------*/

//��ȡ��Ƥ��С���
int get_blaskSkin_min_area()
{
	return blaskSkin_min_area;
}

/*-----------------------------------*/

//��ȡ������ֵ
int get_hough_thresold()
{
	return hough_thresold;
}

/*-----------------------------------*/

//��ȡhough��С�߶γ���*100
int get_hough_min_length()
{
	return hough_min_length;
}

/*-----------------------------------*/

//��ȡhough����߶μ��*100
int get_hough_max_gap()
{
	return hough_max_gap;
}

/*-----------------------------------*/

//��ȡhough���Ƕ�*100
int get_hough_max_angle()
{
	return hough_max_angle;
}

/*-----------------------------------*/

//��ȡ������С���
int get_crack_min_area()
{
	return crack_min_area;
}

/*-----------------------------------*/

//��ȡ���Ƴ����*100
int get_crack_aspect_ratio()
{
	return crack_aspect_ratio;
}

/*-----------------------------------*/

//��ȡ���������*100
int get_crack_area_ratio()
{
	return crack_area_ratio;
}

/*-----------------------------------*/

//���Ƿ��ֵ��
void set_is_binary(int _v)
{
	is_binary = _v;
}

/*-----------------------------------*/

//���Ƿ�ȥ��
void set_is_denoise(int _v)
{
	is_denoise = _v;
}

/*-----------------------------------*/

//���Ƿ��Ƥ���
void set_is_blackSkin(int _v)
{
	is_blackSkin = _v;
}

/*-----------------------------------*/

//���Ƿ�hough
void set_is_hough(int _v)
{
	is_hough = _v;
}

/*-----------------------------------*/

//���Ƿ���̬ѧ
void set_is_morphology(int _v)
{
	is_morphology =_v;
}

/*-----------------------------------*/

//���Ƿ���̬ѧ
void set_is_showResult(int _v)
{
	is_showResult = _v;
}

/*-----------------------------------*/

//���Ƥ��С���
void set_blaskSkin_min_area(int _v)
{
	blaskSkin_min_area = _v;
}

/*-----------------------------------*/

//��hough������ֵ
void set_hough_thresold(int _v)
{
	hough_thresold = _v;
}

/*-----------------------------------*/

//��hough��С�߶γ���*100
void set_hough_min_length(int _v)
{
	hough_min_length = _v;
}

/*-----------------------------------*/

//��hough����߶μ��*100
void set_hough_max_gap(int _v)
{
	hough_max_gap = _v;
}

/*-----------------------------------*/

//��hough���Ƕ�*100
void set_hough_max_angle(int _v)
{
	hough_max_angle = _v;
}

/*-----------------------------------*/

//��������С���
void set_crack_min_area(int _v)
{
	crack_min_area = _v;
}

/*-----------------------------------*/

//�����Ƴ����*100
void set_crack_aspect_ratio(int _v)
{
	crack_aspect_ratio = _v;
}

/*-----------------------------------*/

//�����������*100
void set_crack_area_ratio(int _v)
{
	crack_area_ratio = _v;
}

/*-----------------------------------*/

//�����յļ����
void set_last_detect_result(enum DetectResult _v)
{
	last_detect_result = _v;
}

/*-----------------------------------*/

//�����յļ����
enum DetectResult get_last_detect_result()
{
	return last_detect_result;
}

/*-----------------------------------*/

//һ�ּ����Ѽ���ɰ�ͼƬ����������1
void inc_processed_cnt()
{
	processed_cnt++;
}

/*-----------------------------------*/

//��ȡ һ�ּ����Ѽ���ɰ�ͼƬ����
int get_processed_cnt()
{
	return processed_cnt;
}

/*-----------------------------------*/

//һ�ּ����ɰ�ͼƬ����
int get_number_of_mask()
{
	return number_of_mask;
}

//һ�ּ�⿪ʼʱ�����ֱ�����ʼ��
void img_proc_init(int _v)
{
	number_of_mask = _v;  //һ�ּ����ɰ�ͼƬ���������ں���ͼƬ�ϳ�
	last_detect_result = QUALIFIED;  //���յļ����
	processed_cnt = 0;  //һ�ּ����Ѽ���ɰ�ͼƬ���������ں���ͼƬ�ϳ�
}

//##
//���Һ�Ƥ
IplImage* ImgProcessIpl_BlackSkin(IplImage* _img, int* _posFlag)
{
	const CvRect rect = cvGetImageROI(_img);  //��ȡͼ���ROI���ꣻ���û��ROI���򷵻ؾ���ֵ(cvRect(0,0,image->width,image->height))
	cvResetImageROI(_img);  //�ͷ�ͼ��image�б��趨�ĸ���Ȥ����ROI

	IplImage* resImg = cvCreateImage(cvGetSize(_img), IPL_DEPTH_8U, 1);
	cvSetZero(resImg);

	//���Һ�Ƥ
	if (get_is_blackSkin()) {

		const float Scale = 1.0F / 10.0F;
		const unsigned int num_all = _img->width*_img->height;
		const unsigned int num_255 = ImgProc_PixelNumber_Gray(_img, 255);  //����׵��� �������쳣����Ŀ
		if (num_255 > num_all * Scale) {
			 //����쳣����Ŀռͼ��ı��ش���0.1
			 //������hough

			(*_posFlag)++;

			const float threshold = 254.5;
			const float max_value = 255;
			const int threshold_type = CV_THRESH_BINARY;
			cvThreshold(_img, resImg, threshold, max_value, threshold_type);  //��ֵ�� ���������ֵ��Ϊmax_vslue������Ϊ0
		}
		else
		{
			//��ֵ��
			const float threshold = 254.5;
			const float max_value = 255;
			const int threshold_type = CV_THRESH_BINARY;
			cvThreshold(_img, resImg, threshold, max_value, threshold_type);  //��ֵ�� ���������ֵ��Ϊmax_vslue������Ϊ0

//			//ȥ��
//			Binary2Smooth_Line(resImg);

			//������
			int mMode = CV_RETR_EXTERNAL;   //Ѱ��������ģʽ
			int mMethod = CV_CHAIN_APPROX_NONE;  //Ѱ�������ķ���
			CvScalar mHoleColor = cvScalar(255, 255, 255, 255);  //��Χ������ɫ
			CvSeq * m_pContourHeader;  //��ȡ����������ָ��
			CvMemStorage * mStorage = cvCreateMemStorage(0);  //��ȡ������Ҫ�Ĵ������� 0ΪĬ��64KB
			cvFindContours(resImg, mStorage, &m_pContourHeader, sizeof(CvContour), mMode, mMethod);  //�Ӷ�ֵͼ���м�������  ��������ֱ�Ϊ��ԭ��ֵͼ���ڴ�洢��������ָ�롢�����ֽ�����mMode = CV_RETR_EXTERNAL��ֻ��ȡ���������� mMethod = CV_CHAIN_APPROX_NONE�������е���������ʽת��Ϊ��������ʽ��;

			//test cvFindContours(_img, mStorage, &m_pContourHeader, sizeof(CvContour), mMode, mMethod);  //�Ӷ�ֵͼ���м�������  ��������ֱ�Ϊ��ԭ��ֵͼ���ڴ�洢��������ָ�롢�����ֽ�����mMode = CV_RETR_EXTERNAL��ֻ��ȡ���������� mMethod = CV_CHAIN_APPROX_NONE�������е���������ʽת��Ϊ��������ʽ��;

			//������+�������
			CvSeq * pContour_t = m_pContourHeader;  //��ȡ����������ָ��
			const int max_level = 0; //������������������ͬ�ļ���������
			const int thickness = -1;  //�ߵĿ��  -1Ϊ�ڲ����
			int blackSkinArea = get_blaskSkin_min_area();

			cvSetZero(resImg);
			for (; pContour_t != 0; pContour_t = pContour_t->h_next)
			{
				if (CV_IS_SEQ_CLOSED(pContour_t) && cvContourArea(pContour_t) > blackSkinArea) {

					cvDrawContours(resImg, pContour_t, mHoleColor, mHoleColor, max_level, thickness);  //opencv���� ������������  ��������ֱ�Ϊԭͼ������ָ�롢��������ɫ����������ɫ���������Ƶȼ���������ϸ
					(*_posFlag)++;

				}
			}

			cvReleaseMemStorage(&mStorage);
		}
	}

	cvSetImageROI(_img, rect);   //�趨ROI
	cvSetImageROI(resImg, rect);   //�趨ROI

	return resImg;
}

/*-------------------------------------*/

//ͼ��ȥ��
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

//��ֵ��+ȥ��
void ImgProcessIpl_Base(IplImage * _img)
{
	const CvRect rect = cvGetImageROI(_img);  //��ȡͼ���ROI���ꣻ���û��ROI���򷵻ؾ���ֵ(cvRect(0,0,image->width,image->height))
	cvResetImageROI(_img);  //�ͷ�ͼ��image�б��趨�ĸ���Ȥ����ROI

	//��ֵ��
	if (get_is_binary()) {

#if 0
		const float threshold = 0.5;
		const float max_value = 255;
		const int threshold_type = CV_THRESH_BINARY;
		IplImage * erImg1 = cvCreateImage(cvGetSize(_img), IPL_DEPTH_8U, 1);
		cvThreshold(_img, erImg1, threshold, max_value, threshold_type);  //��ֵ�� �������0.5��Ϊmax_value������Ϊ0

		//##
		const float threshold2 = 224.5;
		IplImage * erImg2 = cvCreateImage(cvGetSize(_img), IPL_DEPTH_8U, 1);
		cvThreshold(_img, erImg2, threshold2, max_value, threshold_type);  //��ֵ�� �������224.5��Ϊmax_value������Ϊ0

		cvAbsDiff(erImg1, erImg2, _img);

		//##
		cvReleaseImage(&erImg1);
		cvReleaseImage(&erImg2);
#else
		const float threshold = 224.5;
		const float max_value = 255;
		const int threshold_type = CV_THRESH_TOZERO_INV;
		cvThreshold(_img, _img, threshold, max_value, threshold_type);  //��ֵ�� �������224.5��Ϊ0������Ϊsrc

		const float threshold2 = 0.5;
		const int threshold_type2 = CV_THRESH_BINARY;
		cvThreshold(_img, _img, threshold2, max_value, threshold_type2);  //��ֵ�� �������0.5��Ϊmax_value������Ϊ0

#endif

	}

	//ȥ��
	if (get_is_denoise()) {
		Binary2Smooth_Line(_img);
	}

	cvSetImageROI(_img, rect);   //�趨ROI
}

/*-------------------------------------*/

//������Ӧ������ͼ�������Ӧ����  �����ֵ�����쳣��ռ��ͼ��ı���  ����  ����hogh�任��Ѱ����Ӧ��Բ
void ImgProcessIpl(IplImage * _img,int* _posFlag)
{
	const CvRect rect = cvGetImageROI(_img);
	cvResetImageROI(_img);

	if (get_is_hough())
	{
		const float Scale = 1.0F / 10.0F;
		const unsigned int num_all = _img->width*_img->height;
		const unsigned int num_255 = ImgProc_PixelNumber_Gray(_img, 255);  //����׵��� �������쳣����Ŀ
		if (num_255 > num_all * Scale) {
			 //����쳣����Ŀռͼ��ı��ش���0.1
			 //������hough

			(*_posFlag)++;
		}
		else
		{   //����쳣����Ŀռͼ��ı���С��0.1
			const int hough_thickness = 3;
			const CvScalar hough_color = CV_RGB(255, 255, 255);
			std::vector<Line2Point> lines_t;

			int mLineTh = get_hough_thresold();
			double mLineLenMin = get_hough_min_length()/100.0;
			double mLineGap = get_hough_max_gap()/100.0;
			double mRemoveDegree = 90.0 - get_hough_max_gap()/100.0;

			// hough�任
			//����opencv��������hough�任 + ɾ���Ƕ���90�ȸ�����ֱ��  ���ͼΪ_img
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
		const unsigned int num_255 = ImgProc_PixelNumber_Gray(_img, 255);  //����׵��� �������쳣����Ŀ
		if (num_255 > num_all * Scale) {  //����쳣����Ŀռͼ��ı��ش���0.1  ����******
			//����쳣����Ŀռͼ��ı��ش���0.1
			//������̬ѧ����

			(*_posFlag)++;
		}
		else
		{
			CvMemStorage * mStorage = cvCreateMemStorage(0);
			CvSeq * m_pContourHeader;
			int mMode = CV_RETR_EXTERNAL;   //Ѱ��������ģʽ
			int mMethod = CV_CHAIN_APPROX_NONE;  //Ѱ�������ķ���
			cvFindContours(_img, mStorage, &m_pContourHeader, sizeof(CvContour), mMode, mMethod);  //�Ӷ�ֵͼ���м�������  ��������ֱ�Ϊ��ԭ��ֵͼ���ڴ�洢��������ָ�롢�����ֽ�����mMode = CV_RETR_EXTERNAL��ֻ��ȡ���������� mMethod = CV_CHAIN_APPROX_NONE�������е���������ʽת��Ϊ��������ʽ��;

			CvSeq * pContour_t = m_pContourHeader;  //��ȡ����������ָ��
			const int max_level = 0; //������������������ͬ�ļ���������
			CvScalar mExternalColor = cvScalar(255, 255, 255, 255);  //��Χ������ɫ

			int minArea = get_crack_min_area();
			double wh = get_crack_aspect_ratio()/100.0;
			double ar = get_crack_area_ratio()/100.0;

			cvSetZero(_img);

			for (; pContour_t != 0; pContour_t = pContour_t->h_next)
			{
				float area_t = cvContourArea(pContour_t);
				CvBox2D mBox = cvMinAreaRect2(pContour_t);  //�Ը����� 2D �㼯��Ѱ����С����İ�Χ����
				float boxArea = mBox.size.height*mBox.size.width;

				if (area_t < minArea)
					continue;

				if ((std::fabs(mBox.size.height-mBox.size.width)) / std::max(mBox.size.height, mBox.size.width) > wh)
				{
					cvDrawContours(_img, pContour_t, mExternalColor, mExternalColor, max_level, -1);  //opencv���� ������������  ��������ֱ�Ϊԭͼ������ָ�롢��������ɫ����������ɫ���������Ƶȼ���������ϸ

					(*_posFlag)++;

					continue;
				}

				if ((boxArea - area_t) / boxArea > ar)
				{
					cvDrawContours(_img, pContour_t, mExternalColor, mExternalColor, max_level, -1);  //opencv���� ������������  ��������ֱ�Ϊԭͼ������ָ�롢��������ɫ����������ɫ���������Ƶȼ���������ϸ

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

//����׵��� �������쳣����Ŀ
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

//����opencv��������hough�任 + ɾ���Ƕ���90�ȸ�����ֱ��
std::vector<Line2Point> getHoughLinesBase(IplImage * _img_bin,
		IplImage * _img_draw,
		CvScalar _color,
		int _thickness,
		const double _remove_degree,
		const int _line_th,
		const double _line_len_min,
		const double _line_gap)
{
	//����opencv���� ����hough�任 ����houghֱ�ߵ�������յ�
	std::vector<Line2Point> lines_t = Hough_Line_CV_PROBABILISTIC_GetLine(_img_bin,
																				1,
																		CV_PI / 180,
																		_line_th,
																		_line_len_min,
																		_line_gap);

	//����ֱ�߽ǶȲ�����
	LineCalAngle(lines_t);

	std::vector<Line2Point> lines_remove0_t = LineRemove(lines_t, 90, _remove_degree);  //ɾ��[90-d,90+d]��[-90-d,-90+d]��ֱ��
	//std::vector<Line2Point> lines_remove1_t = LineRemove(lines_remove0_t, -90, _remove_degree);  //ɾ��[-90-d,-90+d]��ֱ��

	if (_img_bin == _img_draw) {
		cvSetZero(_img_draw);   //��ȡ��_img_binͬ����С��ȫ��ͼ
	}

	if (_img_draw != NULL) {
		LineDraw(lines_remove0_t, _img_draw, _color, _thickness);  //��ͼ�ϻ�������������ֱ��
	}

	return lines_remove0_t;
}

/*-------------------------------------*/

//����opencv���� ����hough�任 ����houghֱ�ߵ�������ص�
std::vector<Line2Point> Hough_Line_CV_PROBABILISTIC_GetLine(
	CvArr * image,
	double rho,
	double theta,
	int threshold,
	double _lineLenMin,
	double _lineGap)
{
	std::vector<Line2Point> line_t;
	CvMemStorage *storage = cvCreateMemStorage();  //��������һ���ڴ�洢������ͳһ������ֶ�̬������ڴ� ���ڴ���ֱ��
	CvSeq *lines = 0;
	lines = cvHoughLines2(image, storage, CV_HOUGH_PROBABILISTIC, rho, theta, threshold, _lineLenMin, _lineGap);  //opencv����-�����ʣ�hough�任  ����5����������ֱ�Ϊ���ص㾫�ȡ���λ�Ƕȡ�ֱ����������ص�������С�߶γ��ȡ�����߶ξ���

	for (int i = 0; i<lines->total; i++)
	{
		CvPoint *line = (CvPoint *)cvGetSeqElem(lines, i);

		line_t.push_back(Line2Point(line[0], line[1]));  //��¼ÿ���ߵ�������յ�
	}

	cvReleaseMemStorage(&storage);  //�ͷ��ڴ�

	return line_t;

}

/*----------------------------------------------------------------*/

//ɾ��ֱ�߽Ƕȷ���������ֱ��   ����ֱ�߽Ƕȷ���������ֱ��
std::vector<Line2Point> LineRemove(
					std::vector<Line2Point>&  _lines,
					double _theta_c,
					double _theta_r)
{
	std::vector<Line2Point> lines_t;

	double theta_min1 = _theta_c - _theta_r;  //90-r��-90-r
	double theta_max1= _theta_c + _theta_r;  //90+r��9-0+r
	double theta_min2 = (-1)*_theta_c - _theta_r;  //90-r��-90-r
	double theta_max2 = (-1)*_theta_c + _theta_r;  //90+r��9-0+r

	for (unsigned int i = 0; i < _lines.size();i++)
	{
		Line2Point line_t = _lines[i];
		double theta_d = line_t.mTheta_d;

		if ((theta_d>theta_min1 && theta_d<theta_max1) || (theta_d>theta_min2 && theta_d<theta_max2)) {

		}
		else
		{
			lines_t.push_back(line_t);   //�������������ֱ��
		}

	}

	return lines_t;
}

/*----------------------------------------------------------------*/

//����ֱ�ߵĽǶ�
void LineCalAngle(std::vector<Line2Point>& _lines)
{
	for (int i = 0; i < (int)_lines.size();i++)
	{
		Line2Point line_t = _lines[i];
		line_t.CalTheta();
	}
}

/*----------------------------------------------------------------*/

//��ͼ�ϻ�ֱ��
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

//����ж� �����Ĭ��Ϊ�ϸ�
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

//�ж����չʾ
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
