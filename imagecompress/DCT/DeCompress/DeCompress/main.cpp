#include"Tool.h"
#include "main.h"
#include "Huffman.h";

using namespace std;
using namespace cv;

ifstream fin;

void main()
{
	ifstream in("imgdata.txt");
	in.seekg(0, ios::end); //�����ļ�ָ�뵽�ļ�����β��  
	streampos ps = in.tellg(); //��ȡ�ļ�ָ���λ��  
	cout << "File size: " << ps << endl;
	cout << "=" << ps / 1024 << "KB";
	in.close(); //�ر��ļ��� 
	readcompressdata();
	cvWaitKey();
	cin.get();
}