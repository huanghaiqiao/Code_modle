[AVX和openmp参考资料](http://portal.nacad.ufrj.br/online/intel/compiler_c/common/core/index.htm#GUID-B225E659-E0AD-4AE2-8806-EC5FD0119B01.htm)

时间序列，openmp自带时间计算

```c++
#include <omp.h>
double t1 = omp_get_wtime();
double t2 = omp_get_wtime();
cout << "openmp time :" << t2-t1 <<endl;
```
