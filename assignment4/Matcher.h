//
// Created by 侯景业 on 2017-03-06.
//

#ifndef ASSIGNMENT4_MATCHER_H
#define ASSIGNMENT4_MATCHER_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <cv.h>
#include <highgui.h>
#include <algorithm>
#include <opencv2/highgui/highgui.hpp>
#include "GaussianKernel.h"
#include <algorithm>
#include <random>

using namespace cv;
using namespace std;


class Matcher {
private:
    float ssd;
    Mat src1;
    Mat Src2;

public:
    Matcher(const Mat &src1, const Mat &Src2);

    void run(Mat& image1, Mat& image2, vector<KeyPoint>& keypoints1, vector<KeyPoint>& keypoints2, Mat& stitch);

    float Ssd(int r1, int r2);

    void match(vector<DMatch> &matches);

    void project(float x1, float y1, Mat& H, float& x2, float& y2);

    void computeInlierCount(Mat& H, vector<DMatch> &matches, int& numMatches, float inlierThrehold, vector<KeyPoint>& keypoint1, vector<KeyPoint>& keypoint2);

    void findAllInlier(Mat& H, vector<DMatch> &matches, vector<DMatch> &matches2, float inlierThrehold, vector<KeyPoint>& keypoint1, vector<KeyPoint>& keypoint2);

    void RANAC(vector<DMatch> &matches, int& numMatches, int numIterations, vector<KeyPoint>& keypoint1, vector<KeyPoint>& keypoint2, Mat &hom, Mat &homlnv, Mat &image1Display,
               Mat &image2Display);

    void stitch(Mat& image1, Mat& image2, Mat& hom, Mat& homInv, Mat& stitchedImage, Mat& stitch);

    float getSsd() const;

    void setSsd(float ssd);

    const Mat &getSrc1() const;

    void setSrc1(const Mat &src1);

    const Mat &getSrc2() const;

    void setSrc2(const Mat &Src2);

};



#endif //ASSIGNMENT4_MATCHER_H
