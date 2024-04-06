# C语言协程
对Linux系统下ucontext.h提供的协程代码封装便于使用

# 使用
Linux平台，GCC编译器
编译：make
运行: ./mainApp

#注意
协程使用的栈设置小了会出现异常,推荐配置16384大小。
