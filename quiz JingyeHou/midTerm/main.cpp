#include <opencv2/opencv.hpp>
#include "opencv2/xfeatures2d.hpp"
#include "HarrisConer.h"
#include "Matcher.h"
#include "Descriptor.h"
#include "ShowPic.h"

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

int main(){

    Mat src;
    Mat src2;
    Mat dst;
    Mat dst2;

    src = cv::imread ("/Users/houjingye/Desktop/Yosemite1.jpg");
    src2 = cv::imread ("/Users/houjingye/Desktop/Yosemite2.jpg");

    if ((!src.data)||(!src2.data)) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

//    feature detection

    HarrisConer harrisConer;
    vector<cv::Point2f> point1;
    harrisConer.detector(src, dst, 0.05, point1);
    vector<cv::Point2f> point2;
    harrisConer.detector(src2, dst2, 0.05, point2);

    ShowPic showPic;
    showPic.showPic("detection1", dst);
    showPic.showPic("detection2", dst2);
    showPic.showPic("detection3", src);
    showPic.showPic("detection4", src2);


//    feature description
//   convert points to keyPoints
    vector<KeyPoint> keyPoint1,keyPoint2;
    KeyPoint::convert(point1,keyPoint1,1,1,0,-1);
    KeyPoint::convert(point2,keyPoint2,1,1,0,-1);

//    create descriptor
    Mat descriptors_1, descriptors_2;
    Descriptor Descriptor;
    Descriptor.descriptor(dst,keyPoint1,descriptors_1);
    Descriptor.descriptor(dst2,keyPoint2,descriptors_2);

    cout << descriptors_1 << endl;

// Matching descriptor vectors with a brute force matcher

    Matcher matcher(descriptors_1, descriptors_2);
    matcher.run(src, src2, keyPoint1, keyPoint2);

//
   return 0;
}





