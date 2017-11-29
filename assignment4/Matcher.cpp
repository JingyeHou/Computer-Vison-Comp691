  //
// Created by 侯景业 on 2017-03-06.
//

#include "Matcher.h"
#include "Tools.h"


Matcher::Matcher(const Mat &src1, const Mat &Src2) : src1(src1), Src2(Src2) {
}


//get ssd
float Matcher::Ssd(int r1, int r2) {
    ssd = 0;
    for(int i = 0; i < getSrc1().cols; i++)
    {
        ssd +=  (getSrc1().at<float>(r1,i) - getSrc2().at<float>(r2,i)) *
                (getSrc1().at<float>(r1,i) - getSrc2().at<float>(r2,i));
    }
    return ssd;
}

//get ratio test
void Matcher::match(vector<DMatch> &matches) {
    int minkey = 0;
    float threshold = 0.5;
    for(int row1 = 0; row1 < getSrc1().rows;row1++){
        float distsq2= 6;
        float distsq1= 8;
        minkey= 0 ;
        for(int row2 = 0 ;row2 < getSrc2().rows;row2++){
            float SSD = Ssd(row1, row2);
//            cout << SSD << endl;
            if(SSD < distsq1){
                distsq2 = distsq1;
                distsq1 = SSD;
                minkey = row2;
            }
        }
        if((distsq1 / distsq2) < threshold){
            DMatch bestPair(row1 , minkey , distsq1);
            matches.push_back(bestPair);
        }
    }
}

