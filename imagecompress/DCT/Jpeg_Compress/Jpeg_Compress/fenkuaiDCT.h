#pragma once

#include <iostream>
#include "cv.h"
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;

void Block_DCT(Mat &src, Mat &dst);
void Quantification(Mat &dst, Mat &qua);