# include <iostream>
# include <string>
# include <chrono>
# include "opencv2/opencv.hpp"

# include <typeinfo>
# include "ipp.h"

using namespace std;
static const int DEBUG = false;
static const int iternum = 10000;
static const float abs_erro = 0.00001;


//using namespace cv;
// C:\Users\haiqiaox\source\CVOI_package
//ippi.dll

void test_opencv() {

    float elements[6] = { 1,2,3,4,5,6 };
    cv::Mat a = cv::Mat(2, 3, CV_32FC1, elements);
    cv::Mat b = cv::Mat(2, 3, CV_32FC1, elements);
    cv::Mat c;
    cv::magnitude(a, b, c);
    cout << "mag = \n"
        << cv::format(c, cv::Formatter::FMT_PYTHON) << ";" << endl
        << endl
        << endl;
}


void compare(Ipp32f* single_dst, cv::Mat& cv_dst)
{
    int total_num = cv_dst.rows * cv_dst.cols;
    std::cout << "total num is: " << total_num << endl;
    int multi_er_num = 0;
    int single_er_num = 0;

    if ((cv_dst.at< float>(0, 0) != single_dst[0])) {
        cout << "huang" << endl;
    }

    for (int x = 0; x < cv_dst.rows; x++)
    {
        for (int y = 0; y < cv_dst.cols; y++)
        {
            if ((single_dst[x * cv_dst.cols + y] - cv_dst.at<float>(x, y) > abs_erro))
            {
                cout << single_dst[x * cv_dst.cols + y] - cv_dst.at<float>(x, y) << endl;
                cout << "ipps: " << single_dst[x * cv_dst.cols + y] << endl;
                cout << "opencv:"  <<cv_dst.at< float>(x, y) << endl;
                single_er_num++;
            }
        }
    }
    std::cout << "accuracy of magnitude: " << (float)((total_num - single_er_num) / total_num) * 100 << "%" << endl;
}


template <typename T>
void displayArray(T array[],int col, int row) {
    // 整形打印
    cout << "row is " << row << "  col is " << col << endl;
    for (int x = 0; x < row; x++)
    {
        for (int y = 0; y < col; y++)
        {
             //printf("%.1f,", array[x * col + y]);
            cout << (float)array[x * col + y] <<",";
        }
        cout << endl;
    }
    cout << endl;
}


void displayArray_opencv(cv::Mat img) {
    // 整形打印
    cout << cv::format(img, cv::Formatter::FMT_PYTHON) << ";" << endl
        << endl
        << endl;
}


int ipp_magnitude(cv::Mat& img_Re, cv::Mat& img_Im, Ipp32f* pDst) {
    //displayArray_opencv(img_Re);
    if (img_Re.cols != img_Im.cols || img_Re.rows != img_Im.rows) {
        cout << "img_Re and img_Im shape is different, Cannot be converted to a complex !" << endl;
        return -1;
    }
    IppStatus status;
    IppiSize roiSize = { img_Re.cols, img_Re.rows };
    int cols = img_Re.cols;
    int rows = img_Re.rows;

    // 接收数据
    Ipp32f* pSrc32f_Re = (float*)img_Re.data;
    Ipp32f* pSrc32f_Im = (float*)img_Im.data;

    // 计算步长
    int step32 = img_Re.cols * sizeof(Ipp32f);
    int srcStep = img_Re.cols * sizeof(Ipp32fc);

    // 申请空间
    Ipp32fc* sDst = new Ipp32fc[img_Re.rows * img_Re.cols * img_Re.channels()];
 
    // 复数转换
    status = ippsRealToCplx_32f(pSrc32f_Re, pSrc32f_Im, sDst, cols* rows);

    // 计算sMagnitude
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iternum; i++) {
        status = ippiMagnitude_32fc32f_C1R(sDst, srcStep, pDst, step32, roiSize);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "ippiMagnitude took " 
        << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
        << " milliseconds\n";

    // float 打印
    if (DEBUG) {
        cout << "================= all data =========================" << endl;
        for (int i = 0; i < img_Re.rows; i++) {
            for (int j = 0; j < img_Im.cols; j++) {

                //printf("%.1f,", pDst[i * img_Im.cols + j]);
               cout << pDst[i * img_Im.cols + j] <<",";
            }
            cout << endl;
        }
    }
    delete [] sDst;
    return 0;
}

int main() {
    string img_path = "./data/so_small_starry_25.png";
    cv::Mat img_Re = cv::imread(img_path, 0);
    if (!img_Re.data) {
        cout << "please check your image path" << endl;
        return -1;
    }
    cv::Mat blurredImg = cv::Mat::zeros(img_Re.size(), CV_8UC1);
    cv::Mat dx = cv::Mat::zeros(img_Re.size(), CV_32FC1);
    cv::Mat dy = cv::Mat::zeros(img_Re.size(), CV_32FC1);
    cv::Mat mag = cv::Mat::zeros(img_Re.size(), CV_32FC1);
    cv::Mat pha = cv::Mat::zeros(img_Re.size(), CV_32FC1);

    cv::medianBlur(img_Re, blurredImg, 9);
    cv::Sobel(blurredImg, dx, CV_32FC1, 1, 0);
    cv::Sobel(blurredImg, dy, CV_32FC1, 0, 1);


    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iternum; i++) {
        cv::magnitude(dx, dy, mag);
    }

    std::cout << "Total number of cycles: " << iternum << endl;
    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << "opencv Magnitude took "
        << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
        << " milliseconds\n";

    Ipp32f* pDst = new Ipp32f[img_Re.rows * img_Re.cols * img_Re.channels()];

    ipp_magnitude(dx, dy, pDst);
    compare(pDst, mag);
    delete[] pDst;
    return 0;
}
