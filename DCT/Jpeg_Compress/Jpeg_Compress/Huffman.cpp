#include"Huffman.h"
#include"main.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<iostream>

//全局变量
int pred = 0;//前一个DC值
int zz[64][2] = { 0 };
char ac_vv[] = { 0 };

//之字形编码
static int zigzag_table[64] = {
	0,   1,  5,  6, 14, 15, 27, 28,
	2,   4,  7, 13, 16, 26, 29, 42,
	3,   8, 12, 17, 25, 30, 41, 43,
	9,  11, 18, 24, 31, 40, 44, 53,
	10, 19, 23, 32, 39, 45, 52, 54,
	20, 22, 33, 38, 46, 51, 55, 60,
	21, 34, 37, 47, 50, 56, 59, 61,
	35, 36, 48, 49, 57, 58, 62, 63
};
//DC 亮度 category 对应的Code Word
int luminance_dc_code_table[] = {
	0x0000, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x000E, 0x001E, 0x003E,
	0x007E, 0x00FE, 0x01FE
};
//DC 亮度 category 对应的Code Length
int luminance_dc_size_table[] = { 2, 3, 3, 3, 3, 3, 4, 5, 6, 7, 8, 9 };
//AC 亮度 category 对应的Code Word
int chrominance_dc_code_table[] = {
	0x0000, 0x0001, 0x0002, 0x0006, 0x000E, 0x001E, 0x003E, 0x007E, 0x00FE,
	0x01FE, 0x03FE, 0x07FE
};
//AC 亮度 category 对应的Code Length
int chrominance_dc_size_table[] = {
	0x0002, 0x0002, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008,
	0x0009, 0x000A, 0x000B
};
//AC 亮度 category 对应的Code Word
int luminance_ac_code_table[] = {
	0x000A,//(EOB),（run/size）=(0/0)
	0x0000, 0x0001, 0x0004, 0x000B, 0x001A, 0x0078, 0x00F8, 0x03F6,
	0xFF82, 0xFF83, 0x000C, 0x001B, 0x0079, 0x01F6, 0x07F6, 0xFF84, 0xFF85,
	0xFF86, 0xFF87, 0xFF88, 0x001C, 0x00F9, 0x03F7, 0x0FF4, 0xFF89, 0xFF8A,
	0xFF8b, 0xFF8C, 0xFF8D, 0xFF8E, 0x003A, 0x01F7, 0x0FF5, 0xFF8F, 0xFF90,
	0xFF91, 0xFF92, 0xFF93, 0xFF94, 0xFF95, 0x003B, 0x03F8, 0xFF96, 0xFF97,
	0xFF98, 0xFF99, 0xFF9A, 0xFF9B, 0xFF9C, 0xFF9D, 0x007A, 0x07F7, 0xFF9E,
	0xFF9F, 0xFFA0, 0xFFA1, 0xFFA2, 0xFFA3, 0xFFA4, 0xFFA5, 0x007B, 0x0FF6,
	0xFFA6, 0xFFA7, 0xFFA8, 0xFFA9, 0xFFAA, 0xFFAB, 0xFFAC, 0xFFAD, 0x00FA,
	0x0FF7, 0xFFAE, 0xFFAF, 0xFFB0, 0xFFB1, 0xFFB2, 0xFFB3, 0xFFB4, 0xFFB5,
	0x01F8, 0x7FC0, 0xFFB6, 0xFFB7, 0xFFB8, 0xFFB9, 0xFFBA, 0xFFBB, 0xFFBC,
	0xFFBD, 0x01F9, 0xFFBE, 0xFFBF, 0xFFC0, 0xFFC1, 0xFFC2, 0xFFC3, 0xFFC4,
	0xFFC5, 0xFFC6, 0x01FA, 0xFFC7, 0xFFC8, 0xFFC9, 0xFFCA, 0xFFCB, 0xFFCC,
	0xFFCD, 0xFFCE, 0xFFCF, 0x03F9, 0xFFD0, 0xFFD1, 0xFFD2, 0xFFD3, 0xFFD4,
	0xFFD5, 0xFFD6, 0xFFD7, 0xFFD8, 0x03FA, 0xFFD9, 0xFFDA, 0xFFDB, 0xFFDC,
	0xFFDD, 0xFFDE, 0xFFDF, 0xFFE0, 0xFFE1, 0x07F8, 0xFFE2, 0xFFE3, 0xFFE4,
	0xFFE5, 0xFFE6, 0xFFE7, 0xFFE8, 0xFFE9, 0xFFEA, 0xFFEB, 0xFFEC, 0xFFED,
	0xFFEE, 0xFFEF, 0xFFF0, 0xFFF1, 0xFFF2, 0xFFF3, 0xFFF4, 0xFFF5, 0xFFF6,
	0xFFF7, 0xFFF8, 0xFFF9, 0xFFFA, 0xFFFB, 0xFFFC, 0xFFFD, 0xFFFE,
	0x07F9	//(ZRL 分配给运行16个零系数的HUFFVAL中的值)  (run/size)=(F/0)
};
//AC 亮度 category 对应的Code Length
int luminance_ac_size_table[] = {
	4,
	2,  2,  3,  4,  5,  7,  8, 10,
	16, 16,  4,  5,  7,  9, 11, 16, 16,
	16, 16, 16,  5,  8, 10, 12, 16, 16,
	16, 16, 16, 16,  6,  9, 12, 16, 16,
	16, 16, 16, 16, 16,  6, 10, 16, 16,
	16, 16, 16, 16, 16, 16,  7, 11, 16,
	16, 16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16,  8,
	12, 16, 16, 16, 16, 16, 16, 16, 16,
	9, 15, 16, 16, 16, 16, 16, 16, 16,
	16,  9, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 10, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 11, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16, 16,
	16, 16, 16, 16, 16, 16, 16, 16,
	12
};
//AC 色度 category 对应的Code Word
int chrominance_ac_code_table[] = {
	0x0000, 0x0001, 0x0004, 0x000A, 0x0018, 0x0019, 0x0038, 0x0078, 0x01F4,
	0x03F6, 0x0FF4, 0x000B, 0x0039, 0x00F6, 0x01F5, 0x07F6, 0x0FF5, 0xFF88,
	0xFF89, 0xFF8A, 0xFF8B, 0x001A, 0x00F7, 0x03F7, 0x0FF6, 0x7FC2, 0xFF8C,
	0xFF8D, 0xFF8E, 0xFF8F, 0xFF90, 0x001B, 0x00F8, 0x03F8, 0x0FF7, 0xFF91,
	0xFF92, 0xFF93, 0xFF94, 0xFF95, 0xFF96, 0x003A, 0x01F6, 0xFF97, 0xFF98,
	0xFF99, 0xFF9A, 0xFF9B, 0xFF9C, 0xFF9D, 0xFF9E, 0x003B, 0x03F9, 0xFF9F,
	0xFFA0, 0xFFA1, 0xFFA2, 0xFFA3, 0xFFA4, 0xFFA5, 0xFFA6, 0x0079, 0x07F7,
	0xFFA7, 0xFFA8, 0xFFA9, 0xFFAA, 0xFFAB, 0xFFAC, 0xFFAD, 0xFFAE, 0x007A,
	0x07F8, 0xFFAF, 0xFFB0, 0xFFB1, 0xFFB2, 0xFFB3, 0xFFB4, 0xFFB5, 0xFFB6,
	0x00F9, 0xFFB7, 0xFFB8, 0xFFB9, 0xFFBA, 0xFFBB, 0xFFBC, 0xFFBD, 0xFFBE,
	0xFFBF, 0x01F7, 0xFFC0, 0xFFC1, 0xFFC2, 0xFFC3, 0xFFC4, 0xFFC5, 0xFFC6,
	0xFFC7, 0xFFC8, 0x01F8, 0xFFC9, 0xFFCA, 0xFFCB, 0xFFCC, 0xFFCD, 0xFFCE,
	0xFFCF, 0xFFD0, 0xFFD1, 0x01F9, 0xFFD2, 0xFFD3, 0xFFD4, 0xFFD5, 0xFFD6,
	0xFFD7, 0xFFD8, 0xFFD9, 0xFFDA, 0x01FA, 0xFFDB, 0xFFDC, 0xFFDD, 0xFFDE,
	0xFFDF, 0xFFE0, 0xFFE1, 0xFFE2, 0xFFE3, 0x07F9, 0xFFE4, 0xFFE5, 0xFFE6,
	0xFFE7, 0xFFE8, 0xFFE9, 0xFFEA, 0xFFEb, 0xFFEC, 0x3FE0, 0xFFED, 0xFFEE,
	0xFFEF, 0xFFF0, 0xFFF1, 0xFFF2, 0xFFF3, 0xFFF4, 0xFFF5, 0x7FC3, 0xFFF6,
	0xFFF7, 0xFFF8, 0xFFF9, 0xFFFA, 0xFFFB, 0xFFFC, 0xFFFD, 0xFFFE,
	0x03FA
};
//AC 色度 category 对应的Code Length
int chrominance_ac_size_table[] = {
	0x0002, 0x0002, 0x0003, 0x0004, 0x0005, 0x0005, 0x0006, 0x0007, 0x0009,
	0x000A, 0x000C, 0x0004, 0x0006, 0x0008, 0x0009, 0x000B, 0x000C, 0x0010,
	0x0010, 0x0010, 0x0010, 0x0005, 0x0008, 0x000A, 0x000C, 0x000F, 0x0010,
	0x0010, 0x0010, 0x0010, 0x0010, 0x0005, 0x0008, 0x000A, 0x000C, 0x0010,
	0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0006, 0x0009, 0x0010, 0x0010,
	0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0006, 0x000A, 0x0010,
	0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0007, 0x000B,
	0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0007,
	0x000B, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
	0x0008, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
	0x0010, 0x0009, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
	0x0010, 0x0010, 0x0009, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
	0x0010, 0x0010, 0x0010, 0x0009, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
	0x0010, 0x0010, 0x0010, 0x0010, 0x0009, 0x0010, 0x0010, 0x0010, 0x0010,
	0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x000B, 0x0010, 0x0010, 0x0010,
	0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x000E, 0x0010, 0x0010,
	0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x000F, 0x0010,
	0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
	0x000A
};
using namespace std;

