//==============================================================
/* Copyright(C) 2022 Intel Corporation
 * Licensed under the Intel Proprietary License
 */
 // =============================================================

#include "ipp.h"
#include "ippi.h"
#include "ippcc.h"
#include "ipptypes.h"
#include "ippi_tl.h"
#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc.hpp>
#include <stdlib.h>

using namespace cv;
using namespace std;

static const bool DEBUG = false;
static const int iternum = 1000;

void log(const char* txt)
{
    if (DEBUG)
        printf("%s \n", txt);
}

void compare(Ipp16s* single_dst, Ipp16s* multi_dst, cv::Mat& cv_dst)
{
    using milli = std::chrono::milliseconds;

    auto compare_start = std::chrono::high_resolution_clock::now();

    bool pass = true;
    bool isMultiFail = false;
    bool isSingleFail = false;

    int total_num = cv_dst.rows * cv_dst.cols;

    std::cout << "total num is: " << total_num << endl;
    int multi_er_num = 0;
    int single_er_num = 0;

    for (int x = 0; x < cv_dst.rows; x++)
    {
        if (!pass)
        {
            break;
        }
        for (int y = 0; y < cv_dst.cols; y++)
        {
            if (abs(multi_dst[x * cv_dst.cols + y]) != abs(cv_dst.at<short>(x, y)))
            {
                multi_er_num++;
             
            }
            if (abs(single_dst[x * cv_dst.cols + y]) != abs(cv_dst.at<short>(x, y)))
            {
                printf("fail x is %d, fail y is %d, single num is %d, cv num is %d \n", x, y, single_dst[x * cv_dst.cols + y], cv_dst.at<short>(x, y));
                single_er_num++;
            }
        }
    }
    std::cout << "accuracy of multi_dst: " << (float)((total_num - multi_er_num)/total_num)*100 <<"%"<< endl;
    std::cout << "accuracy of single_dst: " << (float)((total_num - single_er_num) / total_num)*100 << "%" << endl;
}

template <typename T>
void displayArrayFloat(T array[], int row, int col)
{
    if (!DEBUG)
    {
        return;
    }
    cout << "row is " << row << "  col is " << col << endl;

    for (int x = 0; x < row; x++)
    {
        for (int y = 0; y < col; y++)
        {
            // printf("%7.1f ", array[x * col + y]);
            cout << array[x * col + y];
        }
        cout << endl;
    }
    cout << endl;
}

template <typename T>
void displayArray(T array[], int row, int col)
{
    if (!DEBUG)
    {
        return;
    }
    cout << "row is " << row << "  col is " << col << endl;

    for (int x = 0; x < row; x++)
    {
        for (int y = 0; y < col; y++)
        {
            // printf("%7d ", array[x * col + y]);
            cout << array[x * col + y] << ",";
        }
        cout << endl;
    }
    cout << endl;
}

void displayArray(Ipp16s array[], int row, int col, int channel)
{
    cout << "row is " << row << endl;
    int step = col * channel;
    for (int x = 0; x < row; x++)
    {
        for (int y = 0; y < col * channel; y += 3)
        {
            printf("[%3u, %3u, %3u], ", array[x * step + y], array[x * step + y + 1], array[x * step + y + 2]);
        }
        printf("\n");
    }
    printf("\n");
}

