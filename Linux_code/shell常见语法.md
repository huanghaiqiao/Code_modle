#### 一、shell头文件

```shell
#!/bin/bash 
```

#### 二、shell之if语句

```shell
if [ -e filename ];then
  echo "文件存在"
else
  echo "文件不存在"
fi
```

#### 三、shell之while语句

```shell
while [ $i -le 10 ]
do
   date
   sleep 10
   let i++
done
```

#### 四、case语句

```shell
#!/bin/bash
option=$1
case ${option} in
   -f) echo "param is -f"
      ;;
   -d) echo "param is -d"
      ;;
   *) 
      echo "$0:usage: [-f ] | [ -d ]"
      exit 1  #退出码
      ;;
esac
#case语句，每一个匹配项结束，用";;"
```

#### 五、循环之break和continue

```shell
for i in `seq 1 5`    
do  
  if [ $i == 3 ]
  then
      break
  fi
 done
 #  seq [选项]... 首数 尾数
 #  seq [选项]... 首数 增量 尾数
 #  seq [选项]... 尾数
 #  ";"可以表示一句，或者直接换行
```

#### 六、常用命令

```shell
&&：用来执行条件成立后执行的命令
||：用来执行条件不成立后的执行命令
```

#### 七、函数调用可shell调用

```
$0,$1,$2,$3   #分别是文件名，函数位置参数1，2，3
```

| 参数 | 说明                                                         |
| ---- | ------------------------------------------------------------ |
| $#   | 传递参数个数                                                 |
| $*   | 以单字符串，传参                                             |
| $$   | 脚本进程id号                                                 |
| $!   | 后台运行的最后一个进程id                                     |
| $@   | **                                                           |
| $-   | 显示Shell使用的当前选项，与[set命令](https://www.runoob.com/linux/linux-comm-set.html)功能相同。 |
| $?   | 退出状态。0表示没有错误，非0有错误。                         |

$* 与 $@ 区别：

​       假设在脚本运行时写了三个参数 1、2、3，，则 " * " 等价于 "1 2 3"（传递了一个参数），而 "@" 等价于 "1" "2" "3"（传递了三个参数）。

#### 八、函数返回值

Shell 函数返回值只能是整形数值，一般是用来表示函数执行成功与否的，0表示成功，其他值表示失败。

#### 九、文件存在的几种判断

| 命令 | 使用            | 备注                |
| ---- | --------------- | ------------------- |
| -e   | [ -e filename ] | 文件/目录；存在为真 |
| -d   | [ -d filename ] | 为目录，为真        |
| -f   | [ -f filename ] | 为常规文件，为真    |
| -L   | [ -L filename ] | 为符号链接，为真    |
| -r   | [ -r filename ] | 可读，为真          |
| -w   | [ -w filename ] | 可写，为真          |
| -x   | [ -x filename ] | 可执行，为真        |
| -s   | [ -s filename ] | 文件不为空，为真    |
| -h   | [ -h filename ] | 软连接，为真        |

判断文件创建新旧

```
filename1 -nt filename2 #如果 filename1新，则为真。
filename1 -ot filename2 #如果 filename2新，则为真。
```

判断符号

| 符号 | 含义     |
| ---- | -------- |
| -eq  | 等于     |
| -ne  | 不等于   |
| -gt  | 大于     |
| -ge  | 大于等于 |
| -lt  | 小于     |
| -le  | 小于等于 |

