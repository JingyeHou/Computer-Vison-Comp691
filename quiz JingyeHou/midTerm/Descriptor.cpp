//
// Created by 侯景业 on 2017-02-26.
//

#include "Descriptor.h"



Mat Descriptor::getDescriptor(Mat src, KeyPoint keyPoint) {

    src.convertTo(src, CV_32F, 1/255.0);


    Mat orientation = Mat::zeros(1, 128, CV_32FC1);

    Mat Dx, Dy;

    float kernel_data0[9]={ -1, 0, 1,

                            -1, 0, 1,

                            -1, 0, 1};

    Mat kernel3 = Mat(3,3, CV_32F, kernel_data0);
    filter2D(src, Dx, CV_32F, kernel3);
    //get Dx

    float kernel_data1[9]={ -1, -1, -1,

                            0,   0,  0,

                            1,   1,  1};
    Mat kernel4 = Mat(3,3,CV_32F,kernel_data1);
    filter2D(src, Dy, CV_32F, kernel4);
    //get Dy

    Mat mag, angle;
    cartToPolar(Dx, Dy, mag, angle, 1);
    //get direction and magnitude

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
        left -=  8;
    }

    for(int i = 0 ;i < 4; i++){
        int beginPoint_row = left + 4 * i;
        for(int j = 0 ;j < 4;j++){
            int beginPoint_col = top + 4 * j;
            for(int row = 0 ;row < 4; row++){
                for(int col = 0; col < 4; col++){
                    int temp = int(angle.at<float>(row+beginPoint_row, col + beginPoint_col) / 45);
                    orientation.at<float>(0, i * 8 * 4 + j * 8 + temp)
                            += mag.at<float>(row + beginPoint_row,col + beginPoint_col);
                }
            }
        }
    }


    for(int i = 0 ; i < 16 ; i++){
        float max = 0;
        for(int j = 0 ; j < 8; j++){
            max += orientation.at<float>(0, i * 8 + j) * orientation.at<float>(0, i * 8 + j);
        }
        max = sqrtf(max);
        for(int j =0 ; j< 8 ;j++){
            orientation.at<float>(0, i * 8 + j) = orientation.at<float>(0, i * 8 + j) / max;
        }
    }
    return orientation;
}

void Descriptor::descriptor(Mat img,
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

Descriptor::Descriptor() {}





