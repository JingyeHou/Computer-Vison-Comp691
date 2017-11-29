//
// Created by 侯景业 on 2017-02-26.
//

#include "HarrisConer.h"

void HarrisConer::detector(Mat& src, Mat& imgDst, double qualityLevel, vector<cv::Point2f> &points) {
    Mat Dx, Dy;
    Mat DxDy,Dx2, Dy2;
    Mat dilated;
    Mat localMax;
    Mat cornerMap;
    Mat gray;
    Mat cornerTh;

    GaussianKernel gaussianKernel;

    if (src.channels() == 3)
    {
        cvtColor(src, gray, CV_BGR2GRAY);
    }
    else
    {
        gray = src.clone();
    }
    gray.convertTo(gray, CV_64F);

    float kernel_data0[9]={ -1, 0, 1,

                            -1, 0, 1,

                            -1, 0, 1};


    Mat kernel3 = Mat(3,3, CV_32F, kernel_data0);
    filter2D(gray, Dx, gray.depth(), kernel3);
    //get Ix by using sobel

    float kernel_data1[9]={ -1, -1, -1,

                            0,   0,  0,

                            1,   1,  1};
    Mat kernel4 = Mat(3,3,CV_32F,kernel_data1);
    filter2D(gray, Dy, gray.depth(), kernel4);
    //get Iy by using sobel

    DxDy = Dx.mul(Dy);
    Dy2 = Dy.mul(Dy);
    Dx2 = Dx.mul(Dx);
    //get IxIy Ix^2 Iy^2

    Mat Kernel(3, 3, CV_64F);
    gaussianKernel.guassian(3, 3, 1, Kernel);

    filter2D(DxDy, DxDy, DxDy.depth(), Kernel);
    filter2D(Dx2, Dx2, Dx2.depth(), Kernel);
    filter2D(Dy2, Dy2, Dy2.depth(), Kernel);
    //gausian blur to smooth IxIy Ix^2 Iy^2

   Mat cornerStrength(gray.size(), gray.type());
    for (int i = 0; i < gray.rows; i++)
    {
        for (int j = 0; j < gray.cols; j++)
        {
            double det_m = Dx2.at<double>(i,j) * Dy2.at<double>(i,j) - DxDy.at<double>(i,j) * DxDy.at<double>(i,j);
            double trace_m = Dx2.at<double>(i,j) + Dy2.at<double>(i,j);
            cornerStrength.at<double>(i,j) = det_m/trace_m;
        }
    }
    //get cornerStrength

    double maxStrength;
    minMaxLoc(cornerStrength, NULL, &maxStrength, NULL, NULL);
    dilate(cornerStrength, dilated, Mat());
    compare(cornerStrength, dilated, localMax, CMP_EQ);

    double thresh = qualityLevel * maxStrength;
    cornerMap = cornerStrength > thresh;
    bitwise_and(cornerMap, localMax, cornerMap);

    imgDst = cornerMap.clone();


    for( int y = 0; y < cornerMap.rows; y++ ) {
        const uchar* rowPtr = cornerMap.ptr<uchar>(y);
        for( int x = 0; x < cornerMap.cols; x++ ) {
            if (rowPtr[x]) {
                points.push_back(cv::Point2f(x,y));
            }
        }
    }
    //get interests Points

    Mat_<uchar>::const_iterator it = imgDst.begin<uchar>();
    Mat_<uchar>::const_iterator itd = imgDst.end<uchar>();
    for (int i = 0; it != itd; it++, i++)
    {
        if (*it)
            circle(src, Point(i%src.cols, i / src.cols), 3, Scalar(0, 255, 0), 1);
    }
    //show interests Points

}