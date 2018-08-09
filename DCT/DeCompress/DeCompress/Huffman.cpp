
#include "Huffman.h"
#include "Tool.h"
#include "main.h"

//未完成的东西
//未添加图像块的循环
//未添加DC系数

using namespace std;

//全局变量定义


cv::Mat ZigZag(8, 8, CV_64FC1);	//存储一个图像块反之字编码后的数据
								//之字顺序
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
//量化矩阵
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

//函数
//读取数据
void readcompressdata()
{
	fin.open("imgdata.txt");
	string InitInData = "0";
	string SubBlockData = { 0 };	//一个子块的数据

	cv::Mat E_Mat(sub_rows, sub_cols, CV_64FC1);
	cv::Mat ImgDataMat(myrows, mycols, CV_64FC1);		//存放所有图像数据
	cv::Mat AAA(myrows, mycols, CV_32SC1);
	cv::Mat III(myrows, mycols, CV_8UC1);
	int n = 0, m = 0;

	while (getline(fin, SubBlockData))		//使用getline将一行数据读取到SubBlockData中
	{
		//对SubBlockData进行分割
		//getline(fin, SubBlockData);

		int RunSize[64] = { 0 };	//顺序的1*64
		istringstream input(SubBlockData);			//创建一个字符串扫描流
		vector<int> NoHuffData;
		int ifzerobit = 0;		//判断奇偶位数
		int b = 0;
		int InitInData_length = 0;
		while (input >> InitInData)
		{
			char ifzero = InitInData[0];	//取出字符串的最高位
			//如果是奇数位，且为0，就要改变值
			if (ifzerobit % 2 == 1 && ifzero == '0')
			{
				//完善负数转换的代码
				InitInData_length = InitInData.length();
				b = mystringtoint(InitInData, InitInData_length);
			}
			
			else		//其他情况就不需要做出改变
			{
				string a = BinToHex(InitInData);
				b = mystoi(a);
			}
			NoHuffData.push_back(b);		//此时将一个分块的数据放置在NoHuffData数组中
			ifzerobit++;
		}
		ExtrHuffDatta(NoHuffData,RunSize);
		ReZigZag(RunSize);
		ReDCT(ZigZag, E_Mat);

		for (int k = 0; k < 8; k++)
		{
			for (int l = 0; l < 8; l++)
			{
				ImgDataMat.at<double>(m * 8 + k, n * 8 + l) = E_Mat.at<double>(k, l);
			}
		}
		if (n < 31)
			n++;
		else
		{
			if (m < 31)
			{
				m++;
				n = 0;
			}

		}
		NoHuffData.clear();

	}
	ImgDataMat.convertTo(III, CV_8UC1);
	cv::imshow("iii", III);
}

//HUffman数据的提取
void ExtrHuffDatta(vector<int> NoHuffData, int *RunSize)
{
	int HuffData[64][2] = { 0 };		//二维数组存放取出来的值
	auto ibegin = NoHuffData.begin();
	auto iend = NoHuffData.end();
	int dccode = *ibegin;
	ibegin++;
	int dcactual = *ibegin;		//将DC的两个系数分别提取，AC的一系列数值放到一个数组中,
	HuffData[0][0] = dccode;
	HuffData[0][1] = dcactual;		//此时是十六进制的 表示形式
	ibegin++;
	int aaa = 1;
	for (; ibegin != iend - 1; ibegin++)
	{
		int accode = *ibegin;		//虽然以cout输出时是十进制的数值，但元素内是十六进制的形式
		int acactual;
		if (ibegin != iend)
		{
			ibegin++;
			acactual = *ibegin;		//是否能将最后一个数据取出
		}
		HuffData[aaa][0] = accode;
		HuffData[aaa][1] = acactual;//将第一行所有的数据存放在二维数组中
		aaa++;

	}
	//调用数据比较
	//DC的值暂时不变，为dcactual

	//AC
	int NoRunSize[64][3] = { 0 };		//存放的是游程编码之前的值
	NoRunSize[0][2] = HuffData[0][1];
	for (int j = 1; j < 64; j++)
	{
		for (int i = 0; i < 162; i++)
		{
			if ((HuffData[j][0] == luminance_ac_code_table[i])&(HuffData[j][1] != 0))
			{
				//此时要得到的是在luminance_ac_code_table中对应的下标
				NoRunSize[j][0] = i / 10;
				NoRunSize[j][1] = i % 10;
				NoRunSize[j][2] = HuffData[j][1];     //(Run,Size,actual value)
													  //cout << i;
													  //cout << luminance_ac_code_table[i];
				break;
			}
		}
	}
	//游程编码的方式将数据转换到1*64的数组中
	int IfHaveData = 0;
	RunSize[0] = NoRunSize[0][2];
	for (int i = 1; i < 64;)
	{

		if (NoRunSize[i][0] != 0)
		{
			IfHaveData += NoRunSize[i][0] + 1;
		}
		else
		{
			IfHaveData++;
		}
		if (NoRunSize[i][2] != 0)
		{
			RunSize[IfHaveData] = NoRunSize[i][2];//+ NoRunSize[i][1]
		}
		i++;
	}
	//测试数据
	//for (int i = 0; i < 64; i++)
	//	cout << RunSize[i]<<" ";

}

//反之字形编码+量化
void ReZigZag(int RunSize[])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int k = zigzag_table[8 * i + j];
			ZigZag.at<double>(i, j) = RunSize[k];		//将数据存入8*8的Mat矩阵中
			ZigZag.at<double>(i, j) *= quantification[i][j];	//反量化
		}
	}
}

//反DCT变换
void ReDCT(cv::Mat &D_Mat, cv:: Mat &E_Mat)
{
	double pi = 3.141592657;
	cv::Mat C_Mat(8, 8, CV_64FC1);
	cv::Mat C_Mat_Inv(8, 8, CV_64FC1);
	cv::Mat CT_Mat(8, 8, CV_64FC1);
	cv::Mat CT_Mat_Inv(8, 8, CV_64FC1);

	for (int i = 0; i < C_Mat.rows; i++)
		C_Mat.at<double>(0, i) = sqrt(2.0 / (C_Mat.rows))*sqrt(1.0 / C_Mat.rows);
	for (int i = 1; i<C_Mat.rows; i++)
		for (int j = 0; j < C_Mat.cols; j++)
			C_Mat.at<double>(i, j) = (2.0 / (C_Mat.rows)) * cos(pi * i * (2 * j + 1) / (2 * C_Mat.rows));
	CT_Mat = C_Mat.t();
	invert(C_Mat, C_Mat_Inv);
	invert(CT_Mat, CT_Mat_Inv);
	E_Mat = C_Mat_Inv*D_Mat*CT_Mat_Inv;
}

