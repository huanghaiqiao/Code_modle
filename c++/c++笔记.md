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

typedef 使用

```c++
typedef int (*FUNC_P)(int, int); 
// 定义了一个函数指针类型，可以使用FUNC_P去定义指向函数的指针，其指向的函数类型必须是返回值为int、参数为两个且均为int
// 函数指针类型，替换
typedef int p;
// 函数指针类型，替换
```

函数指针

```c++
typedef int ( *func)(int , int); // 定义函数指针
int func2(int a, int b){
    return 0;
}
int main(int argc, char **argv){
	func func1 = func2; // 实例化函数指针指向
}
```

赋值

```c++
char * p = 
NULL;
```

三目运算符

```c++
int a = 1;
int b = 2;
int c = (a==b)?3:4;
// 成立输出3，不成立输出4
// <表达式1>?<表达式2>:<表达式3>
// 如果表达式1成立，则输出表达式2的值，否则输出表达式3的值
```

Q：static关键字的作用

A：静态变量在程序执行之前就创建，在程序执行的整个周期都存在。可以归类为如下五种：

局部静态变量：作用域仅在定义它的函数体或语句块内，该变量的内存只被分配一次，因此其值在下次函数被调用时仍维持上次的值；
全局静态变量：作用域仅在定义它的文件内，该变量也被分配在静态存储区内，在整个程序运行期间一直存在；
静态函数：在函数返回类型前加static，函数就定义为静态函数。静态函数只是在声明他的文件当中可见，不能被其他文件所用；
类的静态成员：在类中，静态成员属于整个类所拥有，对类的所有对象只有一份拷贝，因此可以实现多个对象之间的数据共享，并且使用静态数据成员还不会破坏隐藏的原则，即保证了安全性；
类的静态函数：在类中，静态成员函数不接收this指针，因而只能访问类的static成员变量，如果静态成员函数中要引用非静态成员时，可通过对象来引用。（调用静态成员函数使用如下格式：<类名>::<静态成员函数名>(<参数表>);）
原文链接：https://blog.csdn.net/qq_35034604/article/details/107959429

```c++
int func1(){
    static int a = 1;
    cout << "a = "  << a << endl;
    a++;
    return 0;
}

int main(){
    func1();
    func1();
}
// 输出a = 1
// a = 2
```

字节(64位系统)

| 数据类型           | 字节 | 位数 | 数据范围 |
| ------------------ | ---- | ---- | -------- |
| int (signed int)   | 4    | 32   |          |
| unsigned int       | 4    | 32   |          |
| float              | 4    | 32   |          |
| short int          | 2    | 16   |          |
| unsigned short int | 2    | 16   |          |
| long int           | 8    | 64   |          |
| double             | 8    | 64   |          |

C++ 进制打印

```c++
#include<bitset>
#include<iostream>
int main(){
    int c=0;
    bitset<8> a (1); // 有参构造
    std::cout<<a<<"\n";
    return 0;
}
// C++ 只有才能转化二进制bitset,<>内设置位数
```

dec 十进制，oct 八进制，hex 16进制

```C++
#include<iostream>
#include<bitset>
using namespace std;//必须得加上 
int main()
{
	int a=1000;
	cout<<"默认下"<<a<<endl;
	cout<<"十进制"<<dec<<a<<endl;
	cout<<"八进制"<<oct<<a<<endl;//八进制 
	cout<<"十六进制"<<hex<<a<<endl;	//十六进制 
	cout<<"二进制"<<bitset<16>(a)<<endl; //输出为十六位二进制数 
	return 0;
}
```

位运算

| 含义   | C++  | 注释                   |
| ------ | ---- | ---------------------- |
| 按位或 | a\|b | 全0才为0,其余情况均为1 |
| 按位与 | a&b  | 全1才为1,其余情况均为0 |
