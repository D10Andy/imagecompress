#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "math.h"
#include "cv.h"
#include "stdlib.h"

using namespace std;
using namespace cv;

void DCT(Mat &src, Mat &dst)
{
	double pi = 3.141592657;
	Mat C_Mat(src.rows, src.cols, CV_64FC1);
	Mat CT_Mat(src.rows, src.cols, CV_64FC1);

	for (int j = 0; j<C_Mat.rows; j++)
		C_Mat.at<double>(0, j) = sqrt(2.0 / (C_Mat.rows))*sqrt(1.0 / C_Mat.rows);

	for (int i = 1; i<C_Mat.rows; i++)
		for (int j = 0; j<C_Mat.cols; j++)
			C_Mat.at<double>(i, j) = (2.0 / (C_Mat.rows))*cos(pi*i*(2 * j + 1) / (2 * C_Mat.rows));

	CT_Mat = C_Mat.t();	//ת��û�д���
	cout << C_Mat.at<double>(2, 3);

	dst = C_Mat*src*CT_Mat;	//�������û�д�������֤
}

void main1()
{
	Mat img = imread("lena_256.jpg", 0);
	imshow("img", img);
	Mat src(img.rows, img.cols, CV_64FC1);
	img.convertTo(src, CV_64FC1);
	//imshow("src",src);
	Mat dst(src.rows, src.cols, CV_64FC1);
	DCT(src, dst);
	imshow("dst", dst);
	cout << "����" << img.rows << endl;
	cout << "����" << img.cols << endl;
	cvWaitKey(0);
}
