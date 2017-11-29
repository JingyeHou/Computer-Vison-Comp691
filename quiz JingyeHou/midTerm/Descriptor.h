//
// Created by 侯景业 on 2017-02-26.
//

#ifndef MIDTERM_DESCRIPTOR_H
#define MIDTERM_DESCRIPTOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "GaussianKernel.h"
#include <math.h>

class Descriptor {
private:

public:
    Descriptor();


    void descriptor(Mat img,
                    CV_OUT CV_IN_OUT vector<KeyPoint>& keypoints,
                    Mat &descriptors);

    //get 128's orientations
    Mat getDescriptor(Mat src, KeyPoint keyPoint);
};


#endif //MIDTERM_DESCRIPTOR_H
