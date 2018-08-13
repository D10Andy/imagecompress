#include "fenkuaiDCT.h"
#include "main.h"




void Block_DCT(Mat &src, Mat &dst)
{
	double pi = 3.141592657;
	Mat C_Mat(sub_num, sub_num, CV_64FC1);
	Mat CT_Mat(sub_num, sub_num, CV_64FC1);

	//C矩阵的初始化
	for (int i = 0; i < C_Mat.rows; i++)
		C_Mat.at<double>(0, i) = sqrt(2.0 / (C_Mat.rows))*sqrt(1.0 / C_Mat.rows);
	for (int i = 1; i < C_Mat.rows; i++)
		for (int j = 0; j < C_Mat.cols; j++)
			C_Mat.at<double>(i, j) = (2.0 / (C_Mat.rows))*cos(pi*i*(2 * j + 1) / (2 * C_Mat.rows));

	//C转置矩阵的初始化
	CT_Mat = C_Mat.t();
	Mat D_Mat(sub_num, sub_num, CV_64FC1);
	Mat E_Mat(sub_num, sub_num, CV_64FC1);

	//图像块的循环
	for (int m = 0; m < bsize; m++)
		for (int n = 0; n < bsize; n++)
		{
			//每个图像块分别进行处理
			for (int k = 0; k < sub_num; k++)
				for (int l = 0; l < sub_num; l++)
					D_Mat.at<double>(k, l) = src.at<double>(m*sub_num + k, n*sub_num + l);

			//8*8块的DCT变换
			E_Mat = C_Mat*D_Mat*CT_Mat;

			//将分别处理过的图像块还原为原来的一个矩阵中
			for (int k = 0; k < sub_num; k++)
			{
				for (int l = 0; l <sub_num; l++)
					dst.at<double>(m*sub_num + k, n*sub_num + l) = E_Mat.at<double>(k, l);
			}
		}
}

//dst是输入矩阵，qua是输出矩阵
void Quantification(Mat &dst, Mat &qua)//缺少对量化后的系数进行取整的操作
{
	//量化矩阵的初始化
	//该矩阵是从论坛中找的经典量化矩阵，具体生成原因不明
	int quantification[8][8] =
	{
		{ 16, 11, 10, 16, 24, 40, 51, 61 },
		{ 12, 12, 14, 19, 26, 58, 60, 55 },
		{ 14, 13, 16, 24, 40, 57, 69, 56 },
		{ 14, 17, 22, 29, 51, 87, 80, 62 },
		{ 18, 22, 37, 56, 68, 109, 103, 77 },
		{ 24, 35, 55, 64, 81, 104, 113, 92 },
		{ 49, 64, 78, 87, 103, 121, 120, 101 },
		{ 72, 92, 95, 98, 112, 100, 103, 99 }
	};
	Mat D_Mat(sub_num, sub_num, CV_64FC1);
	for (int m = 0; m < bsize; m++)
	{
		for (int n = 0; n < bsize; n++)			
		{
			//图像块的循环
			for (int k = 0; k < sub_num; k++)
			{
				for (int l = 0; l < sub_num; l++)
				{
					D_Mat.at<double>(k, l) = dst.at<double>(m*sub_num + k, n*sub_num + l);
					D_Mat.at<double>(k, l) /= quantification[k][l];
				}
			}
			for (int k = 0; k < sub_num; k++)
			{
				for (int l = 0; l < sub_num; l++)
				{
					qua.at<double>(m*sub_num + k, n*sub_num + l) = D_Mat.at<double>(k, l);
					qua.at<double>(m*sub_num + k, n*sub_num + l) = round(qua.at<double>(m*sub_num + k, n*sub_num + l));
				}
				//是不是应该先+0.5以后再将double强制转换为int,达到四舍五入的目的
			}
		}
	}


}