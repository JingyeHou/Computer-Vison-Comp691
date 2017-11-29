//
// Created by 侯景业 on 2017-02-26.
//

#ifndef MIDTERM_HARRISCONER_H
#define MIDTERM_HARRISCONER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "GaussianKernel.h"
#include <math.h>

using namespace cv;
using namespace std;

class HarrisConer {
public:
    void detector(Mat& src, Mat& imgDst, double qualityLevel, vector<cv::Point2f> &points);
};


#endif //MIDTERM_HARRISCONER_H
