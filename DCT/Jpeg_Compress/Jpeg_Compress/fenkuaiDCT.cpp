#include "fenkuaiDCT.h"
#include "main.h"




void Block_DCT(Mat &src, Mat &dst)
{
	double pi = 3.141592657;
	Mat C_Mat(sub_num, sub_num, CV_64FC1);
	Mat CT_Mat(sub_num, sub_num, CV_64FC1);

	//C����ĳ�ʼ��
	for (int i = 0; i < C_Mat.rows; i++)
		C_Mat.at<double>(0, i) = sqrt(2.0 / (C_Mat.rows))*sqrt(1.0 / C_Mat.rows);
	for (int i = 1; i < C_Mat.rows; i++)
		for (int j = 0; j < C_Mat.cols; j++)
			C_Mat.at<double>(i, j) = (2.0 / (C_Mat.rows))*cos(pi*i*(2 * j + 1) / (2 * C_Mat.rows));

	//Cת�þ���ĳ�ʼ��
	CT_Mat = C_Mat.t();
	Mat D_Mat(sub_num, sub_num, CV_64FC1);
	Mat E_Mat(sub_num, sub_num, CV_64FC1);

	//ͼ����ѭ��
	for (int m = 0; m < bsize; m++)
		for (int n = 0; n < bsize; n++)
		{
			//ÿ��ͼ���ֱ���д���
			for (int k = 0; k < sub_num; k++)
				for (int l = 0; l < sub_num; l++)
					D_Mat.at<double>(k, l) = src.at<double>(m*sub_num + k, n*sub_num + l);

			//8*8���DCT�任
			E_Mat = C_Mat*D_Mat*CT_Mat;

			//���ֱ������ͼ��黹ԭΪԭ����һ��������
			for (int k = 0; k < sub_num; k++)
			{
				for (int l = 0; l <sub_num; l++)
					dst.at<double>(m*sub_num + k, n*sub_num + l) = E_Mat.at<double>(k, l);
			}
		}
}

//dst���������qua���������
void Quantification(Mat &dst, Mat &qua)//ȱ�ٶ��������ϵ������ȡ���Ĳ���
{
	//��������ĳ�ʼ��
	//�þ����Ǵ���̳���ҵľ����������󣬾�������ԭ����
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
			//ͼ����ѭ��
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
				//�ǲ���Ӧ����+0.5�Ժ��ٽ�doubleǿ��ת��Ϊint,�ﵽ���������Ŀ��
			}
		}
	}


}