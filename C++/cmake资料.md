### CMakeLists.txt常见问题

一、常见格式

```cmake
cmake_minimum_required(VERSION 3.11) # 缺报错
project(ProjectName) # 缺报错
add_executable(test test.cpp)
```

二、增加gdb调试

```cmake
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
```

三、指定编译器位置

```cmake
SET(CMAKE_C_COMPILER "/usr/bin/gcc")
```

