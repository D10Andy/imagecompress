#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "cv.h"


void readcompressdata();
void ExtrHuffDatta(std::vector<int> NoHuffData, int *RunSize);
void ReZigZag(int RunSize[]);
void ReDCT(cv::Mat &D_Mat, cv::Mat &E_Mat);

typedef struct
{
	char DcCode[16] = { 0 };
	char DcActual[16] = { 0 };

}DCStruct;
typedef struct
{
	char AcCode[16] = { 0 };
	char AcActual[16] = { 0 };
}ACStruct;