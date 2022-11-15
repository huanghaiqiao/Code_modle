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

变量的声明

```
// 如果是定义的全局变量或者静态变量，未初始化的话就是0.如果是局部变量
static int n; //定义静态全局变量,外部使用extern int n 会报错
int n; //定义全局变量 ,使用extern int n 不会报错
```

c++存储区域

1. 栈区（先进后出），把它想象成水桶，栈桶
2. 堆区
3. 静态区（全局区），全局变量和静态变量（只初始化一次），在程序全部结束之后释放
4. 常量区
5. 代码区

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
#pragma once
```

链表的构造

```c++
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {} // 结构体构造函数
    ListNode(int x) : val(x), next(nullptr) {} // 有参构造
    ListNode(int x, ListNode *next) : val(x), next(next) {} 
};

student * creat_student(){
    student * head = new student;
    student * ptr = head;
    int num[5] = {2,3,4,5,9};
    int len = sizeof(num) / sizeof(int);
    std::cout << "总长度：" << len << endl;
    for(int i=0;i<len;i++){
        student * node = new student;
        node -> a = num[i];
        ptr -> next = node;
        ptr = node;
        ptr -> next = NULL;
        printf("%d \n",num[i]);
    }
    return head;
}

// 假如需要delete空间，需要删除所有的new
```
C++查看数据类型

```c++
#include <typeinfo>
#include <iostream>
 
using namespace std;
int main(){
   int iobj = 10; 
 
   cout << typeid( iobj ).name() << endl;  //  打印: int 
   cout << typeid( 8.16 ).name() << endl; // 打印: double      
   return 0;
}
```

数组指针

```c++
int array[] = {1,2,3,4,5};
int *array1 = new int[1,2,3,4,5];
// 注意：array表示数组也可是第一元素指针，sizeof，数组名就是整个数组长度
// new 出来的只是数组，不为数组，只是指针
```
注意

```
(float)(total_num - single_er_num) / total_num * 100 
// 注意必须只float第一个数就行了
```

踩坑
初始化函数最好有确定值
out_image.zeros(img_name.size(), img_name.type());
