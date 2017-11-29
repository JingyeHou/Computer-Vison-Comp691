//
// Created by 侯景业 on 2017-02-06.
//

#include "GuassianKernel.h"
using namespace std;

void GuassianKernel::guassian(int sizex, int sizey, double sigma, cv::Mat &kernel) {
    double pi = M_PI;
    double mins = 0;
    double mid1 = floor((sizex - 1) / 2);
    double mid2 = floor((sizey - 1) / 2);
    for(int i = 1; i <= sizex; i++){
        for(int j = 1 ; j <= sizey; j++) {
            double ttt = ((i - mid1 - 1) * (i - mid1 - 1) + (j - mid2 - 1) * (j - mid2 - 1)) / (2 * sigma * sigma);
            double t = exp(- ttt);
            double a = t / (2 * pi * sigma * sigma);
            mins += a;
            kernel.at<double>(i - 1, j - 1) = a;
        }
    }

    for(int i = 0; i < sizex; i++){
        for (int j = 0; j < sizey; j++) {
            kernel.at<double>(i, j) /= mins;
        }
    }
}
