### ipp使用文档

一、命名规范，1B=8bit

| 数据类型 |                                                      |
| -------- | ---------------------------------------------------- |
| **8u**   | 8 bit, unsigned data ；例如 Ipp8u                    |
| **8s**   | 8 bit, signed data                                   |
| **16u**  | 16 bit, unsigned data                                |
| **16uc** | 16-bit, complex unsigned short data                  |
| **16s**  | 16 bit, signed data                                  |
| **16sc** | 16-bit, complex short data                           |
| **32u**  | 32 bit, unsigned data                                |
| **32s**  | 32 bit, signed data                                  |
| **32sc** | 32-bit, complex int data                             |
| **32f**  | 32-bit, single-precision real floating point data    |
| **32fc** | 32-bit, single-precision complex floating point data |
| **64s**  | 64-bit, quadword signed data                         |
| **64f**  | 64-bit, double-precision real floating point data    |

二、Intel IPP by structures

```c++
typedef struct {     Ipp16s re;     Ipp16s im; } Ipp16sc;
typedef struct {     Ipp32s re;     Ipp32s im; } Ipp32sc;
typedef struct {     Ipp32f re;     Ipp32f im; } Ipp32fc;
```

三、Descriptors（描述符）

| A              | Image data contains an alpha channel as the last channel, requires C4, alpha-channel is not processed | ippiAddC_8u_AC4R                                             |
| -------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| A0             | Image data contains an alpha channel as the first channel, requires C4, alpha-channel is not processed | ippiLUTPalette_8u_C3A0C4R                                    |
| C1, C2, C3, C4 | Image data is in pixel order and made up of 1, 2, 3 or 4 discrete interleaved channels | ippiFilter_32f_C1RippiFilter_32f_C3RippiFilter_32f_C4RippiResizeCCRotate_8u_C2R |
| C              | Channel of interest (COI) is used in the operation           | ippiSet_8u_C3CR                                              |
| I              | Operation is performed in-place - that is result of operation is written back into the source (default is not-in-place) | ippiMulPack_32f_C3IR                                         |
| M              | Operation uses a mask to determine pixels to be processed    | ippiCopy_8u_C1MR                                             |
| P              | Function works with non-contiguous volume data (the location of the planes is passed to the function using pointers on the plane) | ipprResize_8u_C1PV                                           |
| P2, P3, P4     | Image data is in planar order and made up of 2, 3 or 4 discrete planar (non-interleaved) channels, with a separate pointer to each plane | ippiResizeYUV420_8u_P2R, ippiGammaFwd_8u_P3R, ippiCopy_32f_P4R |
| R              | Function operates on a defined region of interest (ROI) for each source image | ippiMean_8u_C4R                                              |
| Sfs            | Saturation and fixed scaling mode is used                    | ippiSubC_8u_C1RSfs                                           |
| s              | Saturation and no scaling (default)                          | ippiConvert_16s16u_C1Rs                                      |
| V              | Function operates on a defined volume of interest (VOI) for each source image | ipprCopyConstBorder_8u_C1V_L                                 |

四、错误提示

