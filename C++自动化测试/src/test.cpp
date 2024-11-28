#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>
#include "demo.h"

#define NUM 10
#define MAX_ELEMENT_NUM 20

using namespace std;
static int testCaseCount = -1;
static std::vector<std::vector<std::string>> csv_msg;
typedef std::pair<std::string, std::vector<int>> TestParam;
static nlohmann::json data_json;
// static int csv_row = 0;
// static int csv_clo = 0;

// 从配置文件中读取测试参数集合
std::vector<std::pair<std::string, std::vector<int>>> GetTestValuesFromConfig(const std::string &configFile)
{
    std::map<std::string, std::vector<int>> testcase_key_value;
    std::vector<int> test_case_id;
    std::vector<std::pair<std::string, std::vector<int>>> m;
    std::ifstream file(configFile);
    // 检查文件是否成功打开
    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
        exit(-1);
    }

    // 读取并忽略表头（第一行）
    // std::string header;
    // std::getline(file, header);

    // 逐行读取文件
    std::string line;
    int line_num = 0;
    std::vector<int> index = {0, 0};
    while (std::getline(file, line))
    {
        // cout << line << endl;

        // 使用 stringstream 处理每一行
        std::stringstream line_stream(line);
        std::vector<std::string> every_line;
        std::string every_cell;
        // std::vector<int> index = {0, 0};

        // 使用逗号分隔每个值
        while (std::getline(line_stream, every_cell, ','))
        {
            every_line.push_back(every_cell);
        }
        every_line.pop_back();
        csv_msg.push_back(every_line);

        if (every_line[0].size())
        {
            if (testcase_key_value.find(every_line[0]) != testcase_key_value.end())
            {
                index[1] = line_num;
            }
            else
            {
                index[0] = line_num;
                index[1] = line_num;
            }

            if (line_num == 0)
            {
            }
            else
            {
                testcase_key_value[every_line[0]] = index;
            }
        }
        line_num++;
    }
    cout << csv_msg.size() << endl;
    // 遍历字典并打印元素
    for (const auto &kv : testcase_key_value)
    {
        std::cout << "键: " << kv.first << ", 值: ";
        test_case_id.push_back(1);
        m.push_back(kv);
        for (int num : kv.second)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    return m;
}

void write()
{
    std::ofstream file("result.csv");
    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
        exit(-1);
    }
    for (const auto &ever_line : csv_msg)
    {
        std::vector<std::string> line;
        for (int index = 0; index < ever_line.size(); index++)
        {
            file << ever_line[index];
            if (index != (ever_line.size() - 1))
            {
                file << ",";
            }
        }
        file << endl;
    }
}

template <typename T>
T test_add(const T &a, const T &b)
{
    return (a + b);
}

// string print_zones(const headlampCtlMsg *zones)
// {
//     string info_tmp = "";
//     string info_sum = "";
//     // cout << "Darkzones: { ";
//     for (int i = 0; i < MAX_ELEMENT_NUM; i++)
//     {
//         if (zones[i].DarkAreaAglHonStat == 0 &&
//             zones[i].DarkAreaAglHonEnd == 0)
//         {
//             continue;
//         }
//         info_tmp = to_string(i) + ": [V" + to_string(zones[i].veh_id) + ", " +
//                    to_string(zones[i].DarkAreaAglHonStat) + "," +
//                    to_string(zones[i].DarkAreaAglHonEnd) + ",d" +
//                    to_string(zones[i].distanc) + ",type" +
//                    to_string(zones[i].dynamicLight_type) + ",Mode" +
//                    to_string(zones[i].GfaSetMode) + "]; ";
//         // cout << i << ": [V" << zones[i].veh_id << ", "
//         //      << zones[i].DarkAreaAglHonStat << "," << zones[i].DarkAreaAglHonEnd
//         //      << ",d" << zones[i].distanc << ",type"
//         //      << zones[i].dynamicLight_type << "]; ";
//         info_sum += info_tmp;
//     }
//     // cout << info_tmp;
//     // cout << " }" << endl;
//     return info_sum;
// }

