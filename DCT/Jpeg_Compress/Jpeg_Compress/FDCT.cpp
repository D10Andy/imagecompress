#include "FDCT.h"
#include "main.h"



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


void FDCT(Mat &qua,Mat &FD_Mat)
{
	Mat qua_Mat(sub_num, sub_num, CV_64FC1);
	Mat AAA(sub_num, sub_num, CV_64FC1);
	for (int m = 0; m < bsize; m++)
	{
		for (int n = 0; n < bsize; n++)			
		{
			//��ÿһ�ֿ鴦��
			for (int k = 0; k < 8; k++)
			{
				for (int l = 0; l < 8; l++)
				{
					AAA.at<double>(k, l) = qua.at<double>(m * 8 + k, n * 8 + l);
				}
			}

			Fqua(AAA);
			ReDCT(AAA, qua_Mat);
			for (int k = 0; k < 8; k++)
			{
				for (int l = 0; l < 8; l++)
				{
					FD_Mat.at<double>(m * 8 + k, n * 8 + l) = qua_Mat.at<double>(k, l);
				}
			}
		}
	}
}
void Fqua(Mat &A)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			A.at<double>(i, j) *= quantification[i][j];	//������
		}
	}
}

//��DCT�任
void ReDCT(cv::Mat &D_Mat, cv::Mat &E_Mat)	//�������һ���ֿ����
{
	//��άDCT����任�������任����ͬ���ǿɷ����
	//F=C*f*CT,����ͬ���ķ����������C��CT���õ�f=C-1*F*CT-1
	double pi = 3.141592657;
	Mat C_Mat(sub_num, sub_num, CV_64FC1);
	Mat C_Mat_Inv(sub_num, sub_num, CV_64FC1);
	Mat CT_Mat(sub_num, sub_num, CV_64FC1);
	Mat CT_Mat_Inv(sub_num, sub_num, CV_64FC1);

	//C����ĳ�ʼ��
	for (int i = 0; i < C_Mat.rows; i++)
		C_Mat.at<double>(0, i) = sqrt(2.0 / (C_Mat.rows))*sqrt(1.0 / C_Mat.rows);
	for (int i = 1; i<C_Mat.rows; i++)
		for (int j = 0; j < C_Mat.cols; j++)
			C_Mat.at<double>(i, j) = (2.0 / (C_Mat.rows)) * cos(pi * i * (2 * j + 1) / (2 * C_Mat.rows));
	//Cת�þ���ĳ�ʼ��
	CT_Mat = C_Mat.t();		//�������C��CT���
	invert(C_Mat, C_Mat_Inv);
	invert(CT_Mat, CT_Mat_Inv);
	E_Mat = C_Mat_Inv*D_Mat*CT_Mat_Inv;		//ת���ĺ���
}
