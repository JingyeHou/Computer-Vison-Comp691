#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include<opencv2/opencv.hpp>
#include "BayerToBGR.h"

using namespace cv;
using namespace std;

int main( int argc, char** argv ) {

    //part 1
    BayerToBGR change;

    Mat image;
    Mat result_image;
    Mat imageGreen;
    Mat imageRed;
    Mat imageBlue;
    Mat modifiedRed;
    Mat modifiedBlue;
    Mat partTwoResult;
    Mat imageOriginal;
    Mat imageTest;

    image = imread("/Users/houjingye/Desktop/pencils_mosaic.bmp", CV_LOAD_IMAGE_COLOR);
    imageOriginal = imread("/Users/houjingye/Desktop/pencils.jpg", CV_LOAD_IMAGE_COLOR);

    if (!image.data) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    vector<Mat> bgr;
    split(image, bgr);

    change.changeGreen(bgr[1]);
    imageGreen = bgr[1];

    change.changeRed(bgr[2]);
    imageRed = bgr[2];

    change.changeBlue(bgr[0]);
    imageBlue = bgr[0];

    float kernel_data0[9]={0.25,0.5,0.25,

                           0.5,   1, 0.5,

                           0.25,0.5,0.25};


    float kernel_data1[9]={   0,   0.25,     0,

                              0.25,    1,  0.25,

                              0,   0.25,     0};



    change.filter(kernel_data0, bgr[2]);
    change.filter(kernel_data0, bgr[0]);
    change.filter(kernel_data1, bgr[1]);

    merge(bgr, result_image);

    change.showNewPictures("firstPart", result_image);

    change.showNewPictures("Original Pic", imageOriginal);

    change.testFirstPart(imageOriginal, result_image, imageTest);

    //finish part 1

    //part 2

    change.modifiedColor(imageRed, imageGreen, modifiedRed);
    change.modifiedColor(imageBlue, imageGreen, modifiedBlue);

    bgr[2] = modifiedRed;
    bgr[0] = modifiedBlue;

    merge(bgr, partTwoResult);
    change.showNewPictures("secondPart ", partTwoResult);


    //finish part 2

    return 0;
}