//match image by using ratio test
void Matcher::run(Mat& image1, Mat& image2, vector<KeyPoint>& keypoint1, vector<KeyPoint>& keypoint2, Mat& stitchs) {
    vector< DMatch > matches;
    match(matches);

    Mat img_matches;
    drawMatches( image1, keypoint1, image2, keypoint2,
                 matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                 vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

//    Tools showPic;
//    showPic.showPic("matchPic1", img_matches);

    std::vector<Point2f> obj;
    std::vector<Point2f> scene;

    for( int i = 0; i < matches.size(); i++ )
    {
        //-- Get the keypoints from the good matches
        obj.push_back( keypoint1[matches[i].queryIdx ].pt );
        scene.push_back( keypoint2[matches[i].trainIdx ].pt );

    }



//    Mat H = findHomography( obj, scene, 0 );

//    std::vector<Point2f> obj_corners(4);
//    obj_corners[0] = cvPoint(0,0);
//    std::vector<Point2f> scene_corners(4);

//    perspectiveTransform( obj_corners, scene_corners, H);
//    float x, y;

//    project((int)obj_corners[0].x, (int)obj_corners[0].y, H, x, y);

    int num = 10;
//    computeInlierCount(H, matches, num, 0.15, keypoint1, keypoint2);
//    cout << num << endl;
//    cout << matches.size() << endl;
    Mat h;
    Mat hinv;
    Mat stitchedImage;

    RANAC(matches, num, 30, keypoint1, keypoint2, h, hinv, image1, image2);

    stitch(image1, image2, h, hinv, stitchedImage, stitchs);


}


float Matcher::getSsd() const {
    return ssd;
}

void Matcher::setSsd(float ssd) {
    Matcher::ssd = ssd;
}

const Mat &Matcher::getSrc1() const {
    return src1;
}

void Matcher::setSrc1(const Mat &src1) {
    Matcher::src1 = src1;
}


const Mat &Matcher::getSrc2() const {
    return Src2;
}

void Matcher::setSrc2(const Mat &Src2) {
    Matcher::Src2 = Src2;
}

void Matcher::project(float x1, float y1, Mat &H, float& x2, float& y2) {
    double w = H.at<double>(2, 0) * x1 + H.at<double>(2, 1) * y1 +  H.at<double>(2, 2);
    x2 = float((H.at<double>(0, 0) * x1 + H.at<double>(0, 1) * y1 +  H.at<double>(0, 2)) / w);
    y2 = float((H.at<double>(1, 0) * x1 + H.at<double>(1, 1) * y1 +  H.at<double>(1, 2)) / w);
}

void Matcher::computeInlierCount(Mat &H, vector<DMatch> &matches, int& numMatches, float inlierThrehold, vector<KeyPoint>& keypoint1, vector<KeyPoint>& keypoint2) {
    float x, y;
    for(int i = 0; i < matches.size(); i++) {
//        cout << keypoint1[matches[i].queryIdx].pt.x << " " << keypoint2[matches[i].trainIdx].pt.x << endl;

       project(keypoint1[matches[i].queryIdx].pt.x, keypoint1[matches[i].queryIdx].pt.y, H, x, y);

//        cout << x << " 1 " << y << endl;
            float rx = (keypoint2[matches[i].trainIdx].pt.x - x) * (keypoint2[matches[i].trainIdx].pt.x - x);
            float ry = (keypoint2[matches[i].trainIdx].pt.y - y) * (keypoint2[matches[i].trainIdx].pt.y - y);
            float distance = sqrt(rx + ry);
//            cout << rx << " " << ry << endl;
//            cout << distance << endl;
            if(distance < inlierThrehold) {
                numMatches++;
            }
//        cout << numMatches << endl;
    }
}



void Matcher::RANAC(vector<DMatch> &matches, int &numMatches, int numIterations, vector<KeyPoint> &keypoint1,
                    vector<KeyPoint> &keypoint2, Mat &hom, Mat &homlnv, Mat &image1Display,
                    Mat &image2Display) {
    int max_num = 0;

    for(int i = 0; i < numIterations; i++) {
        Mat H;

        vector< DMatch > matches2;
        vector<KeyPoint> keyPoints1, keyPoints2;
        vector<Point2f> obj;
        vector<Point2f> scene;

        int m = 4;
        // initialize numbers.
        vector<int> v(matches.size() - 1);
        iota(v.begin(), v.end(), 1);

        // do random shuffle.
        random_device rd;
        mt19937 g(rd());
        shuffle(v.begin(), v.end(), g);

        ostream_iterator<int> output(cout," ");
        copy_n(v.begin(), m, output);


        for (int j = 0; j < m; j++) {
            keyPoints1.push_back( keypoint1[matches[v[j]].queryIdx]);
            keyPoints2.push_back(keypoint2[matches[v[j]].trainIdx]);

            obj.push_back( keypoint1[matches[v[j]].queryIdx ].pt );
            scene.push_back( keypoint2[matches[v[j]].trainIdx ].pt );

            DMatch bestPair(j , j , 0);
            matches2.push_back(bestPair);

        }
         H = findHomography( obj, scene );
//        cout << H << endl;
        int num = 0;

        computeInlierCount(H, matches2, num, 0.01, keyPoints1, keyPoints2);
        std::vector<Point2f> scene_corners(4);
        perspectiveTransform( obj, scene_corners, H);
//        cout << scene_corners << endl;

        if(num > max_num) {
            max_num = num;
            hom = H;
        }
        cout << max_num << endl;
    }
    vector< DMatch > good_matches;
    findAllInlier(hom, matches, good_matches, 0.02, keypoint1, keypoint2);

    vector<Point2f> goodPoints;
    vector<Point2f> matchedPoints;

    for( int i = 0; i < good_matches.size(); i++ )
    {
        //-- Get the keypoints from the good matches
        goodPoints.push_back( keypoint1[good_matches[i].queryIdx ].pt );
        matchedPoints.push_back( keypoint2[good_matches[i].trainIdx ].pt );
    }
    hom = findHomography( goodPoints, matchedPoints, 0 );
    homlnv = hom.inv();

    Mat img_matches;
    drawMatches( image1Display, keypoint1, image2Display, keypoint2,
                 good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                 vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

//    Tools showPic;
//    showPic.showPic("matchPic2", img_matches);
}

void Matcher::findAllInlier(Mat &H, vector<DMatch> &matches, vector<DMatch> &matches2, float inlierThrehold,
                            vector<KeyPoint> &keypoint1, vector<KeyPoint> &keypoint2) {

    float x, y;
    for(int i = 0; i < matches.size(); i++) {
//        cout << keypoint1[matches[i].queryIdx].pt.x << " " << keypoint2[matches[i].trainIdx].pt.x << endl;

        project(keypoint1[matches[i].queryIdx].pt.x, keypoint1[matches[i].queryIdx].pt.y, H, x, y);

        float rx = (keypoint2[matches[i].trainIdx].pt.x - x) * (keypoint2[matches[i].trainIdx].pt.x - x);
        float ry = (keypoint2[matches[i].trainIdx].pt.y - y) * (keypoint2[matches[i].trainIdx].pt.y - y);
        float distance = sqrt(rx + ry);
        if(distance < inlierThrehold) {
            matches2.push_back(matches[i]);
        }
    }
}

void Matcher::stitch(Mat &image1, Mat &image2, Mat &hom, Mat &homInv, Mat &stitchedImage, Mat& stitch) {
    vector<Point2f> image2_corners(4);
    image2_corners[0] = cvPoint(0,0); image2_corners[1] = cvPoint( image2.cols, 0 );
    image2_corners[2] = cvPoint( image2.cols, image2.rows ); image2_corners[3] = cvPoint( 0, image2.rows );
    vector<Point2f> projectedImage1_corners(4);

    for(int i = 0; i < 4; i++) {
        project(image2_corners[i].x, image2_corners[i].y, homInv, projectedImage1_corners[i].x, projectedImage1_corners[i].y);
    }
    cout << projectedImage1_corners << endl;

    float minX = 0;
    float maxX = image1.cols;
    for(int i = 0; i < 4; i++) {
       if(projectedImage1_corners[i].x < minX) {
           minX = projectedImage1_corners[i].x;
       }
        if(projectedImage1_corners[i].x > maxX) {
            maxX = projectedImage1_corners[i].x;
        }
    }
    if(minX < 0) {
        minX = -minX;
    }

    float minY = 0;
    float maxY = image1.rows;
    for(int i = 0; i < 4; i++) {
        if(projectedImage1_corners[i].y < minY) {
            minY = projectedImage1_corners[i].y;
        }
        if(projectedImage1_corners[i].y > maxY) {
            maxY = projectedImage1_corners[i].y;
        }
    }
    if(minY < 0) {
        minY = -minY;
    }
    int stitchRow, stitchCol;
    stitchRow = int(maxY) + int(minY);
    stitchCol = int(maxX) + int(minX);

    stitchedImage = Mat::zeros(stitchRow, stitchCol, image1.type());
    Mat imageROI;
    imageROI = stitchedImage(Rect((int)minX, (int)minY,image1.cols,image1.rows));
            image1.copyTo(imageROI);

    for(int i = 0; i < stitchedImage.rows; i++) {
        for(int j = 0; j <stitchedImage.cols; j++) {
            float x, y;
            project(j - minX, i - minY, hom, x, y);
            if(x >= 0 && x <= image2.cols && y >= 0 && y <= image2.rows) {
                stitchedImage.at<Vec3b>(i, j) = image2.at<Vec3b>((int)y, (int)x);
            }
        }
    }
    stitch = stitchedImage;

}






