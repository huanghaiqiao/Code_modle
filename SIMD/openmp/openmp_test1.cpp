#include <iostream>
#include <chrono>


int fun(int *a, int N){
    // clock_t t3 = clock();
    auto start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for num_threads(N)
    for (int i=0; i<102400; i++){
        // cout<< "this is  Thread " << omp_get_thread_num() << " "<<  i << endl;
        a[i] = i*i + i*2;
        // cout << i << endl;
    }
    // clock_t t4 = clock();
    auto stop = std::chrono::high_resolution_clock::now();

    cout << "开启优化线程数：" << N << "  --";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count() << "毫秒" <<endl;
    return 0;

}

int main(int argc, char **argv){
    int a[102400] = {0};
    auto start = std::chrono::high_resolution_clock::now();
    for (int i=0; i<102400; i++){
        a[i] = i*i + i*2; 
    }
    auto stop = std::chrono::high_resolution_clock::now();
    cout << "原始算法：";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count() << "毫秒" <<endl;


    for(int i=0; i<1000; i++){
        fun(a, i);
    }
    // fun(a, 100);
}
