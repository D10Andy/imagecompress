//��CPP�зŵ���һЩС���߳���

//header file
#include "Tools.h"



//��ʾ��������

void datashow(Mat &DataMat)
{
	for (int i = 0; i < DataMat.rows; i++)//
	{
		for (int j = 0; j < DataMat.cols; j++)//
		{
			std::cout << (int)DataMat.at<double>(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

//��ʾ��(m,n)�������������
void datashow(Mat &DataMat, int m, int n)
{
	for (int i = 0 + 8 * m; i < 8 + 8 * m; i++)//
	{
		for (int j = 0 + 8 * n; j < 8 + 8 * n; j++)//
		{
			std::cout << DataMat.at<int>(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

void AcHexToDec(int a, char c[])
{
	int b[16] = { 0 };
	for (int i = 0; i < 16; ++i)
	{
		b[16 - 1 - i] = a % 2;
		a /= 2;
	}
	for (int i = 15; i >= 0; i--)
		c[i] = b[i] + '0';

	//std::cout << " ";
	//for (int i = 0; i != 16; ++i)
	//{
	//	std::cout << c[i];
	//}
	//std::cout << " ";
}

