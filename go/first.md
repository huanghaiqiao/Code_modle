一、[go语言在线编辑器](https://www.nhooo.com/tool/golang/)

二、第一个代码

```go
package main
import "fmt"
func main() {
   fmt.Println("Hello, World!")
}

// 直接执行 go run hello.go 
// 编译执行 go build hello.go ; ./hello 
```

1、注释使用"//", "/****/"

2、"{}"不能在单独的行上

3、一行代表一个语句结束；多个语句写在同一行使用";"

三、创建包

```shell
# 创建包
go mod init pack_name
# 下载包
go get github.com/davyxu/cellnet
```

四、变量

```
// 第一种
var i int
var f float64
var b bool
var s string
// 第二种，自推断
var d = true
// 第三种，这是声明语句
intVal := 1 

```

五、常量

```
const a, b, c = 1, false, "str"
```

六、切片

```
var numbers = make([]int,3,5)
```

七、遇到编程问题

```
go func()
// 需要定义成函数才行;go fmt.Println("");没用输出
```

