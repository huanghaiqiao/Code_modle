一、docker构建容器时的代理

```
mkdir ~/.docker
touch config.json
```

修改文件config.json

```
{
 "proxies":
 {
   "default":
   {
     "httpProxy": "http://child-prc.intel.com:913",
     "httpsProxy": "http://child-prc.intel.com:913",
     "noProxy": "localhost,127.0.0.1"
   }
 }
}

```

二、docker下拉pull的代理

```
mkdir -p /etc/systemd/system/docker.service.d
touch http-proxy.conf
```

修改文件http-proxy.conf

```
# 添加
# SPDX-License-Identifier: Apache-2.0
# Copyright (c) 2019-2020 Intel Corporation

[Service]
Environment="HTTP_PROXY=http://child-prc.intel.com:913"
Environment="HTTPS_PROXY=http://child-prc.intel.com:913"
Environment="NO_PROXY=see-prc-renlefu-ci-pwek-server-2,127.0.0.1,10.240.224.51,192.168.51.1,172.18.0.1,localhost,virt-api,.svc,.svc.cluster.local,cdi-api,127.0.0.1,10.96.0.0/12,10.32.0.0/12,10.32.0.0/12,172.32.1.0/12,localhost,virt-api,.svc,.svc.cluster.local,cdi-api,127.0.0.1,10.96.0.0/12,10.32.0.0/12,10.245.0.0/16,10.67.115.240,10.67.115.43,NONE"
```

操作完毕，执行

```
# 更新配置
systemctl daemon-reload
# 重启
systemctl restart docker
```