```
ippStsNotSupportedModeErr	The requested mode is currently not supported.
ippStsDecimateFractionErr	Unsupported fraction in decimate.
ippStsWeightErr	Incorrect value for weight.
ippStsQualityIndexErr	Quality Index cannot be calculated for an image filled with a constant.
ippStsResizeNoOperationErr	One of the output image dimensions is less than 1 pixel.
ippStsBlockStepErr	Step for Block is less than 8.
ippStsMBStepErr	Step for MB is less than 16.
ippStsNoiseRangeErr	Noise value for Wiener Filter is out of range.
ippStsLPCCalcErr	Cannot evaluate linear prediction.
ippStsJPEG2KBadPassNumber	Pass number exceeds the limits of [0,nOfPasses-1].
ippStsJPEG2KDamagedCodeBlock	Codeblock for decoding is damaged.
ippStsH263CBPYCodeErr	Illegal Huffman code is detected during CBPY stream processing.
ippStsH263MCBPCInterCodeErr	Illegal Huffman code is detected during MCBPC Inter stream processing.
ippStsH263MCBPCIntraCodeErr	Illegal Huffman code is detected during MCBPC Intra stream processing.
ippStsNotEvenStepErr	Step value is not pixel multiple.
ippStsHistoNofLevelsErr	Number of levels for histogram is less than 2.
ippStsLUTNofLevelsErr	Number of levels for LUT is less than 2.
ippStsMP4BitOffsetErr	Incorrect value for bit offset.
ippStsMP4QPErr	Incorrect value for quantization parameter.
ippStsMP4BlockIdxErr	Incorrect value for block index.
ippStsMP4BlockTypeErr	Incorrect block type.
ippStsMP4MVCodeErr	Illegal Huffman code is detected during MV stream processing.
ippStsMP4VLCCodeErr	Illegal Huffman code is detected during VLC stream processing.
ippStsMP4DCCodeErr	Illegal code is detected during DC stream processing.
ippStsMP4FcodeErr	Incorrect value for fcode.
ippStsMP4AlignErr	Incorrect buffer alignment.
ippStsMP4TempDiffErr	Incorrect temporal difference.
ippStsMP4BlockSizeErr	Incorrect size of block or macroblock.
ippStsMP4ZeroBABErr	All BAB values are equal to zero.
ippStsMP4PredDirErr	Incorrect prediction direction.
ippStsMP4BitsPerPixelErr	Incorrect number of bits per pixel.
ippStsMP4VideoCompModeErr	Incorrect video component mode.
ippStsMP4LinearModeErr	Incorrect DC linear mode.
ippStsH263PredModeErr	Incorrect value for Prediction Mode.
ippStsH263BlockStepErr	The step value is less than 8.
ippStsH263MBStepErr	The step value is less than 16.
ippStsH263FrameWidthErr	The frame width is less than 8.
ippStsH263FrameHeightErr	The frame height is less than, or equal to zero.
ippStsH263ExpandPelsErr	The expand pixels number is less than 8.
ippStsH263PlaneStepErr	Step value is less than the plane width.
ippStsH263QuantErr	Quantizer value is less than, or equal to zero, or more than 31.
ippStsH263MVCodeErr	Illegal Huffman code is detetcted during MV stream processing.
ippStsH263VLCCodeErr	Illegal Huffman code is detetcted during VLC stream processing.
ippStsH263DCCodeErr	Illegal code is detetcted during DC stream processing.
ippStsH263ZigzagLenErr	Zigzag compact length is more than 64.
ippStsJPEGHuffTableErr	JPEG Huffman table is destroyed.
ippStsJPEGDCTRangeErr	JPEG DCT coefficient is out of range.
ippStsJPEGOutOfBufErr	An attempt to access out of the buffer.
ippStsChannelOrderErr	Incorrect order of the destination channels.
ippStsZeroMaskValueErr	All values of the mask are equal to zero.
ippStsRangeErr	Incorrect values for bounds: the lower bound is greater than the upper bound.
ippStsQPErr	Incorrect value for a quantizer parameter.
ippStsQuadErr	The quadrangle is nonconvex or degenerates into triangle, line, or point.
ippStsRectErr	Size of the rectangular region is less than, or equal to 1.
ippStsCoeffErr	Incorrect values for the transformation coefficients.
ippStsNoiseValErr	Incorrect value for the noise amplitude for dithering.
ippStsDitherLevelsErr	Number of dithering levels is out of range.
ippStsNumChannelsErr	Incorrect or unsupported number of channels.
ippStsDataTypeErr	Incorrect or unsupported data type.
ippStsCOIErr	COI is out of range.
ippStsOutOfRangeErr	Argument is out of range or point is outside the image.
ippStsDivisorErr	Divisor is equal to zero, function is aborted.
ippStsAlphaTypeErr	Illegal type of image composition operation.
ippStsGammaRangeErr	Gamma range bound is less than, or equal to zero.
ippStsGrayCoefSumErr	Sum of the conversion coefficients must be less than, or equal to 1.
ippStsChannelErr	Illegal channel number.
ippStsJaehneErr	Magnitude value is negative.
ippStsStepErr	Step value is less than, or equal to zero.
ippStsStrideErr	Stride value is less than the row length.
ippStsEpsValErr	Negative epsilon value.
ippStsScaleRangeErr	Scale bounds are out of range.
ippStsThresholdErr	Invalid threshold bounds.
ippStsWtOffsetErr	Invalid offset value for the wavelet filter.
ippStsAnchorErr	Anchor point is outside the mask.
ippStsMaskSizeErr	Invalid mask size.
ippStsShiftErr	Shift value is less than zero.
ippStsSampleFactorErr	Sampling factor is less than, or equal to zero.
ippStsResizeFactorErr	Resize factor(s) is less than, or equal to zero.
ippStsDivByZeroErr	An attempt to divide by zero.
ippStsInterpolationErr	Invalid interpolation mode.
ippStsMirrorFlipErr	Invalid flip mode.
ippStsMoment00ZeroErr	Moment value M(0,0) is too small to continue calculations.
ippStsThreshNegLevelErr	Negative value of the level in the threshold operation.
ippStsContextMatchErr	Context parameter does not match the operation.
ippStsFftFlagErr	Invalid value of the FFT flag parameter.
ippStsFftOrderErr	Invalid value of the FFT order parameter.
ippStsMemAllocErr	Not enough memory for the operation.
ippStsNullPtrErr	Pointer is NULL.
ippStsSizeErr	Wrong value for the data size.
ippStsBadArgErr	Invalid or bad argument.
ippStsNoErr	No errors.
ippStsNoOperation	No operation has been executed.
ippStsMisalignedBuf	Misaligned pointer in operation in which it must be aligned.
ippStsSqrtNegArg	Negative value(s) of the argument in the function Sqrt.
ippStsInvZero	INF result. Zero value was met by InvThresh with zero level.
ippStsEvenMedianMaskSize	Even size of the Median Filter mask was replaced by the odd number.
ippStsDivByZero	Zero value(s) of the divisor in the function Div .
ippStsLnZeroArg	Zero value(s) of the argument in the function Ln.
ippStsLnNegArg	Negative value(s) of the argument in the function Ln.
ippStsNanArg	Argument value is not a number.
ippStsDoubleSize	Sizes of image are not multiples of 2.
ippStsJPEGMarker	JPEG marker in the bitstream.
ippStsResFloor	All result values are floored.
ippStsAffineQuadChanged	The fourth ertex of destination quad is not equal to the customer's one.
ippStsWrongIntersectROI	Incorrect ROI that has no intersection with the source or destination image. No operation.
ippStsWrongIntersectQuad	Incorrect quadrangle that has no intersection with the source or destination ROI. No operation.
ippStsSymKernelExpected	The kernel is not symmetric.
ippStsEvenMedianWeight	Even weight of the Weighted Median Filter was replaced by the odd one.
ippStsNoAntialiasing	The mode does not support antialiasing.
ippStsAlgTypeErr	The algorithm type is not supported.
ippStsAccurateModeNotSupported	Accurate mode is not supported.
```

