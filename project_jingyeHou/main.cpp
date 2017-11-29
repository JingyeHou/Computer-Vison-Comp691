#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "eigen3/Eigen/Eigen"

using namespace cv;
using namespace std;
using namespace Eigen;

Mat src;


// compute integral depthX
void integralX(Mat& src, Mat &dst) {
    float max = -9999;
    float min = 0;
    for(int i = 0; i < src.rows; i++) {
        float sum = 0;
        for(int j = 0; j < src.cols; j++) {
            sum += src.at<float>(i, j);
            if(max < sum) {
                max = sum;
            }
            if(min > sum) {
                min = sum;
            }
            dst.at<float>(i, j) = sum;
        }
    }
    for(int i = 0; i < src.rows; i++) {
        for(int j = 0; j < src.cols; j++) {
            dst.at<float>(i, j) =  dst.at<float>(i, j) - min;
        }
    }
    dst = dst / (max - min);
}

// compute integral depthY
void integralY(Mat& src, Mat &dst) {
    float max = -9999;
    float min = 0;
    for(int j = 0; j < src.cols; j++) {
        float sum = 0;
        for(int i = 0; i < src.rows; i++) {
            sum += src.at<float>(i, j);
            if(max < sum) {
                max = sum;
            }
            if(min > sum) {
                min = sum;
            }
            dst.at<float>(i, j) = sum;
        }
    }
    for(int i = 0; i < src.rows; i++) {
        for(int j = 0; j < src.cols; j++) {
            dst.at<float>(i, j) =  dst.at<float>(i, j) - min;
        }
    }
    dst = dst / (max - min);

}

// show picture
void showPic(String name, Mat &image) {
    namedWindow( name , WINDOW_AUTOSIZE);
    imshow( name, image);
    waitKey(0);
}


// get Normal Map
void NormalMap(const int NUM_IMGS, vector<Mat> &modelImages, const Mat &Lights, Mat &Normals, Mat &Mask){
    Mat gray;
    cvtColor(Mask, gray, CV_BGR2GRAY);
    Mat LightsT = Lights.t();
    Mat bgr[3];
    split(Normals, bgr);
    for (int row=0; row < modelImages[0].rows; row++) {
        for (int col = 0; col < modelImages[0].cols; col++) {
            Vec<float, 12> I;
            for (int i = 0; i < NUM_IMGS; i++) {
                I[i] = modelImages[i].at<uchar>(row, col);
            }
            Mat mInv;
            Mat g;
            Mat n = LightsT * Mat(I);
            Mat m = LightsT * Lights;
            invert(m, mInv, DECOMP_SVD);
            g = mInv * n;
            float p = (float)sqrt(g.dot(g));
            if (p > 0) { g = g / p; }
            if (g.at<float>(2, 0) == 0) { g.at<float>(2, 0) = 1.0; }
            for (int i = 0; i < 3; i++) {
                float q = g.at<float>(i, 0);
                bgr[i].at<float>(row, col) = q;
                if((int)gray.at<uchar>(row, col) == 0) {
                    bgr[i].at<float>(row, col) = 0;
                }
            }
        }
    }

    merge(bgr, 3 , Normals);

}

// get albedo
void getAlbedo(const int NUM_IMGS, const vector<Mat> &modelImages, const Mat &Lights, const Mat &Normals,  Mat &albedo) {
    Mat bgr[3];
    split(Normals, bgr);
    float Max = 0;
    for (int row=0; row < modelImages[0].rows; row++) {
        for (int col = 0; col < modelImages[0].cols; col++) {
            Vec<float, 12> I;
            for (int i = 0; i < NUM_IMGS; i++) {
                I[i] = modelImages[i].at<uchar>(row, col);
            }
            Mat J = Mat::zeros(NUM_IMGS, 1, CV_32F);
            for(int i = 0; i < NUM_IMGS; i++) {
                J.at<float>(i, 0) = bgr[0].at<float>(row, col) * Lights.at<float>(i, 0)
                                    + bgr[1].at<float>(row, col) * Lights.at<float>(i, 1)
                                    + bgr[2].at<float>(row, col) * Lights.at<float>(i, 2);
            }
            float p = (float)J.dot(J);
            float He = (float)Mat(I).dot(J);
            albedo.at<float>(row, col) = He / p ;
            if(albedo.at<float>(row, col) > Max) {
                Max = albedo.at<float>(row, col);
            }
        }
    }
    albedo = albedo / Max;
}

