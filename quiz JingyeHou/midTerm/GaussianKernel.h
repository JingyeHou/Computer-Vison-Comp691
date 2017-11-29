//
// Created by 侯景业 on 2017-02-26.
//

#ifndef MIDTERM_GAUSSIANKERNEL_H
#define MIDTERM_GAUSSIANKERNEL_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <cv.h>
#include <highgui.h>
#include <algorithm>
#include <opencv2/highgui/highgui.hpp>
#include "GaussianKernel.h"

using namespace cv;
using namespace std;

class GaussianKernel {
public:
    void guassian(int sizex, int sizey, double sigma, Mat &kernel);
};


#endif //MIDTERM_GAUSSIANKERNEL_H