ipp函数命名规则

```
ipp<数据域><名称>_<数据类型描述符>][<_扩展名>]（<参数>）;
ipp<data-domain><name>_<datatypedescriptor>][<_extension>](<parameters>);
```

data-domain

| data-domain |                                                              |
| ----------- | ------------------------------------------------------------ |
| **s**       | for signals (expected data type is a 1D signal)              |
| **i**       | for images and video (expected data type is a 2D image)      |
| m           | for matrices (expected data type is a matrix)                |
| **r**       | for realistic rendering functionality and 3D data processing (expected data type depends on supported rendering techniques) |
| g           | for signals of fixed length                                  |

代码测试：cv::rectangle() 和IPP内函数，rectangle初步测试一致

代码

```
cout << "ippiNorm : "<<ippiNorm << endl;
cout << "ippiNormNone : "<<ippiNormNone << endl;
//ippiNorm : 256
//ippiNormNone : 0

// a|=b，实际上就是a=a|b 是一个位或运算,是二进制运算,数字相同时结果为0,不同十为1
```





常用函数

```
Mat img = imgIn.clone()
img.type() 获取数据类型
if (CV_32FC1 != img.type()){}
```

随机整数

```c++
mutable int var; // 随机整数
```

类的注意事项

1. ##### 注意无参构造不需要加(),不报错也没有原因显示,待研究问题

