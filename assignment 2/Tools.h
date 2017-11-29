//
// Created by 侯景业 on 2017-02-07.
//

#ifndef ASSIGNMENT2_TOOLS_H
#define ASSIGNMENT2_TOOLS_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include<opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "Tools.h"

using namespace std;
using namespace cv;


class Tools {
public:
    void showPic(String name, Mat &image);

    void addGray(Mat &image,  Mat &output);

};


#endif //ASSIGNMENT2_TOOLS_H