// get depth
void DepthMap(Mat &Normal, Mat &MaskImage, float& grayValue){
    std::vector<Triplet<double> > tripletList;
    int number_of_pixels = Normal.rows * Normal.cols;
    SparseMatrix<double> M(2 * number_of_pixels, 2 * number_of_pixels);
    VectorXd v(2 * number_of_pixels);

    Mat channels[3];
    split(Normal, channels);
    Mat bgr[3];
    split(MaskImage, bgr);
    Mat depthMap( MaskImage.rows, MaskImage.cols, CV_32FC2, cv::Scalar::all(0));
    Mat depthChannels[2];
    split(depthMap, depthChannels);
    Mat depthMap2;
    for (int row = 1; row < Normal.rows - 1; row++) {
        for (int col = 1; col < Normal.cols - 1; col++) {
            int i = Normal.cols * (row - 1) + col;
            if( (bgr[0].at<uchar>(row, col + 1) > 0) && (bgr[0].at<uchar>(row - 1, col) > 0) ){
                tripletList.push_back(Triplet<double>(2 * i, 2 * i, channels[2].at<float>(row, col)));
                v[2 * i] = -channels[0].at<float>(row, col);
                tripletList.push_back(Triplet<double>(2 * i + 1, 2 * i + 1, channels[2].at<float>(row, col)));
                v[2 * i + 1] = channels[1].at<float>(row, col);
            } else if (bgr[0].at<uchar>(row - 1, col) > 0) {
                int f = -1;
                if(bgr[0].at<uchar>(row, col + f) > 0) {
                    tripletList.push_back(Triplet<double>(2 * i, 2 * i, channels[2].at<float>(row, col)));
                    v[2 * i] = channels[0].at<float>(row, col);
                }
                tripletList.push_back(Triplet<double>(2 * i + 1, 2 * i + 1, channels[2].at<float>(row, col)));
                v[2 * i + 1] = channels[1].at<float>(row, col);
            } else if (bgr[0].at<uchar>(row, col + 1) > 0) {
                int f = -1;
                if (bgr[0].at<uchar>(row - f, col) > 0) {
                    tripletList.push_back(Triplet<double>(2 * i + 1, 2 * i + 1, channels[2].at<float>(row, col)));
                    v[2 * i + 1] = -channels[1].at<float>(row, col);
                }
                tripletList.push_back(Triplet<double>(2 * i, 2 * i, channels[2].at<float>(row, col)));
                v[2 * i] = -channels[0].at<float>(row, col);
            } else {
                int f = -1;
                if(bgr[0].at<uchar>(row, col + f) > 0) {
                    tripletList.push_back(Triplet<double>(2 * i, 2 * i, channels[2].at<float>(row, col)));
                    v[2 * i] = channels[0].at<float>(row, col);
                }
                if (bgr[0].at<uchar>(row - f, col) > 0) {
                    tripletList.push_back(Triplet<double>(2 * i + 1, 2 * i + 1, channels[2].at<float>(row, col)));
                    v[2 * i + 1] = -channels[1].at<float>(row, col);
                }
            }
        }
    }
    M.setFromTriplets(tripletList.begin(), tripletList.end());
    Eigen::ConjugateGradient<Eigen::SparseMatrix<double> > cg;
    cg.compute(M);
    Eigen::VectorXd z = cg.solve(v);
    std::cout << "Error: " << cg.error() << std::endl;
    std::cout << "# iterations: " << cg.iterations() << std::endl;
    for (int row = 0; row < Normal.rows; row++) {
        for (int col = 0; col < Normal.cols; col++) {
            int i;
            if(row > 0) {
                i = Normal.cols * (row - 1) + col;
            } else {
                i = col;
            }
            if(z[2 * i] != 0) {
                z[2 * i]+= grayValue;
            }
            depthChannels[0].at<float>(row, col) = (float)z[2 * i];
        }
    }

    Mat depthX ( MaskImage.rows, MaskImage.cols, CV_32F, cv::Scalar::all(0));
    integralX(depthChannels[0], depthX);

    showPic("depthX", depthX);
    for (int row = 0; row < Normal.rows; row++) {
        for (int col = 0; col < Normal.cols; col++) {
            int i;
            if(row > 0) {
                i = Normal.cols * (row - 1) + col;
            } else {
                i = col;
            }
            if(z[2 * i + 1] != 0) {
                z[2 * i + 1]+= grayValue;
            }
            depthChannels[1].at<float>(row, col) = (float)z[2 * i + 1];
        }
    }
    Mat depthY ( MaskImage.rows, MaskImage.cols, CV_32F, cv::Scalar::all(0));
    integralY(depthChannels[1], depthY);
    showPic("depthY", depthY);

    addWeighted( depthX, 0.5, depthY, 0.5, 0.0, depthMap2);
    showPic("depth", depthMap2);
}

// 求圆心和半径
void getCentriodAndRadius(Mat& src, Point& point, int& radius) {
    Mat gray;
    cvtColor(src, gray, CV_BGR2GRAY);
    int left = 10000,right = 0, top = 100000, bottom = 0;
    for(int i = 0; i < gray.rows; i++) {
        for (int j =0; j < gray.cols; j++) {
            if(gray.at<uchar>(i, j) >= 254) {
                if(i <= top) {
                    top = i;
                }
                if(i >= bottom ) {
                    bottom = i;
                }
                if(j <= left) {
                    left = j;
                }
                if(j >= right) {
                    right = j;
                }
            }
        }
    }

    point.x = (left + right) / 2;
    point.y = (top + bottom) / 2;
    radius = ((point.x - left) + (right - point.x) + (point.y - top) + (bottom - point.y)) / 4;

}


