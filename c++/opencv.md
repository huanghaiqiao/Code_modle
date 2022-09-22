### opencv算法解析

[参考网址](https://blog.csdn.net/weixin_51229250/article/details/118975308)

```c++
matchTemplate(gray_image, template_image, result, cv::TemplateMatchModes::TM_CCORR_NORMED);
// cv::TemplateMatchModes::TM_CCORR_NORMED 归一化的相关性匹配方法,最佳匹配位置也是在值最大处
```

数学计算，T表示模板图形，I表示匹配图像
$$
R(x,y)={\sum_{\dot{x},\dot{y}} T(\dot{x},\dot{y}) * I(x + \dot{x},y+\dot{y}) - \frac{1}{w*h}  \sum_{\dot{x},\dot{y}} T(\dot{x},\dot{y}) * \sum_{\dot{x},\dot{y}}I(x + \dot{x},y+\dot{y})  \over \sqrt{\sum_{\dot{x},\dot{y}}T^2(\dot{x},\dot{y})-\frac{1}{w*h}(\sum_{\dot{x},\dot{y}}T(\dot{x},\dot{y}))^2} * \sqrt{\sum_{\dot{x},\dot{y}}I^2(x + \dot{x},y+\dot{y}))-\frac{1}{w*h}(\sum_{\dot{x},\dot{y}}I(x + \dot{x},y+\dot{y}))^2}}
$$
