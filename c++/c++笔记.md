c++汇总

```
一、c++ 在定义变量就是在向内存申请空间，申请空间后才有指针
```



#### 符号

```c++
char a = '';
std::string b =""; // 字符串
char kk[] = "huanghaiqiaowoaini"; // 字符串
// 字符用单引号
// 字符串用双引号
```

#### 指针

```C++
// 输出a的地址
int a=1;
std::cout << &a << "\n";

// 打印地址
int m = 1;
int *a=&m;
std::cout << a << "\n";  // 注意：当为cha指针时候必须加(void *)才能输出指针

// 定义指针时候赋初值
int * a=nullptr;
int * b=0;  // 部分c++不赋初值，指针会是随机数

// 当定义void *指针时候，是不能更改里面的值
int m = 1;
void *a;
a = &m;
*a = 12; //直接报错，不允许修改，void *用于比较地址一样与否

// 二维
char **p // 二维指针
char *p  // 一维指针
```

指针数组

```c++
// 指针数组赋值
int  var[MAX] = {10, 100, 200};
int *ptr[MAX];
 
for (int i = 0; i < MAX; i++)
{
     ptr[i] = &var[i]; // 赋值为整数的地址
 }
// 赋值二，强记，它就是类似于，字符串列表
const char *names[MAX] = {
                   "Zara Ali",
                   "Hina Ali",
                   "Nuha Ali",
                   "Sara Ali",
 };
   for (int i = 0; i < MAX; i++)
   {
      cout << "Value of names[" << i << "] = ";
      cout << names[i] << endl;
   }
```

打印

```c++
std::cout << boolalpha;  //打印0，1为true false
```

数组

```c++
// 数组要么在定义时候全部赋值
int bv[2] = {1,2};
// 不然只能单个赋值
int bv[2];
bv[0]=1;
```

字节

```c++
int bv[2] = {1,2};
sizeof(bv)/sizeof(int); // 得到数组长度
```

声明一个指针，指向函数

```c++
float renderFrame() {
	return 0;
}
int main(int argc, char **argv){
    float (*f)();
    f = renderFrame;
}
```
注意错误

```c++
fun_new()
int fun_new(); // 编译器和执行都不会报错，但是下面这句fun_new没有执行
```

类python装饰器功能

```C++
/***
 * 类似python函数装饰器功能
 * 不改变函数情况下，增加性能测试
    ***/

#include <iostream>
#include <chrono>
using namespace std;
static int a[102400];

int fun(){
    for (int i=0; i<102400; i++){
        a[i] = i*i + i*2; 
    }
    return 0;
}

int fun_new(int (*f)()){
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count() << "微秒" <<endl;
    return 0;
}

int main(int argc, char **argv){
    fun_new(fun);
    return 0;
}
```

