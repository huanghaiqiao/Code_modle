参数：[oneapi入门简介](https://blog.csdn.net/qq_46009046/article/details/123306679)

参数：[DPC++并行计算](https://article.itxueyuan.com/XKM1AX)

参考：[开发参考指南](https://www.intel.com/content/www/us/en/develop/documentation/cpp-compiler-developer-guide-and-reference/search.html?q=_mm256_loadu_ps) 

参数：[chryswoods.com |第 2 部分：AVX 内部函数](https://chryswoods.com/vector_c++/immintrin.html)



[1、AVX指令集参考一](http://portal.nacad.ufrj.br/online/intel/compiler_c/common/core/index.htm#GUID-B225E659-E0AD-4AE2-8806-EC5FD0119B01.htm)

[2、AVX指令集参考二](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#text=_mm512_add_ps&ig_expand=4366,4369,4369,159&techs=AVX_512)



SIMD(**Single Instruction Multiple Data**)即单指令流多数据流



### AVX-2使用说明

一、__m256数据类型

float64在64位计算机系统占8字节，8 * 8 * 4 = 256 

float在64位计算机系统占4字节，4 * 8 * 8 = 256 

| 运算             | 注释                                                         |
| ---------------- | ------------------------------------------------------------ |
| _mm256_add_pd    | 4个float64 向量和4个float64 向量之间执行逐个元素的加法       |
| _mm256_add_ps    | 8个float向量和8个float 向量之间执行逐个元素的加法            |
| _mm256_addsub_pd | 4个float64 向量；偶数位相减，奇数位相加； A-B，A+B           |
| _mm256_addsub_ps | 8个float向量；偶数位相减，奇数位相加； A-B，A+B              |
| _mm256_hadd_pd   | 对源向量中的相邻（水平）双精度浮点元素（float64 元素）执行 SIMD 加法 |
| _mm256_hadd_ps   | 对源向量中的相邻（水平）单精度浮点元素（float32 元素）执行 SIMD 加法 |
| _mm256_sub_pd    | 4个float64 向量和4个float64 向量之间执行逐个元素的减法       |
| _mm256_sub_ps    | 8个float向量和8个float 向量之间执行逐个元素的减法            |
| _mm256_hsub_pd   | 对源向量中的相邻（水平）双精度浮点元素（float64 元素）执行 SIMD 减法 |
| _mm256_hsub_ps   | 对源向量中的相邻（水平）单精度浮点元素（float32 元素）执行 SIMD 减法 |
| _mm256_mul_pd    | 4个float64 向量和4个float64 向量之间执行逐个元素的乘法       |
| _mm256_mul_ps    | 8个float向量和8个float 向量之间执行逐个元素的乘法            |
| _mm256_div_pd    | 4个float64 向量和4个float64 向量之间执行逐个元素的除法       |
| _mm256_div_ps    | 8个float向量和8个float 向量之间执行逐个元素的除法            |
| _mm256_dp_ps     | todo                                                         |
| _mm256_sqrt_pd   | 4个float64向量求平方根                                       |
| _mm256_sqrt_ps   | 8个float向量求平方根                                         |
| _mm256_rsqrt_ps  | 执行源向量的八个单精度浮点元素的平方根的倒数计算             |
| _mm256_rcp_ps    | 执行源向量的八个单精度浮点元素的倒数计算                     |

附加计算图：_mm256_hadd_pd



![](https://github.com/huanghaiqiao/Code_modle/blob/master/Fig1.jpg)



二、按位运算

| 按位运算         | 注释                             |
| ---------------- | -------------------------------- |
| _mm256_and_pd    | 向量A和向量B按位AND，float64     |
| _mm256_and_ps    | 向量A和向量B按位AND，float       |
| _mm256_andnot_pd | 向量A和向量B按位AND NOT，float64 |
| _mm256_andnot_ps | 向量A和向量B按位AND NOT，float   |
| _mm256_or_pd     | 向量A和向量B按位OR，float64      |
| _mm256_or_ps     | 向量A和向量B按位OR，float        |
| _mm256_xor_pd    | 异或float64                      |
| _mm256_xor_ps    | 异或float                        |

三、混合条件合并

| 混合条件合并                                           | 注释                            |
| ------------------------------------------------------ | ------------------------------- |
| _mm256_blend_pd(_m256d m1, __m256d m2, const int mask) | 按mask位选A，B向量的值，float64 |
| _mm256_blend_ps(_m256 m1, __m256 m2, const int mask)   | 按mask位选A，B向量的值，float   |
| _mm256_blendv_pd(_m256d m1, _m256d m2, __m256d mask)   | 按mask位选A，B向量的值，float64 |
| _mm256_blendv_ps(_m256 m1, _m256 m2, __m256 mask)      | 按mask位选A，B向量的值，float   |

四、比较运算（to do）

| 比较运算                                                     | 注释 |
| ------------------------------------------------------------ | ---- |
| _m256d _mm256_cmp_pd(_m256d m1, __m256d m2, const int predicate) |      |
| _mm_cmp_sd                                                   |      |

五、数据转换，另有矢量类型转化

int64在64位计算机系统占8字节，8 * 8 * 4 = 256 

int在64位计算机系统占8字节，4 * 8 * 8= 256 

| 数据转换（有符号）                   | 注释                            |
| ------------------------------------ | ------------------------------- |
| _m256 _mm256_cvtepi32_pd(__m128i m1) | 4个int64转换为4个float64        |
| _m256 _mm256_cvtepi32_ps(__m256i m1) | 8个int转换8个float              |
| _mm256_cvtpd_epi32(__m256d m1)       | 4个float64转换为4个int64        |
| _mm256_cvtps_epi32(__m256 m1)        | 8个float转换8个int              |
| _mm256_cvtpd_ps(__m256d m1)          | 4个float64转换为8个float        |
| _mm256_cvtps_pd(__m128 m1)           | 4个float转换为4个float64        |
| _mm256_cvttpd_epi32（__m256d m1）    | 4个float64转换为4个int          |
| _mm256_cvttps_epi32(__m256 m1)       | 4个float64转换为4个int 提示异常 |
| _mm256_cvttps_epi32(__m256 m1)       | 8个float转换8个int，提示异常    |

六、比较

| 比较                                         | 注释                      |
| -------------------------------------------- | ------------------------- |
| _mm256_max_pd( _m256d m1, _m256d m2)         | 返回每对的最大值，float64 |
| _mm256_max_ps( _m256 m1, _m256 m2)           | 返回每对的最大值，float   |
| _m256d _mm256_min_pd( _m256d m1, __m256d m2) | 返回每对的最小值，float64 |
| _m256d _mm256_min_pd( _m256d m1, __m256d m2) | 返回每对的最小值，float   |

七、加载和存储，64位机，多为8字节对齐

| 加载和存储                                           | 注释                                                         |
| ---------------------------------------------------- | ------------------------------------------------------------ |
| _m256d _mm256_broadcast_pd(__m128d const *a)         | 加载 128 位 float64 值，并将其广播到目标 256 位向量中的两个元素 |
| _m256 _mm256_broadcast_ps(__m128 const *a)           | 加载 128 位 float32 值，并将其广播到目标 256 位向量中的所有元素 |
| _m256d _mm256_broadcast_sd(double const *a)          | 加载标量float64，并将其广播到目标向量中的所有四个元素        |
| _mm256_broadcast_ss(float const *a)                  | 加载的值广播到 256 位目标向量中的所有八个元素                |
| _mm_broadcast_ss(float const *a)                     | 加载的值广播到 128 位目标向量中的所有四个元素                |
| _mm256_load_pd(double const *a)                      | 256 位对齐内存位置加载到目标 float64 向量中                  |
| _mm256_load_ps(float const *a)                       | 256 位对齐内存位置加载到目标 float32 向量中                  |
| _mm256_load_si256(__m256i const *a)                  | 256 位对齐内存位置的整数值加载到目标整数向量中               |
| _mm256_loadu_pd(double const *a)                     | 256 位未对齐内存位置加载到目标 float64 向量中                |
| _mm256_loadu_ps(float const *a)                      | 256 位未对齐内存位置加载到目标 float64 向量中                |
| _mm256_loadu_si256(__m256i const *a)                 | 256 位未对齐内存位置加载到目标整数向量中                     |
| _mm_maskload_pd(double const *a, __m128i mask)       | 按照mask拷贝                                                 |
| _mm256_store_pd(double *a, __m256d b)                | 从 float64 向量移动到由指向的 256 位对齐的内存位置来执行存储操作 |
| _mm256_store_ps(float *a, __m256 b)                  | 从 float32 向量移动到 由 指向的 256 位对齐的内存位置来执行存储操作 |
| _mm256_stream_pd                                     | 从 float64 向量移动到指向256 位对齐内存位置来执行存储操作    |
| _mm_maskstore_pd(double *a, __m256i mask, __m128d b) |                                                              |

八、杂项操作

| 操作                                                   | 注释                                                         |
| ------------------------------------------------------ | ------------------------------------------------------------ |
| _mm256_extractf128_pd(__m256d m1, const int offset)    | 从参数中的值指定的位置开始，选取元素                         |
| _mm256_insertf128_pd(__m256d a, __m128d b, int offset) | 第二个源向量插入到目标位置，目标的其余部分由第一个源向量的相应元素写入 |
| _mm256_lddqu_si256(__m256i const *a)                   | 从参数指定的内存地址开始，获取 32 字节的数据，并将它们放在目标位置 |
| _mm256_movedup_pd(__m256d a）                          | 在源向量中执行偶数索引双精度浮点值（float64 值）的复制       |
| _mm256_movemask_pd(__m256d a)                          | 从源向量的四个双精度浮点元素（float64 元素）中执行符号位的提取操作 |
| _mm256_round_pd（__m256d a， int iRoundMode）          | 上下取整                                                     |
| _mm256_set_pd(double, double, double, double)          | 初始化矢量                                                   |
| _mm256_setr_pd(double, double, double, double)         | 按参数指定的相反顺序初始化 256 位矢量                        |
| _m256d _mm256_set1_pd(double)                          | 所有元素都设置为指定标量双精度浮点值的 float64 向量          |
| _mm256_setzero_pd(void)                                | 所有元素都设置为零的 float64 向量。                          |
| _mm256_zeroall(void)                                   | 将所有寄存器归零                                             |
| _mm256_zeroupper(void)                                 | 将所有寄存器的上 128 位归零。与寄存器对应的较低128位保持不变 |



### AVX-512使用说明

intel cpu需要11代后才能支持AVX-512，即16个数据计算

一、__m512数据类型

| 数据类型 | 注释                                                       |
| -------- | ---------------------------------------------------------- |
| __m512   | 单精度浮点向量（浮点 32 向量）                             |
| __m512i  | 一个整数 32 位向量或一个整数 64 位向量（int32/int64 向量） |
| __m512d  | 双精度浮点向量（浮点 64 向量）                             |

二、算法运算

1、加法运算

| 加法运算         | 注释                                               |
| ---------------- | -------------------------------------------------- |
| _mm512_add_epi32 | 在 int32 向量和 int32 向量之间执行逐个元素的加法   |
| _mm512_add_epi64 | 在 int64 向量和 int64 向量之间执行逐个元素的加法   |
| _mm512_add_pd    | 在 float64向量和 float64向量之间执行逐个元素的加法 |
| _mm512_add_ps    | 在 float32向量和 float32向量之间执行逐个元素的加法 |



向量归零，_mm512_setzero_{pd|ps|epi32}

| _mm512_setzero_{pd\|ps\|epi32}            |                                           |
| ----------------------------------------- | ----------------------------------------- |
| _mm512_setzero_ps                         | 返回所有元素都设置为零的类型向量。__m512  |
| _mm512_setzero_pd                         | 返回所有元素都设置为零的类型向量。__m512d |
| _mm512_setzero_epi32/_mm512_setzero_si512 | 返回所有元素都设置为零的类型向量。__m512i |

