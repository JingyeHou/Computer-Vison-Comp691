//
// Created by 侯景业 on 2017-01-24.
//

#include "BayerToBGR.h"

using namespace cv;
using namespace std;

BayerToBGR::BayerToBGR(int a, const Mat &image, const Mat &kernel) : a(a), image(image), kernel(kernel) {}

BayerToBGR::BayerToBGR() {}

void BayerToBGR::changeRed(Mat &image) {
//    for (int i = 0; i < image.rows; i++) {
//        if (i % 2 == 0) {
//            for (int j = 0; j < image.cols; j++) {
//                image.at<uchar>(i, j) = 0;
//                j++;
//            }
//        } else {
//            for (int j = 0; j < image.cols; j++) {
//                image.at<uchar>(i, j) = 0;
//            }
//        }
//    }


    for (int y = 0; y < (image.rows); y++) {
        uchar *ptr = image.ptr(y);
        for (int x = 0; x < image.cols; x++) {
            if (y % 2 != 0 || x % 2 != 0) {

                ptr[x] = 0;
            }

        }

    }
}

void BayerToBGR::changeBlue(Mat &image) {
//    for (int i = 0; i < image.rows; i++){
//        if (i % 2 == 0) {
//            for(int j = 0; j < image.cols; j++) {
//                image.at<uchar>(i, j) = 0;
//            }
//        } else {
//            for(int j = 1; j < image.cols; j++) {
//                image.at<uchar>(i, j) = 0;
//                j++;
//            }
//        }
//    }

    for(int y =0;y< (image.rows);y++){
        uchar* ptr = image.ptr(y);
        for(int x =0;x<image.cols;x++){
            if(y%2==0||x%2==0){
                ptr[x]=0;
            }

        }
    }

}

void BayerToBGR::changeGreen(Mat &image) {
//    for (int i = 0; i < image.rows; i++) {
//        if (i % 2 == 1) {
//            for (int j = 0; j < image.cols; j++) {
//                image.at<uchar>(i, j) = 0;
//                j++;
//            }
//        }
//
//        if (i % 2 == 0) {
//            for (int j = 1; j < image.cols; j++) {
//                image.at<uchar>(i, j) = 0;
//                j++;
//            }
//        }
//    }


    for (int y = 0; y < (image.rows); y++) {
        uchar *ptr = image.ptr(y);
        for (int x = 0; x < image.cols; x++) {
            if ((y % 2 != 0 && x % 2 != 0) || (y % 2 == 0 && x % 2 == 0)) {
                ptr[x] = 0;
            }

        }

    }
}

void BayerToBGR::testFirstPart(Mat &image, Mat &image1, Mat &image2){
    image2 = image - image1 + image1 - image;
    namedWindow("Test" , WINDOW_AUTOSIZE);

    imshow("Test", image2);

    waitKey(0);
}

void BayerToBGR::showNewPictures(String name, Mat &image) {
    namedWindow( name , WINDOW_AUTOSIZE);

    imshow( name, image);

    waitKey(0);
}

void BayerToBGR::description(Mat &image){
    for(int i = 0; i < image.rows; i++)
    {
        uchar* Mi = image.ptr(i);
        for(int j = 0; j < image.cols; j++) {
            cout << (int) (Mi[j]) << " ";
        }
        cout << " " << "\n";
    }
}

void BayerToBGR::filter(float kernel_data[], Mat &image){
    Mat kernel =cv::Mat(3,3,CV_32F,kernel_data);
    filter2D(image, image, image.depth(), kernel);
}

void BayerToBGR::modifiedColor(Mat &image1, Mat &image2, Mat &image3){
    Mat afterSub1 = image1 - image2;
    Mat afterSub2 = image2 - image1;
    medianBlur(afterSub1, afterSub1, 3);
    medianBlur(afterSub2, afterSub2, 3);
    image3 = afterSub1 + image2 - afterSub2;
}

int BayerToBGR::getA() const {
    return a;
}

void BayerToBGR::setA(int a) {
    BayerToBGR::a = a;
}

const Mat &BayerToBGR::getImage() const {
    return image;
}

void BayerToBGR::setImage(const Mat &image) {
    BayerToBGR::image = image;
}

const Mat &BayerToBGR::getKernel() const {
    return kernel;
}

void BayerToBGR::setKernel(const Mat &kernel) {
    BayerToBGR::kernel = kernel;
}