2. 类可以有多个构造函数，有且仅有一个析构函数

```c++
#include <iostream>
class A
{
public:
    int b;
    A(){
    b = 123;
    std::cout << "------a-------" << std::endl; //实际上调用的是func.operator()(i)这个函数
    }
    int operator() (int value) //重载()运算符，传入int的参数，
    // 所谓的重载可以理解为定义了一个函数，就是()函数
    {
    std::cout << "b :"<<b << std::endl; //实际上调用的是func.operator()(i)这个函数
    return 100;
    }
}; // 类后面需要加;
 
int main()
{
    int i = -1;
    A func; // 构造函数已经执行,无参构造不能加(),切记
    std::cout << func(i) << std::endl; //实际上调用的是func.operator()(i)这个函数
    return 0;
}
```

比较迷惑的案例，相比较上面案例

```c++
#include <iostream>
class A
{
public:
    int b;
    A(){
    b = 123;
    std::cout << "------a-------" << std::endl; //实际上调用的是func.operator()(i)这个函数
    }
    A(int m){
    b = m;
    std::cout << "------a-------" << std::endl; //实际上调用的是func.operator()(i)这个函数
    }
    int operator() (int value) //重载()运算符，传入int的参数，
    // 所谓的重载可以理解为定义了一个函数，就是()函数
    {
    std::cout << "执行了重载函数 :"<<b << std::endl; //实际上调用的是func.operator()(i)这个函数
    return 100;
    }
}; // 类后面需要加;
 
int main()
{
    int i = -1;
    A func(129); // 这里执行了有参构造，这是构造函数
    std::cout << func(i) << std::endl; //实际上调用的是func.operator()(i)这个函数
    return 0;
}
```





在C/C++中，在使用[预编译](https://so.csdn.net/so/search?q=预编译&spm=1001.2101.3001.7020)指令**#include**的时候，为了防止重复引用造成二义性，通常有两种方式

方式一

```C++
#ifndef _CODE_BLOCK
#define _CODE_BLOCK
 
// code
 
#endif// _CODE_BLOCK 
```

方式二

```c++
#pragma onceclea
```





docker 查看卷

```shell
docker volume ls
```











C++中的链表是数据域和指针域构成

```
// 单项链表包括数据和指针，这个指针又指向的结构体
struct ListNode
{
	int data;
	ListNode* next;//结构体指针
    // ListNode(int x) : val(x), next(NULL) {}  // 节点的构造函数
};
```







### const 主要作用

1. 修饰类型、值，具有只读性不可更改
2. 便于编译器做检查
3. 运行效率高
4. 类的const，即常函数，不能修改类的成员变量



### static 主要作用

1. 函数体内static变量的作用范围为该函数体，该变量的内存只被分配一次，其值在下次调用时仍维持上次的值
2. 在模块内的static全局变量，仅仅模块内使用
3. 类中的static成员变量属于整个类所拥有，对类的所有对象只有一份拷贝
4. static成员函数，只能用类名字访问，不能用this
5. 出现在类体外的函数定义不能指定关键字static
6. 使用静态数据成员可以节省内存









可以学习的几个方向：

1、linux内核

2、[消息队列中间件---视频教程](https://www.bilibili.com/video/BV164411G7aB/?p=2&spm_id_from=pageDriver)

3、cuda编程







### activteMQ

1. api接受发送
2. MQ高可用
3. MQ的集群和容错配置
4. MQ持久化
5. 延时发送/定时投递
6. 签收机制
7. spring整合

能解决的问题

1. 解耦
2. 削峰
3. 异步

linux命令

```shell
ps -ef #查看进程的，显示的是进程号
netstat -anp | grep 61616 #查看的是端口号
grep -v grep #屏蔽grep
lsof -i 61616
```

附：[消息队列中间件---视频教程](https://www.bilibili.com/video/BV164411G7aB/?p=2&spm_id_from=pageDriver)

