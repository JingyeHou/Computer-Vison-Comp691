//
// Created by 侯景业 on 2017-03-06.
//

#include "Descriptor.h"

void Descriptor::getPatch(Mat& src, KeyPoint keyPoint, Mat& patch) {
    Mat gray = src;
    cvtColor(src, gray, CV_BGR2GRAY);

    int left = (int)keyPoint.pt.y - 8;
    int top = (int)keyPoint.pt.x - 8;

    if(top < 0){
        top += 8;
    }
    if(left < 0){
        left += 8;
    }
    if((top + 16) > src.cols){
        top -= 8;
    }
    if((left + 16) > src.rows){
        left -= 8;
    }

    Mat tmp = gray(cv::Rect(top,left,16,16));
    tmp.copyTo(patch);
}

Mat Descriptor::getDescriptor(Mat& src, KeyPoint keyPoint) {

    Mat patch_gray;
    getPatch(src, keyPoint, patch_gray);
    int n = 3;
    Mat Kernel(n, n, CV_64F);
    GaussianKernel gaussianKernel;
    gaussianKernel.guassian(n, n, 1, Kernel);
    filter2D(patch_gray, patch_gray, patch_gray.depth(), Kernel);

    Mat orientation = Mat::zeros(1, 128, CV_32FC1);

    Mat Dx, Dy;

    float kernel_data0[9]={ -1, 0, 1,

                            -1, 0, 1,

                            -1, 0, 1};

    Mat kernel3 = Mat(3,3, CV_32F, kernel_data0);
    filter2D(patch_gray, Dx, CV_32F, kernel3);
    //get Dx

    float kernel_data1[9]={ -1, -1, -1,

                            0,   0,  0,

                            1,   1,  1};
    Mat kernel4 = Mat(3,3,CV_32F,kernel_data1);
    filter2D(patch_gray, Dy, CV_32F, kernel4);
    //get Dy

    Mat mag, angle;
    cartToPolar(Dx, Dy, mag, angle, 1);


//    Mat theta = getTheta(mag, angle);
//    cout << theta << endl;
//    int dif = theta / 45;

//    Mat Kernel(3, 3, CV_64F);
//    GaussianKernel gaussianKernel;
//    gaussianKernel.guassian(3, 3, 2000, Kernel);
//    filter2D(mag, mag, mag.depth(), Kernel);
    int theta;
    theta = Theta(mag, angle);
//
//    //get Dx
//


    for(int i = 0 ;i < 4; i++){
        int beginPoint_row =  4 * i;
        for(int j = 0 ;j < 4;j++){
            int beginPoint_col =  4 * j;
//            Mat tmp = mag(Rect(i * 4, j * 4,4,4));
//            tmp.copyTo(patch_mag);
//            Mat tep = angle(Rect(i * 4, j * 4,4,4));
//            tep.copyTo(patch_dir);
//            cout << patch_dir << endl;
            for(int row = 0 ;row < 4; row++){
                for(int col = 0; col < 4; col++){
//                    getTheta(mag, angle, theta);
                    int dir = (int)angle.at<float>(row+beginPoint_row, col + beginPoint_col) - theta;
                    if(dir < 0){
                        dir += 360;
                    }
//                    cout << angle.at<float>(row+beginPoint_row, col + beginPoint_col) << endl;
//                    cout << dir << endl;
                    int temp = dir / 45;
                    orientation.at<float>(0, i * 8 * 4 + j * 8 + temp)
                            += mag.at<float>(row + beginPoint_row,col + beginPoint_col);
                }
            }
        }
    }

//    theta = Theta(mag, angle);
//    int dif = theta / 45;
//    for(int i = 0 ;i < 4; i++){
//        int beginPoint_row =  4 * i;
//        for(int j = 0 ;j < 4;j++){
//            int beginPoint_col =  4 * j;
//            for(int row = 0 ;row < 4; row++){
//                for(int col = 0; col < 4; col++){
////                    getTheta(mag, angle, theta);
//                    int dir = (int)angle.at<float>(row+beginPoint_row, col + beginPoint_col);
//                    int temp = dir / 45;
//                    orientation.at<float>(0, i * 8 * 4 + j * 8 + temp)
//                            += mag.at<float>(row + beginPoint_row,col + beginPoint_col);
//                }
//            }
//        }
//    }
//
//    Mat orientation2 = Mat::zeros(1, 128, orientation.type());
//    for(int i = 0; i < 16; i++) {
//        for(int j = 0; j < 8 -dif; j++) {
//            orientation2.at<float>(0, i * 8 + j) = orientation.at<float>(0, i * 8 + j + dif);
//        }
//        for(int j = 8 - dif; j < 8; j++) {
//            orientation2.at<float>(0, i * 8 + j) = orientation.at<float>(0, i * 8 + j + dif - 8);
//        }
//    }

    for(int i = 0 ; i < 16 ; i++){
        float max = 0;
        for(int j = 0 ; j < 8; j++){
            max += orientation.at<float>(0, i * 8 + j) * orientation.at<float>(0, i * 8 + j);
        }
        double thr = sqrt(max) * 0.2;
        max = 0;

        for(int j = 0; j < 8; j++) {
            if(thr <= orientation.at<float>(0,  i * 8 + j)) {
                orientation.at<float>(0, i * 8 + j) = (float)thr;
            }
            max += orientation.at<float>(0, i * 8 + j) * orientation.at<float>(0, i * 8 + j);
        }
        max = sqrtf(max);
        for(int j =0 ; j< 8 ;j++){
            orientation.at<float>(0, i * 8 + j) = orientation.at<float>(0, i * 8 + j) / max;
        }
    }
//    cout << orientation << endl;
//    cout << orientation2 << endl;


//    Mat orientation2 = Mat::zeros(1, 128, CV_32FC1);
//    for(int j = 0; j < 16; j++) {
//        for (int i = 0; i < 8 - dif; i++) {
//            orientation2.at<float>(0, j * 8 + i) = orientation.at<float>(0,j * 8 + dif + i);
//        }
//        for (int i = 0; i < dif; i++) {
//            orientation2.at<float>(0, j * 8 + 8 - dif + i) = orientation.at<float>(0, j * 8 + i);
//        }
//    }
//    float Max = 0;
//    for(int r = 0; r < 128; r++) {
//        Max += orientation.at<float>(0,  r) * orientation.at<float>(0,  r);
//    }
//
//    double thr = sqrt(Max) * 0.2;
//    Max = 0;
//    for(int r = 0; r < 128; r++ ) {
//        if(thr <= orientation.at<float>(0,  r)) {
//            orientation.at<float>(0,  r) = (float)thr;
//        }
//        Max += orientation.at<float>(0,  r) * orientation.at<float>(0,  r);
//    }
//
//    for(int r = 0; r < 128; r++){
//                orientation.at<float>(0,  r) =  orientation.at<float>(0, r) / sqrt(Max);
//            }
    return orientation;
}

