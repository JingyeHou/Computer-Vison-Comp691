//
// Created by 侯景业 on 2017-02-06.
//

#ifndef ASSIGNMENT2_GUASSIANKERNEL_H
#define ASSIGNMENT2_GUASSIANKERNEL_H
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <cv.h>
#include <highgui.h>
#include <algorithm>
#include <opencv2/highgui/highgui.hpp>

class GuassianKernel {
public:
    void guassian(int sizex, int sizey, double sigma, cv::Mat &kernel);
};


#endif //ASSIGNMENT2_GUASSIANKERNEL_H
