#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "math.h"
#include "cv.h"
#include "stdlib.h"

//�Զ���ͷ�ļ�
#include "Tools.h"
#include "fenkuaiDCT.h"
#include "Huffman.h"
#include"main.h"
#include "FDCT.h"

using namespace std;
using namespace cv;

Mat img = imread("lena_256.jpg", 0);		//��ȡͼ��
void Block_DCT(Mat &src, Mat &dst);
void Quantification(Mat &dst, Mat &qua);

//������ʼ��
int sub_num = 8;		//8*8��ͼ���
int rows = img.rows;				//ͼ�����ص�����
int cols = img.cols;				//ͼ�����ص�����
int bsize = rows/ sub_num;			//��ͼ��ֳ�8*8��ͼ���

ofstream fout;
void main()
{
	imshow("lena_256", img);				//��ʾԭͼ
	fout.open("imgdata.txt", ios_base::out);

	Mat src(img.rows, img.cols, CV_64FC1);
	img.convertTo(src, CV_64FC1);
	Mat dst(src.rows, src.cols, CV_64FC1);
	Block_DCT(src, dst);
	Mat dst_1(src.rows, src.cols, CV_8UC1);
	dst.convertTo(dst_1, CV_8UC1);
	imshow("�ֿ�DCTͼ", dst_1);		//�ֿ�DCT��ͼ��

	//���ؾ������������ʾ
	Mat qua(src.rows, src.cols, CV_64FC1);
	Quantification(dst, qua);
	Mat qua_1(src.rows, src.cols, CV_8UC1);
	qua.convertTo(qua_1, CV_8UC1);
	imshow("����ͼ", qua_1);			//������ͼ��

	//FDCT
	Mat fdct(src.rows, src.cols, CV_64FC1);
	FDCT(qua, fdct);
	Mat fdct_1(src.rows, src.cols, CV_8UC1);
	fdct.convertTo(fdct_1, CV_8UC1);
	imshow("�ָ�ͼ", fdct_1);
	//���ϲ���ȫ����ȷ

	qua.convertTo(qua, CV_32SC1);
	HufFuc(qua);
	//��ӹ�����ʾѹ���ʵĴ�С
	fout.close();
	cvWaitKey(0);
	cin.get();
}




