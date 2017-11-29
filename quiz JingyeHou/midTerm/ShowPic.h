//
// Created by 侯景业 on 2017-02-27.
//

#ifndef MIDTERM_SHOWPIC_H
#define MIDTERM_SHOWPIC_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include<opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

class ShowPic {
public:
    void showPic(String name, Mat &image);
};


#endif //MIDTERM_SHOWPIC_H
