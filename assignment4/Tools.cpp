//
// Created by 侯景业 on 2017-03-06.
//

#include "Tools.h"

void Tools::showPic(String name, Mat &image) {
    namedWindow( name , WINDOW_AUTOSIZE);

    imshow( name, image);

    waitKey(0);
}