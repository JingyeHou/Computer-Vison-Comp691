//
// Created by 侯景业 on 2017-02-07.
//

#include "Filter.h"
using namespace std;

void Filter::filtering(Mat const &input_image, Mat const &kernel, Mat &out_pic) {
    Mat image;
    int top = (kernel.rows - 1) / 2;
    int bottom = top;
    int left = (kernel.cols - 1) / 2;
    int right = left;


    copyMakeBorder(input_image, image , top, bottom, left, right, BORDER_CONSTANT);

    int num = image.channels();

    vector<Mat> bgr;
    vector<Mat> input_bgr;
    split(image, input_bgr);

    split(out_pic, bgr);
        for (int o = 0; o < num; o++) {
            for (int i = 0; i < out_pic.rows; i++) {
                for (int j = 0; j < out_pic.cols; j++) {
                    double total = 0;
                    for (int n = 0; n < kernel.rows; n++) {
                        for (int m = 0; m < kernel.cols; m++) {
                            uchar pixel = input_bgr[o].at<uchar>(i + n, j + m);
                            double w = kernel.at<double>(n, m);
                            total += pixel * w;
                        }
                    }
                    bgr[o].at<uchar>(i, j) = (uchar)total;
                }
            }
        }
    merge(bgr, out_pic);
}