// 求两点的中心
void getCentriod(Mat& src, Point& point) {
    Mat gray;
    cvtColor(src, gray, CV_BGR2GRAY);
    int left = 10000,right = 0, top = 100000, bottom = 0;
    for(int i = 0; i < gray.rows; i++) {
        for (int j =0; j < gray.cols; j++) {
            if(gray.at<uchar>(i, j) >= 254) {
                if(i < top) {
                    top = i;
                }
                if(i > bottom ) {
                    bottom = i;
                }
                if(j < left) {
                    left = j;
                }
                if(j > right) {
                    right = j;
                }
            }
        }
    }

    point.x = (left + right) / 2;
    point.y = (top + bottom) / 2;
}

// 求chrome的normal
void getNormal(int &radius, Point& point, Point& point1, Mat& normal) {
    double hz;
    hz =sqrt(radius * radius - (point1.x - point.x) * (point1.x - point.x) - (point1.y - point.y) * (point1.y - point.y));

    normal.at<float>(0, 0) = (point1.x - point.x) / (float)radius;
    normal.at<float>(0, 1) = (point.y - point1.y) / (float)radius;
    normal.at<float>(0, 2) = (float)hz / radius;
}

// 求光线方向
Vec3f getL(Mat& normal) {
    float changshu;
    changshu = 2 * normal.at<float>(0, 2);
    float x = changshu * normal.at<float>(0, 0);
    float y = changshu * normal.at<float>(0, 1);
    float z = changshu * normal.at<float>(0, 2) - 1;
    return Vec3f(x, y, z);
}

int main() {
    src = imread("/Users/houjingye/Desktop/498_project_assets_png/psmImages/chrome/chrome.mask.png",  CV_LOAD_IMAGE_COLOR);

    Point point;
    int radius = 0;
    getCentriodAndRadius(src, point, radius);
    Mat gray;
    Mat normal = Mat::zeros(1, 3, CV_32F);
    const int NUM_IMGS          = 12;
    // 插入图片
    const string CHROMES   = "/Users/houjingye/Desktop/498_project_assets_png/psmImages/chrome/chrome.";
    const string MODEL     = "/Users/houjingye/Desktop/498_project_assets_png/psmImages/cat/cat.";
    Mat MaskImage = imread("/Users/houjingye/Desktop/498_project_assets_png/psmImages/cat/cat.mask.png",  CV_LOAD_IMAGE_COLOR);
    vector<Mat> calibImages;
    vector<Mat> modelImages;
    vector<Mat> modelImages0;
    vector<Mat> modelImages1;
    vector<Mat> modelImages2;
    Mat Lights(NUM_IMGS, 3, CV_32F);
    for (int i = 0; i < NUM_IMGS; i++) {
        Mat Calib = imread(CHROMES + to_string(i) + ".png",
                           CV_LOAD_IMAGE_COLOR);
        Mat tmp = imread(MODEL + to_string(i) + ".png",
                         CV_LOAD_IMAGE_COLOR);

        Point point1;
        getCentriod(Calib, point1);
        getNormal(radius, point, point1, normal);
        Vec3f light = getL(normal);
        Lights.at<float>(i, 0) = light[0];
        Lights.at<float>(i, 1) = light[1];
        Lights.at<float>(i, 2) = light[2];

        Mat channels[3];
        split(tmp, channels);
        modelImages.push_back(tmp);
        modelImages0.push_back(channels[0]);
        modelImages1.push_back(channels[1]);
        modelImages2.push_back(channels[2]);
    }
    cout << Lights << endl;
    // 求normal
    Mat Normals( modelImages[0].rows, modelImages[0].cols, CV_32FC3, cv::Scalar::all(0));
    NormalMap(NUM_IMGS, modelImages0, Lights, Normals, MaskImage);

    // 求albedo
    Mat albedo( modelImages[0].rows, modelImages[0].cols, CV_32FC3, cv::Scalar::all(0));
    Mat albedoRBG[3];
    split(albedo, albedoRBG);

    getAlbedo(NUM_IMGS, modelImages0, Lights, Normals, albedoRBG[0]);
    getAlbedo(NUM_IMGS, modelImages1, Lights, Normals, albedoRBG[1]);
    getAlbedo(NUM_IMGS, modelImages2, Lights, Normals, albedoRBG[2]);
    showPic("albedoR", albedoRBG[0]);
    showPic("albedoB", albedoRBG[1]);
    showPic("albedoG", albedoRBG[2]);

    merge(albedoRBG, 3, albedo);

    float grayValue = 0.5;
    showPic("Normal", Normals);
    showPic("albedo", albedo);
    //求深度
    DepthMap(Normals, MaskImage, grayValue);

    return 0;
}

