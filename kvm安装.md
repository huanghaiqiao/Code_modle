```shell
# 安装kvm加速检查
sudo apt-get install cpu-checker
# 系统是否可以使用 KVM 加速
sudo kvm-ok
```

kvm安装步骤：https://phoenixnap.com/kb/ubuntu-install-kvm

远程控制图形界面：https://www.cnblogs.com/conefirst/articles/15401996.html

```shell
windowns 远程ubuntu
# ubuntu 安装
sudo apt-get install tightvncserver xrdp
# 图新界面隐藏，需要按 win + A 案件
```



目前遇到以下问题没有解决，登录账号就是超级用户，没有出现问题，建议使用mobaxterm

```
huanghaiqiao@huanghaiqiao-NUC8i7HVK:/home/hq$ virt-manager
huanghaiqiao@huanghaiqiao-NUC8i7HVK:/home/hq$ MoTTY X11 proxy: Unsupported authorisation protocol
Unable to init server: Could not connect: Connection refused
MoTTY X11 proxy: Unsupported authorisation protocol
Unable to init server: Could not connect: Connection refused
MoTTY X11 proxy: Unsupported authorisation protocol
Unable to init server: Could not connect: Connection refused
```

```
huanghaiqiao@huanghaiqiao-NUC8i7HVK:/home/hq$ virt-manager 
huanghaiqiao@huanghaiqiao-NUC8i7HVK:/home/hq$ No protocol specified
Unable to init server: Could not connect: Connection refused
No protocol specified
Unable to init server: Could not connect: Connection refused
No protocol specified
Unable to init server: Could not connect: Connection refused
(virt-manager:3731): Gtk-WARNING **: 06:20:33.809: cannot open display: :11.0
```