// 定义一个参数化测试类
class MyParametrizedTest : public ::testing::TestWithParam<TestParam>
{
public:
    TestParam test_param;
    // headlampCtlMsg multi_inputs[NUM][MAX_ELEMENT_NUM];
    // headlampCtlMsg result[NUM][MAX_ELEMENT_NUM];
    int statu_HighWay = 0;

private:
    void SetUp() override
    {
        // std::memset(multi_inputs, 0, sizeof(multi_inputs));
        // std::memset(result, 0, sizeof(result));
        test_param = GetParam();
        // cout << test_param.first << "," << test_param.second[0] << "," << test_param.second[1] << endl;
        statu_HighWay = std::stoi(csv_msg[test_param.second[0]][10]);
        for (int index = test_param.second[0]; index <= test_param.second[1]; index++)
        {
            int row = std::stoi(csv_msg[index][2]);
            int col = std::stoi(csv_msg[index][3]);
            int veh_id = std::stoi(csv_msg[index][4]);
            int DarkAreaAglHonStat = std::stoi(csv_msg[index][5]);
            int DarkAreaAglHonEnd = std::stoi(csv_msg[index][6]);
            int distanc = std::stoi(csv_msg[index][7]);
            int dynamicLight_type = std::stoi(csv_msg[index][8]);
            int GfaSetMode = std::stoi(csv_msg[index][9]);

            // multi_inputs[row][col].veh_id = veh_id;
            // multi_inputs[row][col].DarkAreaAglHonStat = DarkAreaAglHonStat;
            // multi_inputs[row][col].DarkAreaAglHonEnd = DarkAreaAglHonEnd;
            // multi_inputs[row][col].distanc = distanc;
            // multi_inputs[row][col].dynamicLight_type = dynamicLight_type;
            // multi_inputs[row][col].GfaSetMode = GfaSetMode;
        }
        testCaseCount++;
        // cout << "[info]: 测试用例序号： " << testCaseCount << endl;
    }

    void TearDown() override
    {
        const ::testing::TestInfo *const test_info =
            ::testing::UnitTest::GetInstance()->current_test_info();
        // data_json[test_param.first]["Status"] = (test_info->result()->Passed() ? "Passed" : "Failed");
        string Status = test_info->result()->Passed() ? "Passed" : "Failed";
        data_json[test_param.first]["Status"] = Status;
        data_json[test_param.first]["statu_HighWay"] = statu_HighWay;
        csv_msg[test_param.second[0]].insert((csv_msg[test_param.second[0]]).end(), Status);
        if (test_info->result()->Failed())
        {
            string msg = test_info->result()->GetTestPartResult(0).message();
            data_json[test_param.first]["Failure"] = msg;
        }

        for (int i = 0; i < NUM; ++i)
        {
            // std::string string_tmp = print_zones(result[i]);
            // data_json[test_param.first]["output_status_" + to_string(i)] = string_tmp;
        }

        for (int i = 0; i < NUM; ++i)
        {
            // std::string string_tmp = print_zones(multi_inputs[i]);
            // data_json[test_param.first]["input_status_" + to_string(i)] = string_tmp;
        }
    }
};

// 注册测试实例
INSTANTIATE_TEST_CASE_P(MyParametrizedTests, MyParametrizedTest,
                        ::testing::ValuesIn(GetTestValuesFromConfig("../testcase/input.csv")));

// 定义参数化测试案例
TEST_P(MyParametrizedTest, MyTestCase)
{
    int a = 1;
    int b = 2;
    std::cout << "a+b=" << std::endl;
    add_num(a, b);
    // addOrConcatenate<int, int>(a, b);
    // test_param = GetParam();
    // 获取所需要的执行时间
    float run_time = std::stof(csv_msg[test_param.second[0]][1]);
    cout << run_time << endl;

    std::chrono::duration<double> elapsed_seconds;
}

// 运行测试
int main(int argc, char **argv)
{
    std::ofstream file("result.json");
    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
        exit(-1);
    }
    ::testing::InitGoogleTest(&argc, argv);
    int test_result = RUN_ALL_TESTS();
    file << std::setw(4) << data_json;
    write();
    return test_result;
}
