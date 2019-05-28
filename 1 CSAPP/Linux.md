# Linux & Vim 

### Section 1 Lead-in

```
ls: 现实当且目录所有文件
ls -l: 较长格式
ls -a: 显示隐藏文件
ls -A: 显示除了当前目录和上一级目录外的所有文件


pwd: 显示当前路径
Tab: 补全, 连续两次显示所有候选
 
touch file.txt: 创建一个文件
mkdir code: 创建一个文件夹
touch love_{1..10}_test.txt: 一次性创建多个文件，它们只有数字序号不同
```

2 通配符

```
通配符出现在命令的参数中，主要为 * ？, 用来对字符串进行模糊匹配，可以用它来代替一个或者多个真实的字符，将所有满足条件的匹配项给出
*: 匹配 0/多个字符
?: 匹配一个字符
[list]: 匹配 list 中的任意单一字符
[^list]: 匹配 list 中的任意单一字符以外的字符
[c1-c2]: 匹配c1-c2中任意单一字符，例如 [0-9]

ls *.txt 
```

### Section 2 Users

Linux 可以同时供多个用户登录, 但是彼此文件不会直接共享

```
who am i

su <user> 切换到用户 user
sudo <cmd> 以特权级别运行 cmd 命令
sudo adduser <user> 创建用户
exit / ctrl+d: 退出当前用户, 也是退出终端的命令

groups: 查看用户群组，同一组的用户共享一些资源
sudo 用户组的成员可以通过sudo获得root权限
sudo usermod -G sudo lilei
sudo deluser lilei --remove-home: 删除用户

sudo chown shiyanlou file: 把file的所有者变更为用户 shiyanlou
```

## Section 3 File

```
cd ..: 进入上一级目录
cd ~: 进入用户 home 目录
pwd: 显示当前路径

touch test: 创建空白文件 test
mkdir: 创建空白目录
mkdir -p father/son/grandson: 创建多级目录

cp test /home/shiyanlou/father/son/grandson : 复制 test 到..
cp -r father family : 复制目录到文件夹
cp -r dir1/. dir2 : 把 dir1 的所有文件复制到 dir2

rm test: 删除 testls
rm -r family: 删除目录

mv file Document: 将文件file 剪切移动到 Document 目录
mv file myfile: 将文件 file 重命名为 myfile
rename: 批量重命名
```

### Section 4 Display file

```
cat file: 正序显示
tac file: 倒序显示
-n: 添加行号

more file
less file
分页查看文件: space 滚动一屏, enter 滚动一行, q 退出

head 
tail
显示文件头/尾 10 行
tail -n 2 file: 看2行

file dir: 查看文件类型
```



### Section 1 Modes of vim

1 Normal mode

2 Insert mode

3 Command line mode

4 Visual mode

5 Ex mode

6 Select mode



模式选择： vim 启动自动进入normal mode, 处于 insert / command line mode 的时候按 Esc 进入 normal mode, 在 normal mode 中按 i/a 进入 insert mode，按 : 进入命令行模式



### Section 2 Basic operation

多个键组合不需要赶着按, 一个个按是ok的

```
vim test.txt	打开文件, 如果不存在，则创建文件
vim		打开vim
:e 文件路径 	打开文件
:w filename 	另存为

normal mode:
h l j k: 左右下上
w b: 下一个，上一个单词

normal mode-> insert mode
RK：必须回到普通模式才能切成不同的插入模式

i: 在当前光标处进行编辑
I: 行首
A: 行末
o: 当前行后插入一个新行
O: 当前行前插入一个新行

command line mode
:q!		强制退出，不保存
:q		退出
:wq!	强制保存并 退出
:w <文件路径> 另存为
:wq		保存并退出

normal mode
delete
x 删除游标所在字符
dd 剪切整行
3dd 删除三行
dw 删除一个单词(英文)
D 删除到行尾
d^ 删除到行首
dG 删除到文档结尾
d1G 删除到文档首
```

### Section 3 Edit

```
10x
3dd
n+command: 连续执行n次命令

:set nu 显示行号
nG 	光标跳到第n行
gg	光标跳到第一行
G 	到最后一行
ctrl+o 回到跳转前位置

行内操作：
w 	到下一个单词的开头
f<字母>	向后搜索字母，并跳到第一个匹配的位置
F<字母>	向前

yy	复制一行
3yy	复制三行
y^	复制到行首
y$	复制到行尾
yw	复制一个单词
y2w	复制2个单词
yG	复制到文档末
y1G	复制到文档开头

p:	粘贴到光标后
P:	粘贴到光标前

ddp:	与下面那一行交换
```

### Section 4 Search & Replacement & Indent

```
normal mode
?str	  向上查找
/str	  向下查找
n, N	  查找下一个/上一个内容

\*		向后查找游标所在单词
\#		向前查找游标所在单词

r<字母>	将游标所在字母替换成指定字母
R<字母>	连续替换直到Esc
~		 反转游标所在大小写
u(n)	 撤销(n)次操作
U		 撤销当前行所有修改
ctrl+r	  re-do, 撤销un-do

>>		整行向右缩进
<<		整行向左回退
:set shiftwidth=10	设置缩进量

:ce		使本行居中
:ri		使本行居右
:le		左
```

### Section 5 Advanced approach

```
vim 1.txt 2.txt
:n
:N
同时编辑多个文件，并切换

在vim中打开新的文件
:e 3.txt
:e#	回到前一个文件
:ls 列出以前编辑过的文件
:b 2.txt	直接进入2.txt文件的编辑
:f new.txt	改名正在编辑的文件为new.txt

normal mode
v 	进入 visual mode
可以区域选取, 再次按v取消
d	删除选取区域内容
y 	复制选取区域内容

normal mode
ctrl+w s	分成两个水平的窗口
```

yG