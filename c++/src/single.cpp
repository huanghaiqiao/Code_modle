# include <iostream>
# include <string>
# include <chrono>
# include "opencv2/opencv.hpp"
# include <string>

# include <typeinfo>
# include "ipp.h"

#define _USE_MATH_DEFINES
#include <math.h>


using namespace std;

static const int init_num = 2;
static const int iternum = 10000;
static const bool DEBUG = false;
//using namespace cv;
// C:\Users\haiqiaox\source\CVOI_package

void compare_data(const cv::Mat& img1, const cv::Mat& img2) {
    int total_num = img1.rows * img1.cols;
    int erro_num = 0;
    float abs_erro = 0.000001;
    for (int x = 0; x < img1.rows; x++)
    {
        for (int y = 0; y < img1.cols; y++)
        {
            if (abs(img1.at< uchar>(x, y)) - abs(img2.at< uchar>(x, y)) > abs_erro) {
                cout << "opencv:" << (float)img1.at< uchar>(x, y) << endl;
                cout << "ipp:" << (float)img2.at< uchar>(x, y) << endl;
                erro_num++;
            }
        }
    }
    cout << "abs erro : " << abs_erro << "; ";
    std::cout << "accuracy of blurredImg: " << (float)((total_num - erro_num) / total_num) * 100 << "%" << endl;
}

void compare_data(const cv::Mat& img1, Ipp32f* &data) {
    int total_num = img1.rows * img1.cols;
    int erro_num = 0;
    float abs_erro = 0.00001;

    for (int x = 0; x < img1.rows; x++)
    {
        for (int y = 0; y < img1.cols; y++)
        {
            if (abs(img1.at< float>(x, y)) - abs(data[x * img1.cols + y]) > abs_erro) {
                cout << "opencv:" << (float)img1.at< float>(x, y) << endl;
                cout << "ipp:" << (float)data[x * img1.cols + y] << endl;
                erro_num++;
            }
        }
    }
    cout << "abs erro : " << abs_erro << "; ";
    std::cout << "accuracy : " << (float)((total_num - erro_num) / total_num) * 100 << "%" << endl;
}

void compare_data(const cv::Mat& img1, Ipp32f*& data, bool phase) {
    int total_num = img1.rows * img1.cols;
    int erro_num = 0;
    float abs_erro = 0.01;

    for (int x = 0; x < img1.rows; x++)
    {
        for (int y = 0; y < img1.cols; y++)
        {
            if (abs(tan(img1.at< float>(x, y))) - abs(tan(data[x * img1.cols + y])) > abs_erro) {
                if (DEBUG) {
                    cout << "opencv:" << tan(img1.at< float>(x, y)) << endl;
                    cout << "ipp:" << tan(data[x * img1.cols + y]) << endl;
                }
                erro_num++;
            }
        }
    }
    cout << "abs erro : " << abs_erro << "; ";
    std::cout << "accuracy : " << ((float)(total_num - erro_num) / total_num) * 100 << "%" << endl;
}

void compare_data(const cv::Mat& img1, Ipp16s*& data) {
    int total_num = img1.rows * img1.cols;
    int erro_num = 0;
    float abs_erro = 0.000001;

    for (int x = 0; x < img1.rows; x++)
    {
        for (int y = 0; y < img1.cols; y++)
        {
            if (abs(img1.at< float>(x, y)) - abs(data[x * img1.cols + y]) > abs_erro) {
                cout << "opencv:" << (float)img1.at< float>(x, y) << endl;
                cout << "ipp:" << (float)data[x * img1.cols + y] << endl;
                erro_num++;
            }
        }
    }
    cout << "abs erro : " << abs_erro << "; ";
    std::cout << "accuracy : " << (float)((total_num - erro_num) / total_num) * 100 << "%" << endl;
}


