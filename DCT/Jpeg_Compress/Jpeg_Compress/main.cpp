#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "math.h"
#include "cv.h"
#include "stdlib.h"

//自定义头文件
#include "Tools.h"
#include "fenkuaiDCT.h"
#include "Huffman.h"
#include"main.h"
#include "FDCT.h"

using namespace std;
using namespace cv;

Mat img = imread("lena_256.jpg", 0);		//读取图像
void Block_DCT(Mat &src, Mat &dst);
void Quantification(Mat &dst, Mat &qua);

//参数初始化
int sub_num = 8;		//8*8的图像块
int rows = img.rows;				//图像像素的行数
int cols = img.cols;				//图像像素的列数
int bsize = rows/ sub_num;			//将图像分成8*8的图像块

ofstream fout;
void main()
{
	imshow("lena_256", img);				//显示原图
	fout.open("imgdata.txt", ios_base::out);

	Mat src(img.rows, img.cols, CV_64FC1);
	img.convertTo(src, CV_64FC1);
	Mat dst(src.rows, src.cols, CV_64FC1);
	Block_DCT(src, dst);
	Mat dst_1(src.rows, src.cols, CV_8UC1);
	dst.convertTo(dst_1, CV_8UC1);
	imshow("分块DCT图", dst_1);		//分块DCT后图像

	//像素矩阵的量化及显示
	Mat qua(src.rows, src.cols, CV_64FC1);
	Quantification(dst, qua);
	Mat qua_1(src.rows, src.cols, CV_8UC1);
	qua.convertTo(qua_1, CV_8UC1);
	imshow("量化图", qua_1);			//量化后图像

	//FDCT
	Mat fdct(src.rows, src.cols, CV_64FC1);
	FDCT(qua, fdct);
	Mat fdct_1(src.rows, src.cols, CV_8UC1);
	fdct.convertTo(fdct_1, CV_8UC1);
	imshow("恢复图", fdct_1);
	//以上部分全部正确

	qua.convertTo(qua, CV_32SC1);
	HufFuc(qua);
	//添加功能显示压缩率的大小
	fout.close();
	cvWaitKey(0);
	cin.get();
}




