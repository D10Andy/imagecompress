#include "Tool.h"

using namespace std;

//二进制转十六进制
string BinToHex(const string &strBin)
{
	string strHex = { 0 };
	strHex.resize(4);
	char cCur = '0';

	int a = (strBin.size() % 4 == 0) ? strBin.size() / 4 : (strBin.size() / 4 + 1);//需要的位数
	for (int i = 0; i < a; i++)
	{
		int sum = 0;
		for (int j = 0; j < 4; j++)
		{
			int binsub = strBin.size() - 4 * i - j - 1;	//下标
			if (binsub >= 0)
			{
				sum += (strBin[binsub] - '0')*pow(2, j);//4*i+3-j
			}
		}
		if (sum  < 10)
		{
			cCur = sum + '0';
		}
		else
		{
			cCur = sum - 10 + 'A';
		}
		strHex[a - 1 - i] = cCur;
	}
	return strHex;
}


//string 转换为int
int mystoi(string mystring)
{
	int myint;
	stringstream ss;
	ss << mystring;
	ss >> hex >> myint;
	return myint;
}

int mystringtoint(string str,int strlength)
{
	int num = pow(2, strlength) - 1;
	int sum = 0;
	//string 转换成十进制正数
	for (int i = 0; i < strlength; i++)
	{
		sum = sum + pow(2, i) * (str[strlength - i - 1]- '0');
	}
	sum = sum - num;
	return sum;
}