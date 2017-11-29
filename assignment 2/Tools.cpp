//
// Created by 侯景业 on 2017-02-07.
//

#include "Tools.h"

void Tools::showPic(String name, Mat &image) {
    namedWindow( name , WINDOW_AUTOSIZE);

    imshow( name, image);

    waitKey(0);
}


void Tools::addGray(Mat &image, Mat &output) {
    Mat bgr[3];
    split(image, bgr);
    for (int i = 0; i < bgr[0].rows; i++) {
        for (int j = 0; j < bgr[0].cols; j++) {
            bgr[0].at<uchar>(i, j) =  bgr[0].at<uchar>(i, j) + 128;
        }
    }

    for (int i = 0; i < bgr[1].rows; i++) {
        for (int j = 0; j < bgr[1].cols; j++) {
            bgr[1].at<uchar>(i, j) =  bgr[1].at<uchar>(i, j) + 128;
        }
    }

    for (int i = 0; i < bgr[2].rows; i++) {
        for (int j = 0; j < bgr[0].cols; j++) {
            bgr[2].at<uchar>(i, j) =  bgr[2].at<uchar>(i, j) + 128;
        }
    }
    merge(bgr, 3,  output);
}


