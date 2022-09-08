#include <iostream>
using namespace std;

int *fun(int *array_a, int *array_b, int *array_c, int len_a, int len_b, int len_c){
    int i = 0, j = 0, m = 0;  //多变量赋值

    while (i < len_a && j < len_b) //且语句&&
    {
        if (array_a[i] <= array_b[j]){
            array_c[m] = array_a[i];
            i++;
        }
        else{
            array_c[m] = array_b[j];
            j++;
        }
        m++;
    }

    if (i == len_a){
        for(int m_tmp=j; m_tmp<len_b; m_tmp++){
                // cout << " ===i=" << i << endl;
                cout << " ===j=" << j << endl;
                cout << " ===len_b=" << len_b << endl;
            array_c[m] = array_b[m_tmp];
            m++;
        }
    }
    else{
        for(int n_tmp=i;n_tmp < len_a;n_tmp++){
            array_c[m] = array_a[n_tmp];
            m++;
        }
    }

    return array_c;
}

int main(){

    // 合并两个有序数组
    int array_a[] = {1,2,3,4,6,9,11,14};
    int array_b[] = {2,2,3,4,6,9,80,123,333,666};
    int len_a = sizeof(array_a)/sizeof(int);
    int len_b = sizeof(array_b)/sizeof(int);
    int len_a_and_b = len_a + len_b;
    int array_c[len_a_and_b] = {0};

    int * result = fun(array_a, array_b, array_c, len_a, len_b, len_a_and_b);
    // 打印最终结果
    for(int n=0; n<len_a_and_b; n++){

        cout << " " << result[n];
    }
    cout << " " << endl;

    cout << "n " << n <<endl;

}

/************
此次代码出现错误：
1、for循环三个值不能少，缺一不可,for 循环临时变量仅限于循环，例如n
2、int 必须赋初值
3、注释内容需要关注
4、调试代码步骤，g++ -g ../test1.cpp -o hello; gdb ./hello
*************/
