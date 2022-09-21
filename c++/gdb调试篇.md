### gdb调试篇

程序编译增加gdb

```shell
gcc -g 1.c # c语言增加gdb调试
gcc -g hello.c -o hello -lstdc++ # C++ 增加gdb调试
g++ -g hello.cpp -o hello
```

gdb指令

```
run 缩写 r , 程序全部执行，若程序出错，或者已经打了断点，即可使用bt
bt 查看当前堆栈信息
c 继续执行
info b 查看断点信息
thread apply all bt full 显示所有线程
thread 1 选择线程1
p 打印信息
quit 退出
```

查看已经在运行的gdb程序

```shell
# 找到运行程序的进程号
ps -axu | grep a.out
# 直接进去程序，动态调试
gdb attch 830311
```

