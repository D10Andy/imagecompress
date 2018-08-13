#include"Tool.h"
#include "main.h"
#include "Huffman.h";

using namespace std;
using namespace cv;

ifstream fin;

void main()
{
	ifstream in("imgdata.txt");
	in.seekg(0, ios::end); //设置文件指针到文件流的尾部  
	streampos ps = in.tellg(); //读取文件指针的位置  
	cout << "File size: " << ps << endl;
	cout << "=" << ps / 1024 << "KB";
	in.close(); //关闭文件流 
	readcompressdata();
	cvWaitKey();
	cin.get();
}