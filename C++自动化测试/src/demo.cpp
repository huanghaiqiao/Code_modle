#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "demo.h"

// template <typename T, typename U>
// std::string addOrConcatenate(const T& a, const U& b) {
//     // 检查是否是数字
//     std::string str_a = std::to_string(a);
//     std::string str_b = std::to_string(b);
//     std::cout << "================================" << std::endl;
    
//     // 如果两个都是数字，执行加法
//     if (std::all_of(str_a.begin(), str_a.end(), ::isdigit) && std::all_of(str_b.begin(), str_b.end(), ::isdigit)) {
//         // 将字符串转为数字进行加法操作
//         double num_a = std::stod(str_a);  // 转换为 double
//         double num_b = std::stod(str_b);  // 转换为 double
//         double sum = num_a + num_b;
//         return std::to_string(sum);       // 返回加法结果
//     } else {
//         // 否则进行拼接
//         return str_a + str_b;
//     }
// }

int add_num(int a, int b){
    std::cout << "================================" << std::endl;
    if(a > b){
        return 0;
    }
    return a + b;
}

int add_minus(int a, int b){
    std::cout << "================================" << std::endl;
    return a - b;
}
