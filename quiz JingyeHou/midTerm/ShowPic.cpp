//
// Created by 侯景业 on 2017-02-27.
//

#include "ShowPic.h"

void ShowPic::showPic(String name, Mat &image) {
    namedWindow( name , WINDOW_AUTOSIZE);

    imshow( name, image);

    waitKey(0);
}