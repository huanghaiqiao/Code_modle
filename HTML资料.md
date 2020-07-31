中文手册：https://www.php.cn/course/27.html

手册2：https://www.jmjc.tech/t-1/131

# head

一、引入css

```html
<link rel="stylesheet" type="text/css" href="theme.css" />
```

二、内部css

```html
<style type="text/css">
            #j2 {
                background-color: #808080;
            }
</style>
```

三、标签内

```html
style="background-color: #3c763d"
```

# body

### 引入方法

一、引入js，在</body>之前添加

```html
<script type="text/javascript" src="js/index.js" ></script>
```

二、内部js

```
<script type="text/javascript">
            function onClickB1() {
                document.getElementById("b1").innerHTML = "HEAD";
            }
</script>
```

### body清除边距

```html
<body style="margin:0 auto"> 0是高度缝隙，auto是div居中
```

### 注释

注释形式<!-- -->

注释快捷键：Ctrl+Shift+/

注意：css、javscript----同样的快捷键

## 一、div标签

### 默认情况

1. 行业标签
2. 默认只占一行，以屏幕为参照物
3. 包涵子元素时候，div设置高和宽，会被默认撑起来
4. 行高height在未设置情况下，自动阔开
5. 宽度超出屏幕，下方会自动生成滑块

## 二、span标签

### 默认情况

#### 父级标签--未设置height、width

1. 块级标签
2. 默认有多大占多大
3. 最大占满本行，以父为参照物

## 三、lable标签

备注：功能实现---点击“用户名”，光标跳转到“input”框

```html
<label for="username">用户名</label>
<input id="username" type="text" placeholder="用户名">	
```

## 四、input标签

### 1、input----placeholder

备注：input，里面默认提示文字

示例：

```html
<input id="username" type="text" placeholder="用户名">
```

### 2、input----value

备注：value属性可以，设置input框里面起始内容

```html
<input type="url" value="Reset">
```

即input框里面可以看到Reset

### 3、input---name

这个用户后台获取，input内容关键

### 4、input---type

#### 4.1、type="text"，

后台取值一般用name

```html
<input id="username" type="text" placeholder="用户名">	
```

#### 4.2、type="password"

输入框内容以***代替，后台取值一般用name

```html
<input type="password" >	
```

#### 4.3、type="submit"

1. 这里一般配合，form表单使用
2. 提交按钮

```html
<input type="submit" >	
```

#### 4.4、type="button"

按钮，value="按钮"表示----按钮上的显示内容

```html
<input type="submit" value="按钮">	
```

#### 4.5、type="radio"

name属性(name相同互斥)

后台取值，一般加上属性value

checked="checked"，页面默认已选

```html
<input type="radio">
```

#### 4.6、type="checkbox"

复选框 value，checked="checked",name属性(批量获取数据)

后台取值，一般加上属性value

```html
<input type="checkbox">
```

#### 4.7、type="file" 

依赖于form表单的一个属性 enctype="multipart/form-data"

```html
<input type="file">
```

#### 4.8、type="rest"

表示清空输入框，按钮形式清空

```html
<input type="reset" value="Reset">
```

#### 4.9、type="email"

邮件格式

```html
<input type="reset" value="Reset">
```

#### 4.10、type="url" 

url格式

```html
<input type="url" value="Reset">
```



## 五、textarea标签

这是可编辑的文本框，下面实例这个框高和宽已经固定

当内容超出，会自动生成下拉框

```html
<textarea rows="2" cols="20">你能找到你需要的网站建设教程
</textarea>
```

## 六、select标签

### select单选

后台通过name和value，获取值，值是唯一的

```html
<select name="选择">
  <option value="volvo">Volvo</option>
  <option value="audi">Audi</option>
</select>
```

select多选

加multiple="multiple"，按住Ctrl+鼠标左键，就能选择

size表示html显示几条option

```html
<select name="选择" multiple="multiple" size="2">
  <option value="volvo">Volvo</option>
  <option value="audi">Audi</option>
</select>
```

## 七、a标签

下面方法表示，回到指定id位置

```html
<a href="#某个标签id"></a>
```

去下划线，加入

```html
style="text-decoration: none;"
```

a标签---回到顶部用法

```html
<a href="#">回到最顶端</a>
```

结合js用法，该方法作为难点-----未解

```html
<a href="javascript:js_method();">内容</a>
```

## 八、fieldset标签-legend标签

这是组合使用的

```html
<form>
  <fieldset>
    <legend>健康信息</legend>
    身高：<input type="text" />
    体重：<input type="text" />
  </fieldset>
</form>
```

![](C:\Users\huang\Desktop\1586933570(1).jpg)

输出为上图

## 九、form标签

该标签通常组合，input

action表示提交到哪里

method提交方法

```html
<form action="form_action.asp" method="get">
  <p>First name: <input type="text" name="fname" /></p>
  <p>Last name: <input type="text" name="lname" /></p>
  <input type="submit" value="Submit" />
</form>
```

穿插实例（这里是，提交到网页，并且附带值传过去。百度直接跳转到：搜索内容）

百度是get方法

```html
<form action="http://www.baidu.com/s" method="get" >
    <input name="wd" placeholder="用户名" type="text">
        <input type="submit" value="Submit" />
  </form>
```



## 十、音频标签

```html
<audio src="/i/horse.ogg" controls="controls">
</audio>
```

## 十一、button标签

示例

```html
<button type="button">Click Me!</button>
```

## 十二、img

示例

alt 属性指定图像不能正常显示（网速慢、图片链接错误）后显示的替换文本。

注意未设置img格式，会图片多大显示多大

```html
<img src="/i/eg_tulip.jpg"  alt="上海鲜花港 - 郁金香" />
```

## 十三、header

写在body里面

html经典布局

https://blog.csdn.net/ixygj197875/article/details/79770711

文本超出

text-overflow

文本不换行

```css
white-space: nowrap;
```

