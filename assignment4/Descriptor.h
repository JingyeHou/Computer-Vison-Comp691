//
// Created by 侯景业 on 2017-03-06.
//

#ifndef ASSIGNMENT4_DESCRIPTOR_H
#define ASSIGNMENT4_DESCRIPTOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "GaussianKernel.h"
#include <math.h>




class Descriptor {
public:
    void getPatch(Mat& src, KeyPoint keyPoint, Mat& patch);



    Mat getDescriptor(Mat& src, KeyPoint keyPoint);

    void descriptor(Mat& img,
                    CV_OUT CV_IN_OUT vector<KeyPoint>& keypoints,
                    Mat &descriptors);

    void getTheta(Mat& mag, Mat& dir, Mat& thetas);

    int Theta(Mat& patch_mag, Mat& patch_dir);
};



#endif //ASSIGNMENT4_DESCRIPTOR_H
