CV2

```c++
cv::Mat color_image = cv::imread(source_path, cv::IMREAD_COLOR);// 彩色图片
cout << Mat << endl; // 可以直接打印所有数据
cout << color_image.rows << endl; // 行列数
cout << color_image.cols << endl; 

if (!color_image.data)
    return -1;

uchar val = mat_CV_8UC1.at<uchar>(nrow,ncol); // 单通道获取数据

cv::namedWindow("image", 0);  // 定义一个窗口
cv::resizeWindow("image", 500, 500); // 定义窗口尺寸
cv::imshow("image", color_image); // 显示图片
cv::waitKey(); // 等待

// 很奇怪的定义"image"，可以在其他函数直接使用

cv::format(image, cv::Formatter::FMT_C) << ";" << std::endl // 按照指定格式打印所有数据
```
opencv数据类型

```c++
Mat::depth() // 获取的是通道的数据类型，而常用的数据类型又会宏定义成数字
#define CV_8U   0
#define CV_8S   1
#define CV_16U  2
#define CV_16S  3
```

Mat.at\<uchar\>(x, y)获取灰度图值(单通道)，对应数据类型

```c++
Mat.at<uchar>———CV_8U
Mat.at<char>———–CV_8S
Mat.at<short>———CV_16S
Mat.at<ushort>——–CV_16U
Mat.at<int>———–CV_32S
Mat.at<float>———-CV_32F
Mat.at<double>——–CV_64F
```

三通道获取值

```c++
int main()
{
	Mat src = Mat::zeros(5, 5, CV_8UC3);//建立一个三通道的图像
	cout << "src"<<endl<<src << endl;
	Vec3b i = src.at<Vec3b>(2, 2);//这里用了mat.at<Vec3b>(2,2),返回一个Vec3b类型的数组
	cout << "i" << endl << i << endl;
	int a = (int)i[0];//因为Vec3b是uchar型，i[0]中是\0，就是空格。这里要转换为int
	cout << a << endl;
	waitKey(0);
	return 0;
}
//这种方法访问速度很慢，使用mat.ptr<uchar>(i,j)(单通道） mat.ptr<vec3b>(i,j) （3通道）会快很多
```