void sobel_ipp_single_thread(cv::Mat& img, Ipp16s* ipp_single_dst_dx, Ipp16s* ipp_single_dst_dy)
{
    std::cout << endl
        << endl
        << "=============  SINGLE thread sobel  ==================" << endl;

    using milli = std::chrono::milliseconds;

    IppStatus status;
    Ipp8u* pSrc = img.data;

    // Ipp8u *fSrc = new Ipp8u[img.rows * img.cols * img.channels()];  // 32f source data
    //Ipp16s* hDst = new Ipp16s[img.rows * img.cols * img.channels()];    // horizon  result
    //Ipp16s* vDst = new Ipp16s[img.rows * img.cols * img.channels()];    // vertical result


    //Ipp16s* hAbsDst = new Ipp16s[img.rows * img.cols * img.channels()]; // horizon  square result
    //Ipp16s* vAbsDst = new Ipp16s[img.rows * img.cols * img.channels()]; // vertical square result

    int step8 = img.cols * sizeof(Ipp8u);
    int step16 = img.cols * sizeof(Ipp16s);
    int step32 = img.cols * sizeof(Ipp32s);
    IppiBorderType borderType = ippBorderRepl; // border type

    Ipp8u* pBuffer;
    int bufferSizeH = 0; // horizon  convolution buffer size
    int bufferSizeV = 0; // vertical convolution buffer size

    IppiSize roiSize = { img.cols, img.rows };

    // in order to prevent data overflow, change 8u to 32f
    // status = ippiConvert_8u32f_C1R(pSrc, step8, fSrc, step32, roiSize);

    auto ipp_start = std::chrono::high_resolution_clock::now();
    ippiFilterSobelVertBorderGetBufferSize(roiSize, ippMskSize3x3, ipp8u, ipp16s, 1, /* numChannels */ &bufferSizeV);
    ippiFilterSobelHorizBorderGetBufferSize(roiSize, ippMskSize3x3, ipp8u, ipp16s, 1, /* numChannels */ &bufferSizeH);
    pBuffer = ippsMalloc_8u(bufferSizeH > bufferSizeV ? bufferSizeH : bufferSizeV); // 创建 horizon 和 vertical 的缓存，取二者的最大值

    for (int i = 0; i < iternum; i++) {
        status = ippiFilterSobelHorizBorder_8u16s_C1R(pSrc, step8, ipp_single_dst_dy, step16,
            roiSize, ippMskSize3x3, borderType, 0, pBuffer);

        status = ippiFilterSobelVertBorder_8u16s_C1R(pSrc, step8, ipp_single_dst_dx, step16,
            roiSize, ippMskSize3x3, borderType, 0, pBuffer);
    }
    auto ipp_finish = std::chrono::high_resolution_clock::now();
    log("horizon sobel");
    displayArray(ipp_single_dst_dx, img.rows, img.cols);
    log("vertical sobel");
    displayArray(ipp_single_dst_dy, img.rows, img.cols);

    std::cout << "ipp Sobel single thread x took "
        << std::chrono::duration_cast<milli>(ipp_finish - ipp_start).count()
        << " milliseconds\n";

    ippsFree(pBuffer);
}

void sobel_ipp_multi_thread(cv::Mat& img, Ipp16s* ipp_multi_dst_dx, Ipp16s* ipp_multi_dst_dy)
{
    using milli = std::chrono::milliseconds;
    std::cout << endl
        << endl
        << "=============  MULTI thread sobel  ==================" << endl;

    Ipp8u* pSrc = img.data; // source data

    IppiSize roiSize = { img.cols, img.rows };
    IppiSizeL roiSizeL = { img.cols, img.rows };

    IppStatus statusT;

    int bufferSizeH = 0; // horizon convolution buffer size
    int bufferSizeV = 0; // vertical convolution buffer 大小
    Ipp8u* pBuffer;

    //Ipp16s* hDst = new Ipp16s[img.rows * img.cols * img.channels()]; // horizon  result
    //Ipp16s* vDst = new Ipp16s[img.rows * img.cols * img.channels()]; // vertical result

    //Ipp16s* hAbsDst = new Ipp16s[img.rows * img.cols * img.channels()];
    //Ipp16s* vAbsDst = new Ipp16s[img.rows * img.cols * img.channels()];

    int step8 = img.cols * sizeof(Ipp8u);
    int step16 = img.cols * sizeof(Ipp16s);
    int step32 = img.cols * sizeof(Ipp32s);
    IppiBorderType borderType_T = ippBorderRepl;

    ippiFilterSobelHorizBorderGetBufferSize_T(roiSize, ippMskSize3x3, ipp8u, ipp16s, 1, /* numChannels */ &bufferSizeH);

    ippiFilterSobelVertBorderGetBufferSize_T(roiSize, ippMskSize3x3, ipp8u, ipp16s, 1, /* numChannels */ &bufferSizeV);

    pBuffer = ippsMalloc_8u(bufferSizeH > bufferSizeV ? bufferSizeH : bufferSizeV);

    auto t_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iternum; i++) {
        // horizon sobel
        statusT = ippiFilterSobelHorizBorder_8u16s_C1R_T(pSrc, step8, ipp_multi_dst_dy, step16,
            roiSize, ippMskSize3x3, borderType_T, 0, pBuffer);
        // vertical sobel
        statusT = ippiFilterSobelVertBorder_8u16s_C1R_T(pSrc, step8, ipp_multi_dst_dx, step16,
            roiSize, ippMskSize3x3, borderType_T, 0, pBuffer);
    }
    auto t_finish = std::chrono::high_resolution_clock::now();
    log("horizon sobel");
    displayArray(ipp_multi_dst_dx, img.rows, img.cols);
    log("vertical sobel");
    displayArray(ipp_multi_dst_dy, img.rows, img.cols);

    std::cout << "ipp Sobel multi thread x took "
        << std::chrono::duration_cast<milli>(t_finish - t_start).count()
        << " milliseconds\n\n\n";

    //delete[] hDst; // horizon  result
    //delete[] vDst; // vertical result
    //delete[] hAbsDst;
    //delete[] vAbsDst;
    ippsFree(pBuffer);
}

