//
// Created by 侯景业 on 2017-02-26.
//

#ifndef MIDTERM_MATCHER_H
#define MIDTERM_MATCHER_H

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


class Matcher {
private:
    float ssd;
    Mat src1;
    Mat Src2;

public:
    Matcher(const Mat &src1, const Mat &Src2);

    void run(Mat& image1, Mat& image2, vector<KeyPoint>& keypoints1, vector<KeyPoint>& keypoints2);

    float Ssd(int r1, int r2);

    void match(vector<DMatch> &matches);

    float getSsd() const;

    void setSsd(float ssd);

    const Mat &getSrc1() const;

    void setSrc1(const Mat &src1);

    const Mat &getSrc2() const;

    void setSrc2(const Mat &Src2);
};


#endif //MIDTERM_MATCHER_H