void Descriptor::descriptor(Mat& img,
                            CV_OUT CV_IN_OUT vector<KeyPoint>& keypoints,
                            Mat &descriptors) {

    descriptors = Mat::zeros((int)keypoints.size(), 128, CV_32FC1);
    for(int i = 0 ; i < keypoints.size();i++){
        cv::Mat temp = getDescriptor(img, keypoints[i]);
        for(int col = 0 ; col < 128; col++){
            descriptors.at<float>(i , col) = temp.at<float>(0, col);
        }
    }
}

void Descriptor::getTheta(Mat &mag, Mat &dir, Mat &thetas) {
    double orientation[4][4];
    Mat patch_mag;
    Mat patch_dir;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            Mat tmp = mag(Rect(i * 4, j * 4,4,4));
            tmp.copyTo(patch_mag);
            Mat temp = dir(Rect(i * 4, j * 4,4,4));
            temp.copyTo(patch_dir);
            orientation[j][i] =  Theta(patch_mag, patch_dir);
            thetas = Mat(4, 4, CV_64F, orientation);
//            thetas.at<int>(i, j) = Theta(patch_mag, patch_dir);
//            cout << orientation[j][i] << endl;
        }
    }

//    cout << orientation << endl;
//    for(int i = 0; i < dir.rows; i++) {
//        for(int j = 0; j < dir.cols; j++) {
//            int temp = int(dir.at<float>(i, j) / 10);
//            orientation.at<float>(0, temp)
//                    += mag.at<float>(i, j);
//        }
//    }
////    cout << orientation << endl;
//    int minkey = 0;
//    float temp = -1;
//    for(int col = 0 ;col < 36;col++) {
//        if (temp < orientation.at<float>(0, col)) {
//            temp = orientation.at<float>(0, col);
//            minkey = col;
//        }
//    }
//    theta = 10 * minkey;
    cout << thetas << endl;

}

int Descriptor::Theta(Mat &patch_mag, Mat &patch_dir) {
    Mat orientation = Mat::zeros(1, 36, CV_32FC1);
    int theta;
    for(int i = 0; i < patch_dir.rows; i++) {
        for(int j = 0; j < patch_dir.cols; j++) {
            int temp = int(patch_dir.at<float>(i, j) / 10);
            orientation.at<float>(0, temp)
                    += patch_mag.at<float>(i, j);
        }
    }
    int minkey = 0;
    float temp = -1;
    for(int col = 0 ;col < 36;col++) {
        if (temp < orientation.at<float>(0, col)) {
            temp = orientation.at<float>(0, col);
            minkey = col;
        }
    }
    theta = 10 * minkey;
    return theta;
}