//huffman函数//输出到文件中
void HufFuc(Mat &qua)
{
	//之字形编码
	for (int m = 0; m < bsize; m++)
	{
		for (int n = 0; n < bsize; n++)
		{
			//每个图像块分别进行处理
			int quadata[64] = { 0 };//存放每个分块的数据
			int zignum = 0;		//存放之字形编码的下标
			for (int k = sub_num * m + 0 ; k < sub_num * m + sub_num; k++)
			{
				for (int l = sub_num * n + 0  ; l < sub_num * n + sub_num; l++)
				{
					int zig = zigzag_table[zignum];	//取出下标
					quadata[zig] = qua.at<int>(k, l);//将mat矩阵转换为1x64的数组
					zignum++;
				}
			}
			//将接近0的数值赋值为0
			for (int i = 1; i < 64; i++)
			{
				if (quadata[i] >= -1 && quadata[i] <= 1)
				{
					quadata[i] = 0;
				}
			}
			//DC差分脉冲调制，暂时没有使用差分
 			int DIFF = 0;
			int g_ValClass = 0;
			char  g_binarayNum[16] = { 0 };
			DIFF = quadata[0];// -pred;	
			HexToBin(DIFF, g_binarayNum, g_ValClass);		//得到的g_binararyNum 是反向的
			int dc_code = luminance_dc_code_table[g_ValClass];
			int dc_size_table = luminance_dc_size_table[g_ValClass];

			//十六进制转换成二进制char 
			char DcBinTemp[16] = { 0 };
			AcHexToDec(dc_code, DcBinTemp);
			for (int i = 16 - dc_size_table; i < 16; i++)
			{
				fout << DcBinTemp[i];					//输出的是DC的Huffman值
			}
			fout << " ";
			//cout << std::endl;
			if (g_ValClass == NULL)
				fout << 0;								//防止输出为空，在解压缩时出现错误
			else
			{
				for (int i = g_ValClass - 1; i >= 0; i--)
				{
					fout << g_binarayNum[i];			//输出的是DC的实际保存值
				}
			}
			//pred = quadata[0];							//存储上次的DC值
			fout << " ";
			//std::cout << std::endl;

			//AC编码
			//定义二维数组,存放非零数值
			int ffff = 0;				//统计0值的个数
			for (int i = 0; i < 64; i++)
			{
				if (quadata[i] == 0)
				{
					ffff++;
				}
			}
			//将(NN,SS)放到二维数组中
			int temp = 0;
			int nozero = 0;
			for (int i = 1; i < 64; i++)
			{
				if (quadata[i] == 0)
				{
					temp++;
				}
				else
				{

					zz[nozero][0] = temp;
					zz[nozero][1] = quadata[i];
					temp = 0;
					nozero++;
				}
			}
			zz[nozero][0] = 0;
			zz[nozero][1] = 0;			//保险
			//在屏幕上输出(NN,SS)
			//for (int i = 0; i < 64; i++)
			//{
			//	cout << "(" << zz[i][0] << " " << zz[i][1] << ")" << std::endl;
			//	if (zz[i][0] == 0 && zz[i][1] == 0)
			//	{
			//		break;
			//	}
			//}
			//cout << "AC code" << std::endl;

			//AC   (NN,SS)VV 查询编码
			for (int i = 0; i < (64 - ffff); i++)
			{
				int aa = zz[i][1];
				int ac_val = 0;
				HexToBin(aa, g_binarayNum, ac_val);

				int ac_table = zz[i][0] * 10 + ac_val;				//亮度code_table的下标
				int ac_code = luminance_ac_code_table[ac_table];	//ac_code存放的是(NN,VV)对应的十六进制代码
				int ac_size_table = luminance_ac_size_table[ac_table];//ac_size_table存放的是ac_code的长度

																	  //十六进制转换成二进制char 
				char AcBinTemp[16] = { 0 };
				AcHexToDec(ac_code, AcBinTemp);
				//fout << "code" << " ";

				for (int i = 16 - ac_size_table; i < 16; i++)
				{
					fout << AcBinTemp[i];	// 输出的是AC的Huffman编码值(NN,SS)
				}
				fout << " ";

				for (int i = ac_val - 1; i >= 0; i--)
				{
					fout << g_binarayNum[i];			//此时输出的是AC 的实际保存值  VV
				}
				fout << " ";

				//fout << endl;
			}
			fout << "\n";
			//fout <<"\r\n";
		}
		//fout << endl;
	}
}


