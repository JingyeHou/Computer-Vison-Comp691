#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "HarisConer.h"
#include "Tools.h"
#include "highgui.h"
#include "Descriptor.h"
#include "Matcher.h"


using namespace cv;
using namespace std;

Mat src;
Mat src2;
Mat src3;
Mat src4;
Mat src5;
Mat dst;
Mat dst2;
Mat dst3;
Mat dst4;
Mat dst5;
Mat dst6;
Mat dst7;
Mat dst8;
vector<cv::Point2f> point1;
vector<cv::Point2f> point2;
vector<cv::Point2f> point3;
vector<cv::Point2f> point4;
vector<cv::Point2f> point5;
vector<cv::Point2f> point6;
vector<cv::Point2f> point7;
vector<cv::Point2f> point8;
Tools tools;
const int threshold_max = 2500;
int n = 3;
int thresh = 1000;
HarisConer harisConer;




void on_trackbar( int, void*);

int main() {

//    src = imread("/Users/houjingye/Desktop/img2.ppm", CV_LOAD_IMAGE_COLOR);
//    src2 = imread("/Users/houjingye/Desktop/img1.ppm", CV_LOAD_IMAGE_COLOR);

//    src = imread("/Users/houjingye/Desktop/630.png", CV_LOAD_IMAGE_COLOR);
//    src2 = imread("/Users/houjingye/Desktop/6301.png", CV_LOAD_IMAGE_COLOR);


//    src = imread("/Users/houjingye/Desktop/Hanging1.png", CV_LOAD_IMAGE_COLOR);
//    src2 = imread("/Users/houjingye/Desktop/Hanging2.png", CV_LOAD_IMAGE_COLOR);

//    src = imread("/Users/houjingye/Desktop/Yosemite1.jpg", CV_LOAD_IMAGE_COLOR);
//    src2 = imread("/Users/houjingye/Desktop/Yosemite2.jpg", CV_LOAD_IMAGE_COLOR);

    //first Iteration
    src = imread("/Users/houjingye/Desktop/Rainier1.png", CV_LOAD_IMAGE_COLOR);
    src2 = imread("/Users/houjingye/Desktop/Rainier2.png", CV_LOAD_IMAGE_COLOR);

    Mat stitchedImage1;



    if ((!src.data)||(!src2.data)) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

//    namedWindow("Linear Blend", 1);

//    Mat gray;
//    cvtColor(src, gray, CV_BGR2GRAY);
//    cout << gray << endl;
//    cout << "=========" << endl;
//    cout << src << endl;


//    cvNamedWindow("Contours");
//    createTrackbar("Threshold", "Contours", &thresh, threshold_max, on_trackbar );
//    createTrackbar("size", "Contours", &n, 20, on_trackbar );


//    harisConer.detector(src2, dst2, thresh, point2, n);
//    harisConer.detector(src, dst, thresh, point1, n);
    harisConer.detector(src, dst, 0.05, point1);
    harisConer.detector(src2, dst2, 0.05, point2);


    vector<KeyPoint> keyPoint1,keyPoint2;
    KeyPoint::convert(point1,keyPoint1,1,1,0,-1);
    KeyPoint::convert(point2,keyPoint2,1,1,0,-1);

//    create descriptor
    Mat descriptors_1, descriptors_2;
    Descriptor Descriptor;
    Descriptor.descriptor(src,keyPoint1,descriptors_1);
    Descriptor.descriptor(src2,keyPoint2,descriptors_2);

//    cout << descriptors_1 << endl;

// Matching descriptor vectors with a brute force matcher

    Matcher matcher(descriptors_1, descriptors_2);
    matcher.run(src, src2, keyPoint1, keyPoint2,stitchedImage1);
    tools.showPic("1", stitchedImage1);

    //secondIteration
    src3 = imread("/Users/houjingye/Desktop/Rainier3.png", CV_LOAD_IMAGE_COLOR);
    if (!src3.data) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }
    harisConer.detector(src3, dst3, 0.05, point3);
    harisConer.detector(stitchedImage1, dst4, 0.05, point4);

    vector<KeyPoint> keyPoint3,keyPoint4;
    KeyPoint::convert(point3,keyPoint3,1,1,0,-1);
    KeyPoint::convert(point4,keyPoint4,1,1,0,-1);

    Mat descriptors_3, descriptors_4;
    Descriptor.descriptor(src3,keyPoint3,descriptors_3);
    Descriptor.descriptor(stitchedImage1,keyPoint4,descriptors_4);

    Mat stitchedImage2;

    Matcher matcher2(descriptors_3, descriptors_4);
    matcher2.run(src3, stitchedImage1, keyPoint3, keyPoint4,stitchedImage2);

    tools.showPic("2", stitchedImage2);

    //thirdIteration

    src4 = imread("/Users/houjingye/Desktop/Rainier4.png", CV_LOAD_IMAGE_COLOR);
    if (!src4.data) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }
    harisConer.detector(src4, dst5, 0.05, point5);
    harisConer.detector(stitchedImage2, dst6, 0.05, point6);

    vector<KeyPoint> keyPoint5,keyPoint6;
    KeyPoint::convert(point5,keyPoint5,1,1,0,-1);
    KeyPoint::convert(point6,keyPoint6,1,1,0,-1);

    Mat descriptors_5, descriptors_6;
    Descriptor.descriptor(src4,keyPoint5,descriptors_5);
    Descriptor.descriptor(stitchedImage2,keyPoint6,descriptors_6);

    Mat stitchedImage3;

    Matcher matcher3(descriptors_5, descriptors_6);
    matcher3.run(src4, stitchedImage2, keyPoint5, keyPoint6,stitchedImage3);

    tools.showPic("3", stitchedImage3);

    //forthIteration

    src5 = imread("/Users/houjingye/Desktop/Rainier5.png", CV_LOAD_IMAGE_COLOR);
    if (!src5.data) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }
    harisConer.detector(src5, dst7, 0.05, point7);
    harisConer.detector(stitchedImage3, dst8, 0.05, point8);

    vector<KeyPoint> keyPoint7,keyPoint8;
    KeyPoint::convert(point7,keyPoint7,1,1,0,-1);
    KeyPoint::convert(point8,keyPoint8,1,1,0,-1);

    Mat descriptors_7, descriptors_8;
    Descriptor.descriptor(src5,keyPoint7,descriptors_7);
    Descriptor.descriptor(stitchedImage3,keyPoint8,descriptors_8);

    Mat stitchedImage4;

    Matcher matcher4(descriptors_7, descriptors_8);
    matcher4.run(src5, stitchedImage3, keyPoint7, keyPoint8,stitchedImage4);
    tools.showPic("fianl", stitchedImage4);
}




