import os
"""
常见os模块，基本使用方法
"""
def modle():
    os.getcwd()                          #返回当前文件绝对路径
    os.path.join(path1[, path2[, ...]])  #路径拼接
    os.path.exists(path)                 #文件存在返回，ture
    os.listdir(path)                     #返回path路径下的所有文件的列表
    os.path.abspath(path)                #返回输入的绝对路径
    os.path.dirname(path)                #返回父级目录绝对路径
    os.environ['HOME']                   #设置环境变量
    os.makedirs(path[, mode])            #递归创建文件夹
    os.environ.get('WORKON_HOME')        #获取环境变量



import sys
def modle():
    sys.path.append('/home/ershisui/')  #加入到环境变量
    sys.path                            #输出python环境

