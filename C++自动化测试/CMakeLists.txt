cmake_minimum_required(VERSION 3.10)

project(test_merge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

find_package(GTest REQUIRED)
aux_source_directory(${PROJECT_SOURCE_DIR} DIR_SOURCE)

#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

include_directories("include")



#add_executable(${PROJECT_NAME} ${DIR_SOURCE})
# add_executable(test_merge 
set(SOURCES
src/test.cpp
src/demo.cpp
)

# # 定义路径
# set(TEST_CASE_PATH "/home/user/data")

# # 将路径作为宏传递给代码
# target_compile_definitions(test_merge PRIVATE TEST_CASE_PATH=\"${TEST_CASE_PATH}\")

add_executable(test_merge ${SOURCES})

target_link_libraries(test_merge ${GTEST_BOTH_LIBRARIES} pthread gtest gcov)
# 打印安装目录（用于调试）
message(STATUS "安装目录: ${CMAKE_INSTALL_PREFIX}/output")
# 安装可执行程序
install(TARGETS test_merge DESTINATION output)