void HexToBin(int num, char  binarayNum[], int & ValClass)
{
	//分类
	int i = 0, sum = 0;
	int intNum[16] = { 0 };

	if (num == 0)
	{
		ValClass = NULL;	//此处是空，改变的是在上面DC输出实际值时，要加上一个不为空的判断
		intNum[0] = 0;
	}

	if (num > 0)
	{
		if (num == 1)
		{

			ValClass = 1;
			intNum[0] = 1;
		}


		else if (num >= 2 && num <= 3)
		{
			int sum = num;
			ValClass = 2;
			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}

		}
		else if (num >= 4 && num <= 7)
		{
			ValClass = 3;
			int sum = num;
			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= 8 && num <= 15)
		{
			ValClass = 4;
			int sum = num;
			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}

		else if (num >= 16 && num <= 31)
		{
			ValClass = 5;
			int sum = num;
			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= 32 && num <= 63)
		{
			ValClass = 6;
			int sum = num;
			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= 64 && num <= 127)
		{
			ValClass = 7;
			int sum = num;
			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= 128 && num <= 255)
		{
			ValClass = 8;
			int sum = num;
			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= 256 && num <= 511)
		{
			ValClass = 9;
			int sum = num;
			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= 512 && num <= 1023)
		{
			ValClass = 10;
			int sum = num;
			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= 1024 && num <= 2047)
		{
			ValClass = 11;
			int sum = num;
			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= 2048 && num <= 4095)
		{
			ValClass = 12;
			int sum = num;
			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= 4096 && num <= 8191)
		{
			ValClass = 13;
			int sum = num;
			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= 8192 && num <= 16383)
		{
			ValClass = 14;
			int sum = num;
			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= 16384 && num <= 32767)
		{
			ValClass = 15;
			int sum = num;
			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}

	}


	//负数转换

	else if (num < 0)
	{
		if (num == -1)
		{

			ValClass = 1;
			intNum[0] = 0;
		}
		else if (num >= -3 && num <= -2)
		{
			ValClass = 2;
			int sum = pow(2, ValClass) + num - 1;

			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= -7 && num <= -4)
		{
			ValClass = 3;
			int sum = pow(2, ValClass) + num - 1;

			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= -15 && num <= -8)
		{
			ValClass = 4;
			int sum = pow(2, ValClass) + num - 1;

			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= -31 && num <= -16)
		{
			ValClass = 5;
			int sum = pow(2, ValClass) + num - 1;

			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= -63 && num <= -32)
		{
			ValClass = 6;
			int sum = pow(2, ValClass) + num - 1;

			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= -127 && num <= -64)
		{
			ValClass = 7;
			int sum = pow(2, ValClass) + num - 1;

			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= -255 && num <= -128)
		{
			ValClass = 8;
			int sum = pow(2, ValClass) + num - 1;

			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= -511 && num <= -256)
		{
			ValClass = 9;
			int sum = pow(2, ValClass) + num - 1;

			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= -1023 && num <= -512)
		{
			ValClass = 10;
			int sum = pow(2, ValClass) + num - 1;

			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= -2047 && num <= -1024)
		{
			ValClass = 11;
			int sum = pow(2, ValClass) + num - 1;

			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= -4095 && num <= -2048)
		{
			ValClass = 12;
			int sum = pow(2, ValClass) + num - 1;

			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= -8191 && num <= -4096)
		{
			ValClass = 13;
			int sum = pow(2, ValClass) + num - 1;

			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= -16383 && num <= -8192)
		{
			ValClass = 14;
			int sum = pow(2, ValClass) + num - 1;

			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}
		else if (num >= -32767 && num <= -16384)
		{
			ValClass = 15;
			int sum = pow(2, ValClass) + num - 1;

			for (i = 0; i < ValClass; i++)
			{
				intNum[i] = sum % 2;
				sum = sum / 2;
			}
		}

	}

	//g_ValClass = ValClass;

	//int 转换成char
	for (int i = ValClass - 1; i >= 0; i--)
		binarayNum[i] = intNum[i] + '0';

	//for (int i = ValClass - 1; i >= 0; i--)
	//	 printf("%s",binarayNum[i]);
}



