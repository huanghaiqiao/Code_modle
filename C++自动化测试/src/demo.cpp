#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <cstring> // 引入 <cstring> 以使用 std::strcmp
#include <vector>

// 自定义参数
std::string custom_arg;

void PrintHelp()
{
    std::cout << "自定义参数解析" << std::endl;
    std::cout << "参数解析" << std::endl;
    std::cout << "-i file_path: 输入测试用例" << std::endl;
}

// 自定义参数解析函数
void ParseArguments(int argc, char **argv)
{
    int second_arg_index = 0;
    bool second_arg_found = false;
    std::string second_arg_str;
    for (int i = 1; i < argc; i++)
    {
        second_arg_index = i + 1;
        if (second_arg_index < argc && argv[second_arg_index][0] != '-')
        {
            second_arg_found = true;
            second_arg_str = argv[second_arg_index];
        }

        if (std::strcmp(argv[i], "--help") == 0)
        {
            std::cout << "自定义参数解析" << std::endl;
            break;
        }

        std::cout << "参数：" << argv[i] << std::endl;
        // else if (arg == "-o")
        // {

        //     break;
        // }
        // else if (arg.find("-o") == 0) {
        //     std::string value = arg.substr(17);  // 提取参数值
        //     std::cout << "Custom argument value: " << value << std::endl;
        // }
        // else if (arg == "--version") {
        //     std::cout << "Version 1.0.0\n";
        // }
        // else {
        //     std::cout << "Unknown argument: " << arg << std::endl;
        // }
    }
}

// 测试用例示例
TEST(SampleTest, CheckCustomArg)
{
    // EXPECT_FALSE(custom_arg.empty()) << "Custom argument --my_custom_arg was not provided!";
    // EXPECT_FALSE(another_custom_arg.empty()) << "Custom argument --another_custom_arg was not provided!";
    // std::cout << "Custom argument --my_custom_arg: " << custom_arg << std::endl;
    // std::cout << "Custom argument --another_custom_arg: " << another_custom_arg << std::endl;
}

int main(int argc, char **argv)
{
    // 解析自定义参数
    ParseArguments(argc, argv);

    // 初始化 Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // // 打印自定义参数值（仅示例）
    // if (!custom_arg.empty())
    // {
    //     std::cout << "Custom argument value --my_custom_arg: " << custom_arg << std::endl;
    // }
    // if (!another_custom_arg.empty())
    // {
    //     std::cout << "Custom argument value --another_custom_arg: " << another_custom_arg << std::endl;
    // }

    // 运行测试
    return RUN_ALL_TESTS();
}
