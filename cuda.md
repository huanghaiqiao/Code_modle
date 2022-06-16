一、查看cuda版本

```python
import torch
print(torch.version.cuda)
```

二、nvcc是cuda的编译器, 查看版本
```shell
nvcc --version
```

三、nvidia-smi可以监控GPU状态

```shell
nvidia-smi
```


参考：https://zhuanlan.zhihu.com/p/91334380
