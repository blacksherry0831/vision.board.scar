/*
 * img_proc.h
 *
 *  Created on: 2020��4��10��
 *      Author: yjkj909
 */

#ifndef IMG_PROC_H_
#define IMG_PROC_H_

#include "opencv2/opencv.hpp"
#include "Line2Point.h"

enum DetectResult
{
	QUALIFIED = 0x01,  //�ϸ�
	UNQUALIFIED = 0x02,  //���ϸ�
	UNKNOWN = 0x03,  //δ֪
};

int get_is_binary();  //��ֵ��
int get_is_denoise();  //ȥ��
int get_is_blackSkin();  //��Ƥ
int get_is_hough();  //hough
int get_is_morphology();  //��̬ѧ
int get_is_showResult();  //���չʾ
int get_blaskSkin_min_area();  //��Ƥ��С���
int get_hough_thresold(); //hough������ֵ
int get_hough_min_length();  //hough��С�߶γ���
int get_hough_max_gap(); //hough����߶μ��
int get_hough_max_angle();  //hough���Ƕ�
int get_crack_min_area();  //������С���
int get_crack_aspect_ratio();  //���Ƴ����
int get_crack_area_ratio();  //���������

void set_is_binary(int _v);  //��ֵ��
void set_is_denoise(int _v);  //ȥ��
void set_is_blackSkin(int _v);  //��Ƥ
void set_is_hough(int _v);  //hough
void set_is_morphology(int _v);  //��̬ѧ
void set_is_showResult(int _v);  //���չʾ
void set_blaskSkin_min_area(int _v);  //��Ƥ��С���
void set_hough_thresold(int _v); //hough������ֵ
void set_hough_min_length(int _v);  //hough��С�߶γ���
void set_hough_max_gap(int _v); //hough����߶μ��
void set_hough_max_angle(int _v);  //hough���Ƕ�
void set_crack_min_area(int _v);  //������С���
void set_crack_aspect_ratio(int _v);  //���Ƴ����
void set_crack_area_ratio(int _v);  //���������

void set_last_detect_result(enum DetectResult _v);  //�����յļ����
enum DetectResult get_last_detect_result();   //�����յļ����
int get_number_of_mask();  //һ�ּ����ɰ�ͼƬ����
void inc_processed_cnt();  //һ�ּ����Ѽ���ɰ�ͼƬ����������1
int get_processed_cnt();  //��ȡ һ�ּ����Ѽ���ɰ�ͼƬ����

void Binary2Smooth_Line(IplImage * _img); //ȥ��
IplImage* ImgProcessIpl_BlackSkin(IplImage* _img, int* posFlag); //���Һ�Ƥ

void ImgProcessIpl_Base(IplImage * _img); //��ֵ��+ȥ��

unsigned int ImgProc_PixelNumber_Gray(IplImage * _img, int _p); //����׵��� �������쳣����Ŀ

void ImgProcessIpl(IplImage * _img,int* posFlag); //������Ӧ������ͼ�������Ӧ����  �����ֵ�����쳣��ռ��ͼ��ı���  ����  ����hogh�任��Ѱ����Ӧ��Բ

std::vector<Line2Point> getHoughLinesBase(IplImage * _img_bin, IplImage * _img_draw, CvScalar _color, int _thickness, const double _remove_degree,
		const int _line_th, const double _line_len_min, const double _line_gap); //����opencv��������hough�任 + ɾ���Ƕ���90�ȸ�����ֱ��

std::vector<Line2Point> Hough_Line_CV_PROBABILISTIC_GetLine(CvArr * image, double rho, double theta, int threshold,
		double _lineLenMin, double _lineGap); //����opencv���� ����hough�任 ����houghֱ�ߵ�������ص�

std::vector<Line2Point> LineRemove(std::vector<Line2Point>&  _lines, double _theta_c,
					double _theta_r);  //ɾ��ֱ�߽Ƕȷ���������ֱ��   ����ֱ�߽Ƕȷ���������ֱ��

void LineDraw(std::vector<Line2Point>& _lines, IplImage * img_t, CvScalar _color, int _thickness); //��ͼ�ϻ�ֱ��

void LineCalAngle(std::vector<Line2Point>& _lines); //����ֱ�ߵĽǶ�

void ImgProcessIpl_PredictResult(const int posFlag); //����ж�

void ImgProcessIpl_ShowResult(IplImage* _img);  //�ж����չʾ

void img_proc_init(int _v);
#endif /* IMG_PROC_H_ */
