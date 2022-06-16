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
# 安装完英伟达驱动需要reboot重启才能查看，等待时间有点长
# 目前安装的是 nvidia-driver-510-server
nvidia-smi
```

四、查看显卡

```shell
lspci -nnk | grep '\[03'
lspci | egrep 'VGA|3D'
```

五、查看驱动

```shell
dpkg -l | grep nvidia
```

六、获取可安装的驱动

```shell
sudo ubuntu-drivers devices
```

七、删除软件，彻底

```shell
sudo apt --purge autoremove
```

八、查看内核

```shell
# 查看目前内核版本
uname -r
# 查看安装的内核
find /boot/vmli*
# 查看已经安装的内核
dpkg --list | grep linux-image

dir /nonexistent you specified can't be accessed

https://askubuntu.com/questions/1362970/problem-installing-nvidia-driver-on-ubuntu-20-04
```

遇到问题:

```
import tensorflow      #未找到 libcudart.so.11.0
# 解决 conda install cudatoolkit
```



参考：https://zhuanlan.zhihu.com/p/91334380

参考：[ubuntu20.04 source.list](https://gist.github.com/ishad0w/788555191c7037e249a439542c53e170)
