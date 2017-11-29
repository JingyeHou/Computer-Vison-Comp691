//
// Created by 侯景业 on 2017-03-06.
//

#include "HarisConer.h"
#include "Tools.h"


void HarisConer::detector(Mat& src, Mat& imgDst, double qualityLevel, vector<cv::Point2f> &points) {
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
    gaussianKernel.guassian(3, 3, 1 , Kernel);

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
    Tools tools;

    dilate(cornerStrength, dilated, Mat());
//    tools.showPic("1", cornerStrength);

    compare(cornerStrength, dilated, localMax, CMP_EQ);
//    tools.showPic("2", localMax);

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

//    Mat_<uchar>::const_iterator it = imgDst.begin<uchar>();
//    Mat_<uchar>::const_iterator itd = imgDst.end<uchar>();
//    for (int i = 0; it != itd; it++, i++)
//    {
//        if (*it)
//            circle(src, Point(i%src.cols, i / src.cols), 3, Scalar(0, 255, 0), 1);
//    }
    //show interests Points

}


//    void HarisConer::detector(Mat& src, Mat& imgDst, int threshold, vector<cv::Point2f> &points, int n) {
//    Mat Dx, Dy;
//    Mat DxDy,Dx2, Dy2;
//    Mat dilated;
//    Mat localMax;
//    Mat cornerMap;
//    Mat gray;
//
//    GaussianKernel gaussianKernel;
//
//    if (src.channels() == 3)
//    {
//        cvtColor(src, gray, CV_BGR2GRAY);
//    }
//    else
//    {
//        gray = src.clone();
//    }
//    gray.convertTo(gray, CV_64F);
//
//    float kernel_data0[9]={ -1, 0, 1,
//
//                            -1, 0, 1,
//
//                            -1, 0, 1};
//
//
//
//    Mat kernel3 = Mat(3,3, CV_32F, kernel_data0);
//    filter2D(gray, Dx, gray.depth(), kernel3);
//
//    float kernel_data1[9]={ -1, -1, -1,
//
//                            0,   0,  0,
//
//                            1,   1,  1};
//    Mat kernel4 = Mat(3,3,CV_32F,kernel_data1);
//    filter2D(gray, Dy, gray.depth(), kernel4);
//
//    DxDy = Dx.mul(Dy);
//    Dy2 = Dy.mul(Dy);
//    Dx2 = Dx.mul(Dx);
//
//    Mat Kernel(3, 3, CV_64F);
//    gaussianKernel.guassian(3, 3, 1, Kernel);
//
//    filter2D(DxDy, DxDy, DxDy.depth(), Kernel);
//    filter2D(Dx2, Dx2, Dx2.depth(), Kernel);
//    filter2D(Dy2, Dy2, Dy2.depth(), Kernel);
//
//    Mat cornerStrength(gray.size(), gray.type());
//    for (int i = 0; i < gray.rows; i++)
//    {
//        for (int j = 0; j < gray.cols; j++)
//        {
//            double det_m = Dx2.at<double>(i,j) * Dy2.at<double>(i,j) - DxDy.at<double>(i,j) * DxDy.at<double>(i,j);
//            double trace_m = Dx2.at<double>(i,j) + Dy2.at<double>(i,j);
//            cornerStrength.at<double>(i,j) = det_m/trace_m;
//        }
//    }
//
//
//    Threshold(cornerStrength, threshold);
//
//    dialect(cornerStrength, dilated, n);
//
//    compare(cornerStrength, dilated, cornerMap);
//    imgDst = cornerMap.clone();
//
//    for( int y = 0; y < cornerMap.rows; y++ ) {
//        const uchar* rowPtr = cornerMap.ptr<uchar>(y);
//        for( int x = 0; x < cornerMap.cols; x++ ) {
//            if (rowPtr[x]) {
//                points.push_back(cv::Point2f(x,y));
//            }
//        }
//    }
//
////    Mat_<uchar>::const_iterator it = imgDst.begin<uchar>();
////    Mat_<uchar>::const_iterator itd = imgDst.end<uchar>();
////    for (int i = 0; it != itd; it++, i++)
////    {
////        if (*it)
////            circle(src, Point(i%src.cols, i / src.cols), 3, Scalar(0, 255, 0), 1);
////    }
//}
//
//
//void HarisConer::compare(Mat &src1, Mat &src2, Mat &dst) {
//    dst = Mat(src1.rows, src1.cols, src1.type());
//
//    for(int i = 0; i < src1.rows; i++) {
//        for(int j = 0; j < src1.cols; j++) {
//            if (src1.at<double>(i, j) == src2.at<double>(i, j)) {
//                dst.at<double>(i, j) = src1.at<double>(i, j);
//            } else {
//                dst.at<double>(i, j) = 0;
//            }
//        }
//    }
//}
//
//
//
//void HarisConer::dialect(Mat &scr, Mat &dst, int n) {
//    int size = 2 * n + 1;
//    dst = Mat(scr.rows, scr.cols, scr.type());
//    int left = 0;
//    int top = 0;
//    double temp = 0;
//    int r = scr.rows / size;
//    int c = scr.cols / size;
//    for (int i = 0; i < r; i++) {
//        int beginPoint_row = top + size * i;
//        for (int j = 0; j < c; j++) {
//            int beginPoint_col = left + size * j;
//            for (int row = 0; row < size; row++) {
//                for (int col = 0; col < size; col++) {
//                    if(temp < scr.at<double>(row + beginPoint_row, col + beginPoint_col)) {
//                        temp = scr.at<double>(row + beginPoint_row, col + beginPoint_col);
//                    }
//                }
//            }
//            for (int row = 0; row < size; row++) {
//                for (int col = 0; col < size; col++) {
//                    dst.at<double>(row + beginPoint_row, col + beginPoint_col) = temp;
//                }
//            }
//            temp = 0;
//        }
//    }
//}
//
//void HarisConer::Threshold(Mat &img, int threshold) {
//    for(int i = 0; i < img.rows; i++) {
//        for (int j = 0; j < img.cols; j++) {
//            if (img.at<double>(i, j) < threshold) {
//                img.at<double>(i, j) = 0;
//            }
//        }
//    }
//}
//
//int HarisConer::getTheta(Mat &mag, Mat &dir) {
//    int theta;
//    Mat orientation = Mat::zeros(1, 36, CV_32FC1);
//    for(int i = 0; i < dir.rows; i++) {
//        for(int j = 0; j < dir.cols; j++) {
//            int temp = int(dir.at<float>(i, j) / 10);
//            orientation.at<float>(0, temp)
//                    += mag.at<float>(i, j);
//        }
//    }
//    int minkey = 0;
//    float temp = -1;
//        for(int col = 0 ;col < 36;col++) {
//            if (temp < orientation.at<float>(0, col)) {
//                temp = orientation.at<float>(0, col);
//                minkey = col;
//            }
//        }
//    theta = 10 * minkey;
//    return 0;
//}
//
//
