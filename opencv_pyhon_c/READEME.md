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