void sobel_opencv(cv::Mat& img, cv::Mat& cv_dst_dx, cv::Mat& cv_dst_dy)
{
    using milli = std::chrono::milliseconds;
    std::cout << "=============  OPENCV sobel  =====================" << endl;

    //Mat grad_x;
    //Mat grad_y;

    int ksize = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    auto cv_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iternum; i++) {
        Sobel(img, cv_dst_dx, ddepth, 1, 0, ksize, scale, delta, BORDER_REPLICATE);
        Sobel(img, cv_dst_dy, ddepth, 0, 1, ksize, scale, delta, BORDER_REPLICATE);
    }
    auto cv_finish = std::chrono::high_resolution_clock::now();

    std::cout << "opencv Sobel x took "
        << std::chrono::duration_cast<milli>(cv_finish - cv_start).count()
        << " milliseconds\n";


    if (DEBUG)
    {
        cout << "grad_x = \n"
            << format(cv_dst_dx, Formatter::FMT_PYTHON) << ";" << endl
            << endl
            << endl;

        cout << "grad_y = \n"
            << format(cv_dst_dy, Formatter::FMT_PYTHON) << ";" << endl
            << endl
            << endl;
    }
}

int main(int argc, char** argv)
{
    using milli = std::chrono::milliseconds;

    std::string filename = "data/so_small_starry_25.png";

 
    Mat img = imread(filename, IMREAD_GRAYSCALE);
    if (!img.data) {
        cout << "please check your image path" << endl;
        return -1;
    }

    Mat cv_dst_dx;
    Mat cv_dst_dy;
    Ipp16s* ipp_multi_dst_dx = new Ipp16s[img.rows * img.cols * img.channels()];
    Ipp16s* ipp_multi_dst_dy = new Ipp16s[img.rows * img.cols * img.channels()];

    Ipp16s* ipp_single_dst_dx = new Ipp16s[img.rows * img.cols * img.channels()];
    Ipp16s* ipp_single_dst_dy = new Ipp16s[img.rows * img.cols * img.channels()];


    std::cout << "Total number of cycles: " << iternum << endl;
    // ======================= opencv sobel =====================
    sobel_opencv(img, cv_dst_dx, cv_dst_dy);

    // ======================= ipp single thread ===========

    sobel_ipp_single_thread(img, ipp_single_dst_dx, ipp_single_dst_dy);

    // ====================== ipp multi thread ==================

    sobel_ipp_multi_thread(img, ipp_multi_dst_dx, ipp_multi_dst_dy);

    std::cout << "------------------- dx  accuracy -------------------------" << endl;
    compare(ipp_single_dst_dx, ipp_multi_dst_dx, cv_dst_dx);
    std::cout << "------------------- dy  accuracy -------------------------" << endl;
    compare(ipp_single_dst_dy, ipp_multi_dst_dy, cv_dst_dy);

    printf("\n\n");

    delete[] ipp_multi_dst_dx;
    delete[] ipp_multi_dst_dy;

    delete[] ipp_single_dst_dx;
    delete[] ipp_single_dst_dy;

    return 0;
}
