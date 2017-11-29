//
// Created by 侯景业 on 2017-03-06.
//

#ifndef ASSIGNMENT4_HARISCONER_H
#define ASSIGNMENT4_HARISCONER_H


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "GaussianKernel.h"
#include <math.h>

using namespace cv;
using namespace std;

class HarisConer {
public:
    void detector(Mat& src, Mat& imgDst, double qualityLevel, vector<cv::Point2f> &points);
};


//class HarisConer {
//private:
//public:
//    void detector(Mat& src, Mat& imgDst, int threshold, vector<cv::Point2f> &points, int n);
//
//    void Threshold(Mat& img, int threshold);
//
//    void dialect(Mat& scr, Mat& dst, int n);
//
//    void compare(Mat& src1, Mat& src2, Mat& dst);
//
//    int getTheta(Mat& mag, Mat& dir);
//};


#endif //ASSIGNMENT4_HARISCONER_H
