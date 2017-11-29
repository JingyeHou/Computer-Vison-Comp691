#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include<opencv2/opencv.hpp>
#include "Tools.h"
#include "GuassianKernel.h"
#include "Filter.h"

using namespace cv;
using namespace std;

int main() {

    Mat lowImage;
    Mat highImage;
    Mat lowResult_image;
    Mat highResult_image;
    Mat hybrit_image;
    Mat show_high;
    Mat transform_Image;
    Mat transform;
    Mat sobel_high;
    Mat sobel_high2;
    Mat sobel_out;
    Mat lap_out;
    Tools tools;


    lowImage = imread("/Users/houjingye/Desktop/dog.bmp", CV_LOAD_IMAGE_COLOR);
    highImage = imread("/Users/houjingye/Desktop/cat.bmp", CV_LOAD_IMAGE_COLOR);

    if (!lowImage.data) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    if (!highImage.data) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

//part one

// deal with high frequent image
    GaussianBlur(highImage, transform_Image, Size(33, 33), 0, 0, BORDER_DEFAULT);
    show_high = highImage - transform_Image;
    tools.showPic("high1", show_high);
    tools.addGray(show_high, show_high);
    tools.showPic("high2", show_high);
    highResult_image = highImage - transform_Image;

//deal with low frequent image
    GaussianBlur(lowImage, lowResult_image, Size(33, 33), 0, 0, BORDER_DEFAULT);
    tools.showPic("low", lowResult_image);

//show hybrit image
    hybrit_image = lowResult_image + highResult_image;
    tools.showPic("hybrit", hybrit_image);

//part two

    GuassianKernel kernel;
    Filter filter;

//deal with high frequent image
    Mat Kernel(21, 21, CV_64F);
    Mat out_Pic_high(highImage.rows, highImage.cols, highImage.type());
    kernel.guassian(Kernel.rows, Kernel.cols, 2001, Kernel);
    filter.filtering(highImage, Kernel, out_Pic_high);
    show_high = highImage - out_Pic_high;
    tools.showPic("show_high1", show_high);
    tools.addGray(show_high, show_high);
    tools.showPic("show_high2", show_high);

//deal with low frequent image
    Mat Kernel2(21, 21, CV_64F);
    Mat out_pic_low(lowImage.rows, lowImage.cols, lowImage.type());
    kernel.guassian(Kernel2.rows, Kernel2.cols, 2001, Kernel2);
    filter.filtering(lowImage, Kernel2, out_pic_low);
    tools.showPic("show low", out_pic_low);

//make a hybrite image
    highResult_image = highImage - out_Pic_high;
    addWeighted(highResult_image, 0.5, out_pic_low, 0.5, 0.0, hybrit_image);
    tools.showPic("handmade Gaussian", hybrit_image);

//part three

//sobel


//    Sobel(highImage, highResult_image, -1, 1, 0, 3 );
//    tools.showPic("sobel", highResult_image);

//mage a horizantal direction kernel
    float kernel_data0[9]={ -1, 0, 1,

                            -2, 0, 2,

                            -1, 0, 1};



    Mat kernel3 = Mat(3,3, CV_32F, kernel_data0);
    filter2D(highImage, sobel_high, highImage.depth(), kernel3);

//make a vertical direction kernel
    float kernel_data1[9]={ -1,   -2,    -1,

                              0,    0,   0,

                            1,    2,     1};
    Mat kernel4 = Mat(3,3,CV_32F,kernel_data1);
    Mat hi = highImage;
    filter2D(highImage, sobel_high2, highImage.depth(), kernel4);

// make a high frequent image
    addWeighted(sobel_high, 0.5, sobel_high2, 0.5, 0.0, sobel_out);
    tools.showPic("sobel", sobel_out);



//LOG
//    Laplacian(transform_Image, highResult_image, -1, 3);
//    tools.showPic("Laplacian", highResult_image);

//gausianfilter
    GaussianBlur(highImage, transform_Image, Size(3, 3), 0, 0, BORDER_DEFAULT);

//laplasion filter
    float kernel_data2[9]={ 1, 1,  1,

                            1, -8,  1,

                            1,  1,  1};

    Mat kernel2 = Mat(3,3,CV_32F,kernel_data2);

//make a high frequent image
    filter2D(transform_Image, lap_out, transform_Image.depth(), kernel2);
    tools.showPic("lap", lap_out);

//DOG

    GaussianBlur(highImage, transform_Image, Size(33, 33), 1, 0, BORDER_DEFAULT);
    GaussianBlur(highImage, transform, Size(33, 33), 100, 0, BORDER_DEFAULT);
    highResult_image = transform_Image - transform;
    tools.showPic("DOG", highResult_image);

}