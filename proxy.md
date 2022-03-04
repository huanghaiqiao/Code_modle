一、关于修改环境的系统文件

- "/etc/profile"
- "/etc/environment"
- "~/.bashrc"

```shell
exprot http_proxy=http://child-prc.intel.com:913 
exprot https_proxy=http://child-prc.intel.com:913
```

二、关于apt-get代理

```shell
touch "/etc/apt/apt.conf.d/proxy.conf"
Acquire::http::Proxy "http://child-prc.intel.com:913"; 
Acquire::https::Proxy "http://child-prc.intel.com:913";
```

二、关于网络
```shell
sudo apt-get install openssh-server
```
