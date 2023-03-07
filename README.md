## wps作业仓库
本仓库是金山办公-企业级工程实训设计与实践课程学习内容仓库，**目前已经顺利结课**
### week01

`LinkList ` 链表类，封装了构造链表的相关函数打印函数以及销毁链表的函数
`LinkSolution` 解决反转问题的类，提供一个反转某长度链表的函数，以及反转k  group链表的函数

### week02

1.	除operator[]外，可自由发挥提供其它迭代访问的接口。
    这里提供了迭代器访问方式 
2.	考虑修改代码实现只能让用户使用char/WCHAR两种类型，其他类型不允许，
    这里采用断言的方式，如果类型不匹配会导致编译错误

### week03
1. 本次实验采用了组合设计模式
2. 尝试使用了智能指针，但是传入参数的问题没有解决，对于CompoundShape的add() remove()传参不能接收智能指针类型


### week04
+ `kmatrix` 普通矩阵
+ `compress_matrix` 压缩矩阵
+ `kmatrix_iterator`和`compresskmatrix_iterator`提供了对应的迭代器

### week05
+ `Esc` 快捷退出
+ `enter` 选择输入数字

### week06 07
+ ui界面大体分为四个部分，左边的分组，中间的待办以及输入框部分，以及右边的浮动窗口

![](./image/%E5%A4%A7%E4%BD%93%E6%A1%86%E6%9E%B6%E5%9B%BE.png)

主要功能包括：
+ 新建分组
+ 修改分组名
+ 新建待办
+ 修改待办名
+ 设置到期时间 提醒日期等
+ 设置优先级并可根据优先级排序
+ 已完成待办自动放置队尾
+ 待办排序功能，排序规则包括名字，优先级，截止时间等
+ 本地数据库保存

主要函数说明：
+ 分组和待办部分采用的QListWidget，浮动设置窗口采用的QDockWidget
+ 主要文件包括：todolist 这是主界面，主要负责将各个页面串联起来
+ addnewgroupdialog是新建分组的弹框
+ deadlinecalendar是设置终止日期的弹框
+ grouplistwidget是左边分组QListWidget
+ groupitemwidget是左边分组的自定义item
+ itemgroupwidget是中间todolistwidget所需的自定义item（暂未融入程序）
+ linewidget主要为ListWidget分组提供分割线
+ newcalendar是仿照网页自定义的日历
+ newlineedit是中间自定义的待办输入框
+ noticecalendar是自定义的提醒弹框
+ todolistwidget是中间的QwidgetList
+ todoitemwidget是中间的自定义item文件
+ todoitemsets主要是显示具体设置以及进行设置
+ todoutils提供了两个静态函数，用于辅助
+ tododata是数据存放构造的数据数据结构
+ savelocat 通过数据库将数据存在本地

数据主要存在groupitemwidget当中，每次切换分组都刷新中间todolistwidget以及左边的dockwidget。在todolistwidget以及dockwidget上面的修改通过信号槽机制传到对应的groupitemwidget。todolistwidget,grouplistwidget右键设有菜单