void opencv_test(const cv::Mat &img_name, cv::Mat& blurredImg, 
    cv::Mat &dx, cv::Mat& dy, cv::Mat &mag,cv::Mat &pha, int name = -1) {

    int ksize = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    for (int i = 0; i < init_num; i++) {
        cv::medianBlur(img_name, blurredImg, 9);
        cv::Sobel(blurredImg, dx, CV_32FC1, 1, 0, ksize, scale, delta, cv::BORDER_REPLICATE);
        cv::Sobel(blurredImg, dy, CV_32FC1, 0, 1, ksize, scale, delta, cv::BORDER_REPLICATE);
        cv::magnitude(dx, dy, mag);
        cv::phase(dx, dy, pha);
        //cv::phase(dy, dx, pha);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iternum; i++) {
        cv::medianBlur(img_name, blurredImg, 9);
        cv::Sobel(blurredImg, dx, CV_32FC1, 1, 0, ksize, scale, delta, cv::BORDER_REPLICATE);
        cv::Sobel(blurredImg, dy, CV_32FC1, 0, 1, ksize, scale, delta, cv::BORDER_REPLICATE);
        cv::magnitude(dx, dy, mag);
        cv::phase(dx, dy, pha);
        //cv::phase(dy, dx, pha);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    cout << "opencv : ";
    cout << chrono::duration_cast<chrono::microseconds>(stop - start).count() << "ms" << endl;

    if (name == 0)
    {
        cout << "blurredImg = \n"
            << cv::format(blurredImg, cv::Formatter::FMT_PYTHON) << ";" << endl
            << endl
            << endl;
    }
    if (name == 1)
    {
        cout << "dx = \n"
            << cv::format(dx, cv::Formatter::FMT_PYTHON) << ";" << endl
            << endl
            << endl;

        cout << "dy = \n"
            << cv::format(dy, cv::Formatter::FMT_PYTHON) << ";" << endl
            << endl
            << endl;
    }
    if (name == 2)
    {
        cout << "mag = \n"
            << cv::format(mag, cv::Formatter::FMT_PYTHON) << ";" << endl
            << endl
            << endl;
    }
    if (name == 3)
    {
        //cout << "pha = \n"
        //    << cv::format(pha, cv::Formatter::FMT_PYTHON) << ";" << endl
        //    << endl
        //    << endl;

        cout << "pha = \n";
        for (int x = 0; x < pha.rows; x++)
        {
            for (int y = 0; y < pha.cols; y++)
            {
                cout << tan(pha.at<float>(x, y)) << ",";
            }
            cout << endl;
        }
        //cout << pha
    }
}

void ipp_test(const cv::Mat& img_name, cv::Mat &out_image, Ipp16s* &ipp_dx, Ipp16s* &ipp_dy,
    Ipp32f* &ippiMagnitude, Ipp32f* &ippiPhase, int name = -1) {

    // 接收数据
    //Ipp8u* pSrc = img_name.data;
    Ipp8u* pSrc = nullptr;
    //cv::Mat out_image;
    //out_image.create(img_name.size(), img_name.type());
    //out_image.zeros(img_name.size(), img_name.type());
    //cv::Mat out_image = cv::Mat::zeros(img_name.size(), CV_8UC1);


    //cout << "out_image = " << endl;
    //cout << cv::format(out_image, cv::Formatter::FMT_PYTHON) << ";" << endl
    //    << endl
    //    << endl;

    // 计算步长
    int step8u = img_name.cols * sizeof(Ipp8u);
    int step16s = img_name.cols * sizeof(Ipp16s);
    int step32f = img_name.cols * sizeof(Ipp32f);
    int step32fc = img_name.cols * sizeof(Ipp32fc);

    // 申请空间
    Ipp8u* pBuffer_v;
    int bufferSizeH = 0; // horizon  convolution buffer size
    int bufferSizeV = 0; // vertical convolution buffer size
    IppiBorderType borderType = ippBorderRepl; // border type
    //Ipp16s* ipp_dy = new Ipp16s[img_name.rows * img_name.cols * img_name.channels()];
    //Ipp16s* ipp_dx = new Ipp16s[img_name.rows * img_name.cols * img_name.channels()];

    Ipp32f* pSrc32f_Re = new Ipp32f[img_name.rows * img_name.cols * img_name.channels()];
    Ipp32f* pSrc32f_Im = new Ipp32f[img_name.rows * img_name.cols * img_name.channels()];
    //Ipp32f* ippiMagnitude = new Ipp32f[img_name.rows * img_name.cols * img_name.channels()];
    //Ipp32f* ippiPhase = new Ipp32f[img_name.rows * img_name.cols * img_name.channels()];

    Ipp32fc* sDst_32fc = new Ipp32fc[img_name.rows * img_name.cols * img_name.channels()];

    IppiSize roiSize = { img_name.cols, img_name.rows };

    ippiFilterSobelVertBorderGetBufferSize(roiSize, ippMskSize3x3, ipp8u, ipp16s, 1, /* numChannels */ &bufferSizeV);
    ippiFilterSobelHorizBorderGetBufferSize(roiSize, ippMskSize3x3, ipp8u, ipp16s, 1, /* numChannels */ &bufferSizeH);
    pBuffer_v = ippsMalloc_8u(bufferSizeH > bufferSizeV ? bufferSizeH : bufferSizeV); // 创建 horizon 和 vertical 的缓存，取二者的最大值

    // 中值滤波预处理
    //pBuffer = ippsMalloc_8u(iTmpBufSize);
    int kernelsize = 9;
    IppiSize mask_Size = { kernelsize, kernelsize };

    int numChannels = 1;
    int iTmpBufSize = 0;
    Ipp8u borderValue = 254;
    Ipp8u* pBuffer = NULL;
    ippiFilterMedianBorderGetBufferSize(roiSize, mask_Size, ipp8u, numChannels, &iTmpBufSize);
    //cout << "iTmpBufSize: " << iTmpBufSize << endl;
    pBuffer = ippsMalloc_8u(iTmpBufSize);

    for (int i = 0; i < init_num; i++) {
        ippiFilterMedianBorder_8u_C1R(img_name.data, img_name.step[0], out_image.data, out_image.step[0],
            roiSize, mask_Size, borderType, borderValue, pBuffer);

        pSrc = out_image.data;
        ippiFilterSobelHorizBorder_8u16s_C1R(pSrc, step8u, ipp_dy, step16s,
            roiSize, ippMskSize3x3, borderType, 0, pBuffer_v);

        ippiFilterSobelVertBorder_8u16s_C1R(pSrc, step8u, ipp_dx, step16s,
            roiSize, ippMskSize3x3, borderType, 0, pBuffer_v);

        ippiConvert_16s32f_C1R(ipp_dx, step16s, pSrc32f_Re, step32f, roiSize);
        ippiConvert_16s32f_C1R(ipp_dy, step16s, pSrc32f_Im, step32f, roiSize);

        // 复数转换
        ippsRealToCplx_32f(pSrc32f_Re, pSrc32f_Im, sDst_32fc, img_name.rows * img_name.cols);
        ippiMagnitude_32fc32f_C1R(sDst_32fc, step32fc, ippiMagnitude, step32f, roiSize);
        ippiPhase_32fc32f_C1R(sDst_32fc, step32fc, ippiPhase, step32f, roiSize);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iternum; i++) {
        //ippiFilterMedianBorder_8u_C1R(img_name.data, img_name.step[0], out_image.data, out_image.step[0],
        //    roiSize, mask_Size, borderType, borderValue, pBuffer);

        //pSrc = out_image.data;
        ippiFilterSobelHorizBorder_8u16s_C1R(pSrc, step8u, ipp_dy, step16s,
            roiSize, ippMskSize3x3, borderType, 0, pBuffer_v);

        ippiFilterSobelVertBorder_8u16s_C1R(pSrc, step8u, ipp_dx, step16s,
            roiSize, ippMskSize3x3, borderType, 0, pBuffer_v);
        
        //// 16s转化为32f
        //ippiConvert_16s32f_C1R(ipp_dx, step16s, pSrc32f_Re, step32f, roiSize);
        //ippiConvert_16s32f_C1R(ipp_dy, step16s, pSrc32f_Im, step32f, roiSize);

        // 复数转换
        //ippsRealToCplx_32f(pSrc32f_Re, pSrc32f_Im, sDst_32fc, img_name.rows * img_name.cols);

        ippiMagnitude_32fc32f_C1R(sDst_32fc, step32fc, ippiMagnitude, step32f, roiSize);

        ippiPhase_32fc32f_C1R(sDst_32fc, step32fc, ippiPhase, step32f, roiSize);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    cout << "ipp singel : ";
    cout << chrono::duration_cast<chrono::microseconds>(stop - start).count() << "ms" << endl;

    if (name == 0)
    {
        cout << "out_image = " << endl;
        cout<< cv::format(out_image, cv::Formatter::FMT_PYTHON) << ";" << endl
            << endl
            << endl;
    }
    if (name == 1)
    {
        cout << "dx = " << endl;
        for (int i = 0; i < img_name.rows; i++) {
            for (int j = 0; j < img_name.cols; j++) {

                //printf("%.1f,", pDst[i * img_Im.cols + j]);
                cout << ipp_dx[i * img_name.cols + j] << ",";
            }
            cout << endl;
        }

        cout << "dy = " << endl;
        for (int i = 0; i < img_name.rows; i++) {
            for (int j = 0; j < img_name.cols; j++) {

                //printf("%.1f,", ipp_dy[i * img_name.cols + j]);
                cout << ipp_dy[i * img_name.cols + j] << ",";
            }
            cout << endl;
        }

        //cout << "sDst_32fc.im = " << endl;
        //for (int i = 0; i < img_name.rows; i++) {
        //    for (int j = 0; j < img_name.cols; j++) {

        //        //printf("%.1f,", ipp_dy[i * img_name.cols + j]);
        //        cout << sDst_32fc[i * img_name.cols + j].im << ",";
        //    }
        //    cout << endl;
        //}

        //cout << "sDst_32fc.re = " << endl;
        //for (int i = 0; i < img_name.rows; i++) {
        //    for (int j = 0; j < img_name.cols; j++) {

        //        //printf("%.1f,", ipp_dy[i * img_name.cols + j]);
        //        cout << sDst_32fc[i * img_name.cols + j].re << ",";
        //    }
        //    cout << endl;
        //}

        //cout << "pSrc32f_Im = " << endl;
        //for (int i = 0; i < img_name.rows; i++) {
        //    for (int j = 0; j < img_name.cols; j++) {

        //        //printf("%.1f,", ipp_dy[i * img_name.cols + j]);
        //        cout << pSrc32f_Im[i * img_name.cols + j] << ",";
        //    }
        //    cout << endl;
        //}
    }
    if (name == 2)
    {
        cout << "ippiMagnitude = " << endl;
        for (int i = 0; i < img_name.rows; i++) {
            for (int j = 0; j < img_name.cols; j++) {

                //printf("%.1f,", pDst[i * img_Im.cols + j]);
                cout << ippiMagnitude[i * img_name.cols + j] << ",";
            }
            cout << endl;
        }
    }
    if (name == 3)
    {
        cout << "ippiPhase = " << endl;
        for (int i = 0; i < img_name.rows; i++) {
            for (int j = 0; j < img_name.cols; j++) {

                // 象限
                //printf("%.1f,", pDst[i * img_Im.cols + j]);
                if (ippiPhase[i * img_name.cols + j] < 0) {
                    cout << tan(ippiPhase[i * img_name.cols + j]) << ",";
                    /*cout << M_PI - ippiPhase[i * img_name.cols + j] << ",";*/
                }
                else {
                    cout << tan(ippiPhase[i * img_name.cols + j]) << ",";
                }

               /* cout << 2 * M_PI + ippiPhase[i * img_name.cols + j] << ",";*/
            }
            cout << endl;
        }
    }

    //delete[] ipp_dy;
    //delete[] ipp_dx;
    delete[] pSrc32f_Re;
    delete[] pSrc32f_Im;
    //delete[] ippiMagnitude;
    //delete[] ippiPhase;
    delete[] sDst_32fc;
    ippsFree(pBuffer);
    ippsFree(pBuffer_v);
}

int main() {
    string img_path = "./data/so_small_starry_25.png";

    cv::Mat img = cv::imread(img_path, 0);
    if (!img.data) {
        cout << "please check your image path" << endl;
        return -1;
    }

    std::cout << "Total number of cycles: " << iternum << endl;

    cv::Mat blurredImg = cv::Mat::zeros(img.size(), CV_8UC1);
    cv::Mat out_image = cv::Mat::zeros(img.size(), CV_8UC1);
    cv::Mat dx = cv::Mat::zeros(img.size(), CV_32FC1);
    cv::Mat dy = cv::Mat::zeros(img.size(), CV_32FC1);
    cv::Mat mag = cv::Mat::zeros(img.size(), CV_32FC1);
    cv::Mat pha = cv::Mat::zeros(img.size(), CV_32FC1);

    Ipp16s* ipp_dy = new Ipp16s[img.rows * img.cols * img.channels()];
    Ipp16s* ipp_dx = new Ipp16s[img.rows * img.cols * img.channels()];

    Ipp32f* ippiMagnitude = new Ipp32f[img.rows * img.cols * img.channels()];
    Ipp32f* ippiPhase = new Ipp32f[img.rows * img.cols * img.channels()];

    opencv_test(img, blurredImg, dx, dy, mag, pha);
    ipp_test(img, out_image, ipp_dx, ipp_dy, ippiMagnitude, ippiPhase);

    cout << "======= blurredImg dx =========" << endl;
    compare_data(blurredImg, out_image);

    cout << "======= compare dx =========" << endl;
    compare_data(dx, ipp_dx);

    cout << "======= compare dy =========" << endl;
    compare_data(dy, ipp_dy);

    cout << "======= compare mag =========" << endl;
    compare_data(mag, ippiMagnitude);

    cout << "======= compare phase =========" << endl;
    compare_data(pha, ippiPhase, true);

    delete[] ipp_dy;
    delete[] ipp_dx;
    delete[] ippiMagnitude;
    delete[] ippiPhase;
    return 0;
}
