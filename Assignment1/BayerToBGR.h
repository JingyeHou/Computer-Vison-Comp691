//
// Created by 侯景业 on 2017-01-24.
//

#ifndef COMPUTER_VISION1_BAYERTOBGR_H
#define COMPUTER_VISION1_BAYERTOBGR_H
#pragma once

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;


class BayerToBGR {
private:
    int a;
    Mat image;
    Mat kernel;

public:

    BayerToBGR(int a, const Mat &image, const Mat &kernel);

    BayerToBGR();

    void changeGreen(Mat &image);   // transform a picture into a matrix that only has green pixels

    void changeRed(Mat &image);     // transform a picture into a matrix that only has red pixels

    void changeBlue(Mat &image);    // transform a picture into a matrix that only has blue pixels

    void description(Mat &image);   // help you to see the matrix of your image;

    void filter(float kernel_data[], Mat &image);   // filter2D

    void showNewPictures(String name, Mat &image);  // show a image in a small window

    void testFirstPart(Mat &image, Mat &image1, Mat &image2);   // to show a image that is a subtraction of original image and reconstructed image

    void modifiedColor(Mat &image1, Mat &image2, Mat &image3);  // a modified image

    int getA() const;

    void setA(int a);

    const Mat &getImage() const;

    void setImage(const Mat &image);

    const Mat &getKernel() const;

    void setKernel(const Mat &kernel);


};


#endif //COMPUTER_VISION1_BAYERTOBGR_H
