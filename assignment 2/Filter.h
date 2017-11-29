//
// Created by 侯景业 on 2017-02-07.
//

#ifndef ASSIGNMENT2_FILTERING_H
#define ASSIGNMENT2_FILTERING_H
#include <iostream>
#include <opencv2/opencv.hpp>
#include "GuassianKernel.h"

using namespace cv;

class Filter {
public:
    void filtering(Mat const &input_image, Mat const &kernel, Mat &output_image);
};


#endif //ASSIGNMENT2_FILTERING_H
