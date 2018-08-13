#pragma once

#include <iostream>
#include "cv.h"
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

void ReDCT(cv::Mat &D_Mat, cv::Mat &E_Mat);
void Fqua(Mat &A);
void FDCT(Mat &qua, Mat &F_Mat);