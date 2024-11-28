#!/bin/bash
set -e
# 默认值
output="output.txt"
verbose=0

function MS_Usage() {
    # 函数体
    cat <<EOF
Usage:  [--verbose] [--output output_file] [--help]
Options:
  -h, --help      显示帮助信息并退出
  -c, --compile   重新编译文件
  -o, --output    指定输出文件名，默认为 output.txt
EOF
}

function MAKE_FLOAD() {
    folder=$1
    # 判断文件夹是否存在
    if [ -d "$folder" ]; then
        # 如果文件夹存在，则删除文件夹及其中的所有内容
        rm -rf "$folder"
        echo "文件夹已删除：$folder"
    fi
    mkdir -p "$folder"
}

while true; do
    case "$1" in
    -c | --compile)
        COMPILE=true
        shift
        ;;
    -h | --help)
        MS_Usage
        break
        ;;
    -* | *)
        echo Unrecognized flag : "$1"
        MS_Usage
        break
        ;;
    esac
done

# 创建build文件夹
MAKE_FLOAD "build"
# 编译文件
if [ "$COMPILE" = true ]; then
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=$(pwd)/../ ..
    # make
    make install
    cd ../output
    ./test_merge
    # 判断文件夹是否存在
    if [ -d "coverage_report" ]; then
        # 如果文件夹存在，则删除文件夹及其中的所有内容
        rm -rf "coverage_report"
        echo "文件夹已删除: coverage_report"
    fi
    lcov --capture --directory $(pwd)/../build/ --output-file coverage_full.info
    lcov --remove coverage_full.info '*/c++/9/*' '*/gtest/*' '*/nlohmann/*' --output-file coverage_filtered.info
    genhtml coverage_filtered.info --output-directory coverage_report
    echo "http://10.110.17.233:8000/coverage_report/"
    nohup python -m http.server 8000 --directory coverage_report &
fi
