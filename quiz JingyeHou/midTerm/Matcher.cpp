//
// Created by 侯景业 on 2017-02-26.
//

#include "Matcher.h"
#include "ShowPic.h"


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
    float threshold = 0.03;
    for(int row1 = 0; row1 <getSrc1().rows;row1++){
        float distsq1=10000000000;
        float distsq2=1000000000;
        minkey= 0 ;
        for(int row2 = 0 ;row2 <getSrc2().rows;row2++){
            float SSD = Ssd(row1, row2);
            if(SSD < distsq1 && SSD >= 0){
                distsq2 = distsq1;
                distsq1 = SSD;
                minkey = row2;
            }
        }
        if((distsq1 / distsq2) > threshold){
            DMatch bestPair(row1 , minkey , distsq1);
            matches.push_back(bestPair);
        }
    }

}

//match image by using ratio test
void Matcher::run(Mat& image1, Mat& image2, vector<KeyPoint>& keypoint1, vector<KeyPoint>& keypoint2) {
    vector< DMatch > matches;
    match(matches);
    double max_dist = 0; double min_dist = 100;
    for( int i = 0; i < matches.size(); i++ ) {
        double dist = matches[i].distance;
        if( dist < min_dist )
            min_dist = dist;
        if( dist > max_dist )
            max_dist = dist;
    }

    vector< DMatch > matches2;
    for( int i = 0; i < matches.size(); i++ )
    { if( matches[i].distance <= max( 2 * min_dist, 0.02) )
        { matches2.push_back( matches[i]); }
    }

    Mat img_matches;
    drawMatches( image1, keypoint1, image2, keypoint2,
                 matches2, img_matches, Scalar::all(-1), Scalar::all(-1),
                 vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

    for( int i = 0; i < (int)matches2.size(); i++ )
    { printf( "-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d  \n", i, matches2[i].queryIdx, matches2[i].trainIdx ); }

    //-- Show detected matches
    ShowPic showPic;
    showPic.showPic("matchPic", img_matches);
//
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




