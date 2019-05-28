## Input and Output

in C++ C Java it takes your code and checks or compile it in different ways

in python it get started right away and check almost nothing

```python
# 1. Sample code of output
print('I like you! Valley!\n');
print('The quick brown fox', 'jumps over', 'the lazy dog', '\n');
print(300);
print('\t');
print('100 + 200 = ', '100+200');
print("chr(65): ", chr(65))	
print("ord('A'): ", ord('A'))
dic = {'runoob': 'runoob.com', 'google': 'google.com'}
print(str(dic))
import decimal
print(round(3.1415, 2))
print(round(9.995, 2))
print(decimal.Decimal(9.995))

# 2. Sample code of input 
name = input('Please enter your name:');
if 'YuHui' in name or 'YH' in name:
	print('你个死gay！')
else:
	print('Hello', name);
# Input term is string, needed to be transformed
weight = float(input('please input your weight by the unit of kg: '))
height = float(input('Please input your height by the unit of m: '))
BIM = weight/(heght*height)

if   BIM >= 32:
	print('严重肥胖')
elif BIM >= 28:
	print('肥胖')
elif BIM >= 25:
	print('过重')
elif BIM >=18.5:
	print('正常')
else:
	print('过轻')

'''
多行注释
'''
```



**if else**

```python
# if else
# 如果条件是True就把缩进！！的语句执行
# 别忘记 if, else, elif 条件后的冒号!!!

try :
	age = float(input('Please enter your age: '))
	if age - int(age) == 0:
		if age >= 18:
			print('your age is', age)
			print('adult')
		else:
			print('your age is', age)
			print('teenager')
	else:
		print('Are you kidding me????')
except ValueError as e:
	print('Error: ', e)
finally:
	input('waiting...')
```

## List

list 是python的一种基本类型，它和数组很类似，但是和C语言的数组还是有很大区别的, list的成员可以是不同类型的，list可以作为另一个list的元素，list的内存可以不连续等等

    L = [[1,2,3], 4, 5, 6]
    print(id(L[0]))
    print(id(L[1]))
    #list内的内存竟然可能不是连续的！！！

## list 的三种查找操作
in操作符: 判断值是否在list中

```
 L = ['a', 'b', 'c', 'd', 1, 2, 3, 4]
 print('a' in L)
 print(1 in L)
```
count方法: 判断指定值在list中出现的次数  

L.count('a')  : 统计'a'在L中出现的次数

注意list没有 L.count('a', begin, end)的方法，这个只有string有 

    L = ['a', 'b', 'b', 'd', 1, 2, 3, 4]
    print(L.count('b'))

index方法: 查看指定值在list中的位置:

L.index('a')  : 返回'a'在L中第一次出现的位置

L.index('a', begin, end)  : 返回a在指定切片中第一次出现的位置 [begin, end)
    

list的脚本操作符

1. len([1,2,3,4])                   4

2. [1,2,3] + ['a','b','c']          [1,2,3,'a','b','c']

3. ['a']\*3                          ['a','a','a']

4. 3 in [1,2,3,4]                   True

5. for i in [1,2,3,4]:                迭代器不断给出next，直到抛出错误

list 函数 & 方法

1. L.append(obj)                      在列表末尾添加新的对象

2. L.count(obj)                        统计某个元素在列表中出现的次数

3. L.extend(seq)                       用新列表扩展原列表    **和直接+相比可以保持地址不变**

4. L.index(obj)                        切片可选,找出某个值的第一个匹配项索引位置

5. L.insert(index, obj)                 插入对象

6. a = L.pop()                          删除并返回L的最后一个元素

7. L.remove(obj)                        删除某个值的第一个匹配项

8. L.reverse()                          反向列表中的元素

​    9.L.sort(func)                                               


**list Initiate and visit**

```python
# list 的初始化与访问
classmates = ['Michael','KangKang','Jane','Maria'];
print(classmates);
print('The number of Classmates is:', len(classmates));
for i in range(0, len(classmates)):
	print(classmates[i])
print(classmates[-1]); 	#访问最后一个元素 -2 -3...

input('waiting...')

# list方法来增添成员
classmates.append('LiLei');
print(classmates);

input('waiting...')

classmates.pop();
print(classmates);
input('waiting...')

classmates.insert(1,'Jack');  # i 是索引位置
print(classmates);
input('waiting...')

classmates.pop(1);  # i 是索引位置
print(classmates);
input('waiting...')

classmates[1] = 'Subtitution';
print(classmates);
input('waiting...')

# list作为成员的list(比多维数组更灵活)
L = ['Apple',123,True,['python','c++']];
print(L[3][1]);

input('waiting...')

```

**Generate list**

```python
# List 生成的几种方法

# 1. 用循环append的方法产生List
L = []
for x in range(1,11):
	L.append(x * x)
print(L)

input('waiting')

# 2. [生成元素 for x in list]
L = [x * x for x in range(1,11)] #要生成的元素x*x写在前面，后面是for循环
print(L)

# 后边加上if判断进行筛选也可以
L = [x * x for x in range(1,11) if x % 2 == 0]
print(L)

# 多层循环
L = [m + n for m in 'ABC' for n in 'XYZ']
print(L)

# 多变量循环 dict -> list
d = {'one':1, 'two':2, 'three':3}
L = [k + '=' + str(v) for k,v in d.items()]
print(L)

# Sample codes
# -*- coding: utf-8 -*-
L1 = ['Hello', 'World', 18, 'Apple', None]
L2 = [s.lower() for s in L1 if isinstance(s, str)]
if L2 == ['hello', 'world', 'apple']:
  print('测试通过!')
else:
  print('测试失败!')	

```

## Dict

```python
# dict: Hash 	key->value
# 通过hash访问元素
d = {'Michael':95,'Bod':90,'Tracy':97}
print(d)
print('The score of Michael is : ',d['Michael'])
d['KangKang'] = 100
print('The score of KangKang is : ',d['KangKang'])

print('KangKang in dict? ','KangKang' in d)
print('LiLei in dict? ','LiLei' in d)

print(d.get('Bod'))
d.pop('KangKang') # del d['KangKang']
print('KangKang in dict? ','KangKang' in d)

# key一定要为不可变对象如str，而可变对象list之类的因为不能判断是否相等不能作为key
# 对不可变对象的操作只是返回一个新的值，而没有对本身进行修改, 这里涉及到地址的问题
a = 'abc'
b = a.replace('a','A')
print(a)
print(b)

```

Dict 的迭代

```python
# dict key 迭代
d = {'one': 1, 'two': 2, 'three': 3}
for key in d:
	print(key)
  

# dict value 迭代
for value in d.values():
	print(value)
  

# dict key 和 value 一起迭代 实际上这是一个多变量迭代的特殊例子
for k,v in d.items():
	print(k,v)
```



## Set

数学上的集合的实现

```python
# set only key but no value
# set 没有重复的元素, 而且无序，所以不能index， 有一个应用是比如决策树构造的时候需要去除重复的特征值
s = set([1,2,3])
print(s)

s.add(4)
print(s)

s.remove(4)
print(s)

s1 = set([1,2,3])
s2 = set([2,3,4])
print(s1 & s2)
print(s1 | s2)
```

## tuple

```python
# tuple: 初始化后无法修改没有append,insert等操作 不可变对象
print('The following is the example of tuple');
classmates = ('Michael','KangKang','Jane','Maria');
print(classmates);
t = (1,) # 只有一个元素的tuple需要加一个逗号
print(t)
```

## Flop

```python
# 一个基本类型的迭代
for n in range(1, 11):          # range左闭右开
  print(n)
input('waiting')

# list 迭代
names = ['Michael', 'Bob', 'Tracy']                 # list 也可以
for name in names:
	print(name)
input('waiting')

# tuple 迭代
names = ('Michael', 'Bob', 'Tracy')                 # tuple 也可以
for name in names:
  print(name)
input('waiting')

# while 循环
names = {}
sum = 0
n = 0
while n <= 4:
	sum = sum + n
	n = n + 1
print(sum)
input('waiting')

# string迭代
for ch in 'ABCDEFG':
	print(ch)

# 多变量迭代
for x,y in [(1, 2), (3, 4), (5, 6)]:
	print(x, y)

```

## String

```python
# This file shows some methods of str
t = 'He is a string. Who are you?'

print(t.capitalize()) # Cap first letter

print(t.split()) #split by word

a, b = t.split('.') # 根据'.'两侧进行str的划分

print(t.find('i'))
print(t.find('Python'))
print(t[0:4])
print(t.replace(' ', '|'))

w = 'http://www.google.com'
print(w.strip('http://'))	# strip 只能删除开头或者结尾的子串

print(t.upper())  # string 变大写
print(t.lower())  # string 变小写
print(t + 'HaHaHa') # string 的附加可以直接用+完成

print(t.count('e', 0, len(t)))  # 从0->len-1 中有多少个'e', 这里也是左闭右开

print(t.isalpha()) # string至少有一个字符并且所有字符都是字母则True
print(t.isalnum()) # string至少有一个字符并且所有字符都是字母或者数字则True
```



## 可变对象与不可变对象

```python
# 可变对象(对象内容可变)： list, dict.
# 不可变对象有(对象内容不可变): int, string, float, tuple

# 不可变对象
# 可以发现,在改变a的值后,id的地址也随之改变,实际上我们改变a的值并不是原地改变,而是创建一个新的对象再返回给a。
a = 2
print(id(a))
a = 3
print(id(3))

# 可变对象
a = [1, 2, 3]
print(id(a))
a[0] = 10
print(id(a))

# is 与 == 的差别
# is: id
# ==: 内容
a = 2
b = 2.0
print(a == b) # True
print(a is b) # False
```

## Slice

```python
# 切片索引是左闭右开的 [ )
# 开始索引或者结束索引如果是0可以省略
L = list(range(100))
print('0->99: ')
print(L)
print(L[0:10])
print(L[-10:]) # 省略了 0
print(L[10:20])

# print(begin:end:step)   
print(L[:10:2])
print(L[::5])

# string slice
string = 'ABCDEFG'
print(string)
print(string[2:4])
print(string[2])


# -*- coding: utf-8 -*-
def trim(s):
	i = 0
	j = len(s) - 1
	while i < len(s) and s[i] == ' ':
		if s[i] == ' ':
			i =	 i + 1
	while j > 0 and s[j] == ' ':
		if s[j] == ' ':
			j = j - 1
	s = s[i:j+1] #	切片左闭右开
	print(s)
	return s

if trim('hello  ') != 'hello':
    print('测试失败!')
elif trim('  hello') != 'hello':
    print('测试失败!')
elif trim('  hello  ') != 'hello':
    print('测试失败!')
elif trim('  hello  world  ') != 'hello  world':
    print('测试失败!')
elif trim('') != '':
    print('测试失败!')
elif trim('    ') != '':
    print('测试失败!')
else:
    print('测试成功!')	
```

## Generator

如果需要一个比较大的迭代对象, 但是其中的元素我们是逐个逐个利用，为了节省资源，我们可以采用所谓的 generator

```python
# generator: generate the factors during the floop
# 产生一个generator的语法
g = (x * x for x in range(10))

for n in g:
	print(n)

# almost generator
def fib(max):
	n, a, b = 0, 0, 1
	while n < max:
		print(b)
		a, b = b, a + b
		n = n + 1
	return 'done'

# generator: 顺序执行，碰到yield返回，再次调用next的时候从上次yield返回处继续执行
def fib_(max):
	n, a, b = 0, 0, 1
	while n < max:
		yield b
		a, b = b, a + b
		n = n + 1
	return 'done'

# Yang
def Yang(max):
	temp = [1,]
	n = 1
	while n <= max:
		yield temp
		temp.insert(0, 0)	# insert(index, object)
		temp = [temp[x] + temp[x+1] for x in range(n)]
		temp.append(1)
		n = n + 1
	return 'done'
#	生成第n行的时候为n-1，insert0后共有 0，1，2 ... n
#	range(n-1): 0 ... n-2  (n-2)+(n-1)完成后再append个1，共n个元素

```

## Build-in function

```python
# 一些内置函数可以直接调用
print('|20| = ', abs(20))
print('|-20| = ', abs(-20))

print('max(1,2,3,4) = ', max(1,2,3,4))

# 类型转换
print(int('123'))
print(float('123'))
print(str(123))
print(bool(1))
print(bool(''))
print(int('123', 16)) # 以16进制解释整个字符串得到一个十进制数
print(bin(123)) # 转化为二进制数
print(hex(123)) # 转化为16进制数
printf = print
printf('printf(printf)')
```

## Parameters

```python
# 必选参数: 		 最普通的参数 x
# 默认参数: 		 n=2 
# 可变参数: 	 	 *numbers  !!tuple
# 命名关键字参数:  *, city, age
# 关键字参数:     **kw      !!dict   关键字参数一定要带参数名传入 
# 参数组合顺序必须是：  必选参数，默认参数，可变参数，命名关键字参数，关键字参数


# n = 2 为默认参数，当不输入n的时候相当于认为n=2
# 需要注意的是，对于可变对象List/dict的默认参数，由于原地修改值，会被记忆，所以应当用不可变对象作为默认参数
def power(x, n=2):
	s = 1
	while n > 0:
		n = n - 1
		s = s * x
	return s
	
print(power(4,2))
print(power(4))
input('waiting...')

# 一个用可变对象当默认参数的例子
def test(L=[]):
	L.append('END')
	print(L)
test() # ['END']
test() # ['END', 'END']

input('waiting...')

# 多个默认参数,可以通过指定名称的形式来给值(而不必像C++那样受到参数给出顺序的限制)
def enroll(name, gender, age=6, city='Beijing'):
	print('name: ', name)
	print('gender: ', gender)
	print('age: ', age)
	print('city: ', city)
	print('\n')

enroll('KangKang','M')
enroll('Michael','M',7,'London')
enroll('LiLei','M',city='SiChuan')
input('waiting...')

# 可变参数,自动组装成一个tuple传入，如果不用可变参数要先定义一个list或者tuple
# 在list或者tuple前面加个*就能当成可变参数传入
def add(*numbers):
	sum = 0
	for n in numbers:
		sum = sum + n
	return sum	

print('add(1,2,3,4,5) = ', add(1,2,3,4,5))
a = [1,2,3,4,5]
print('add(1,2,3,4,5) = ', add(*a)) 
input('waiting...')

# 关键字参数: 可以输入任意个数的关键字参数，自动组装成一个dict,可以先组装一个dict，然后加**传入
def person(name, age, **kw):
	print('name:', name, ' age:', age, ' other:', kw)

person('Michael', 30)
person('KangKang', 30, gender='M', city='Beijing')
extra = {'city':'Beijing','job':'Engineer'}
person('Jack', 24, city=extra['city'], job=extra['job'])  # kw获得的是extra的拷贝，无法对原extra进行修改
person('Jcak', 24, **extra)
input('waiting...')

# 命名关键字参数：关键字参数可以有任意个，但是命名关键字参数*只*接收city job作为关键字参数(避免乱传数据进来)
# 命名关键字参数一定要带有参数名
# 命名关键字可以有缺省值
def person3(name, age, *, city, job):  # *，后的字符被认为命名关键字参数
	print(name, age, city, job)

person3('Jane', 23, city='Beijing', job='Engineer')	
input('waiting...')

# 如果函数定义中已经有了一个可变参数，后面的命名关键字参数就不需要特殊分隔符*，了
def person4(name, age, *args, city, job): # city and job are 命名关键字参数
	print(name, age, args, city, job)
input('waiting...')

def person5(name, age, *, city='Beijing', job): #命名关键字可以有缺省值
	print(name, age, city, job)
person5('Jack', 24, job='Engineer')  # 可以不传入city	
input('waiting...')


# 整体的一个例子 **这个例子最清楚**
def func1(a, b, c=0, *args, **kw): # a,b 是普通参数，c是默认参数, *arg代表的是可变参数, **kw是关键字参数
	print('a=', a, 'b=', b, 'c=', c, 'args', args, 'kw=', kw)

func1(1, 2)
func1(1, 2, 3)  # 3是默认参数
func1(1, 2, 3, 'a', 'b')
func1(1, 2, 3, 'a', 'b', job='Engineer', x=77)
tup = ('a', 'b')
kw = {'job':'Engineer', 'x':77}
func1(1, 2, 3, *tup, **kw)
```

## map, reduce, filter and lambda

返回的对象是iteration，可能需要list转换一下



```python
# map() 对每一个元素进行运算
def f(x):
	return x * x
r = map(f, [1, 2, 3, 4, 5, 6, 7, 8, 9]) # r is iterator!!!
print(list(r))
print(list(map(str, list(range(1,10)))))
input('waiting...')

# -*- coding: utf-8 -*-
#将用户输入的不规范的名字改成首字母大写其他小写的形式
def normalize(name):
	return name[0].upper() + name[1:].lower()
L1 = ['adam', 'LISA', 'barT']
L2 = list(map(normalize, L1))
print(L2)

# reduce() 作用在一个有两个参数的函数，把结果和序列下一个继续运算
# f(f(f(x1,x2),x3),x4)
from functools import reduce
def add(x, y):
	return x + y
reduce(add, [1, 3, 5, 7, 8])

# str to int
DIGITS = {'0':0, '1':1, '2':2, '3':3, '4':4, '5':5, '6':6, '7':7, '8':8, '9':9}
def add_(x, y):
	return x * 10 + y
def char_to_num(s):
	return DIGITS[s]
def str_to_int(s):
	return reduce(add_, map(char_to_num, s))
print(str_to_int('74242'))

input('waiting...')

#prod(list) 求积
def prod(L):
	def mult(x, y):
		return x * y
	print("The result is: ", reduce(mult, L))

# str2float(s)
def fun(x, y):
	return x * 10 + y
def str2float(s): # 分别转换int and decimal,然后对decimal进行移位
	s1, s2 = s.split('.')	
	_int = reduce(fun, map(int, s1[:]))
	temp = len(s2)
	_decimal = reduce(fun, map(int, s2[:]))
	_decimal /= pow(10, temp)
	return _int + _decimal

# filter(function, list[]) 筛选序列:只有被function作用后返回True的才会被保留

def is_odd(n):
	return n % 2 == 1
L = list(filter(is_odd, [1,2,4,5,6,9,10,15]))
print(L)
input('waiting...')

# 1. filter 删除空字符
def not_empty(s):
	return s and s.strip()	# s:去除None or ''   s.strip()：去除s内的white space

L = list(filter(not_empty, ['A', '', 'B', None, 'C', ' ']))
print(L)
input('waiting...')

# 2. filter 求素数
def _odd_iter(): # 奇数生成器generator
	n = 1
	while True:
		n = n + 2
		yield n

def _not_divisible(n):
	return lambda x: x % n > 0	# 如果==0说明它以n为因子，就肯定不是素数了 返回一个函数，再对it序列作用

def primes():
	yield 2
	it = _odd_iter()	# it是一个generator 可迭代对象
	while True:
		n = next(it)
		yield n
		it = filter(_not_divisible(n), it) # 构造新序列

for n in primes() :
	if n < 1000:
		print(n)
	else:
		break
    
input('waiting')

# filter 回文判断
def judge(s):
	s = str(s)
	i = 0;
	j = len(s) - 1
	while i < j:
		if(s[i] != s[j]):
			return False
		i = i + 1
		j = j - 1
	return True
output = list(filter(judge, range(1, 1000)))
print(output)

# 匿名函数 lambda 只能有一个表达式，没有return，表达式就是它的return!
# lambda x, y: x * y    (lambda variable: 表达式) ！！！ lambda是一个函数!!!

L = list(map(lambda x: x * x, list(range(1,10))))
print(L)

# lambda x: x * x   ~
# def f(x):
#	  return x * x

L = list(filter(lambda x: x % 2 == 1, range(1, 20)))

```

## Class

init 的第一个参数一定是self表示实例自身，传入对应参数的时候self不需要显示传入

和普通的函数相比，类的方法在定义的时候第一个参数永远是实例变量self,并且在调用的时候隐式地传递这个参数，除此之外，类的方法和普通函数类似

```python
# 封装
# 从外部看Student只需要知道创建Instance的时候要提供name score
# 打印的方法也是在Student类内部定义的
# 对Student进行操作不需要知道内部的细节，而只需要了解**接口特性**
# 方法是与实例instance绑定的函数, 可以让实例绑定其他数据，因此两个同一个类的实例可能拥有不同的变量	
# 并且可以修改实例的某个变量的值
# 如果想要让内部属性不被外部访问
# __xx: Private变量
# __xx__: 特殊变量
# _xx: 可以访问，但是按照约定俗成的规矩，应当视作是私有变量，不要随意访问
class Student(object):

	def __init__(self, name, score):
		self.__name = name
		self.__score = score

	def print_score(self):
		print('%s: %S' % (self.__name, self.__score))

	def get_name(self):
		return self.__name
	def get_score(self):
		return self.__score
	
	def set_name(self, name):
		self.__name = name
	def set_score(self, score):
		if 0 <= score <= 100:
			self.__score = score
		else:
			raise ValueError('bad score')
# Inherit
# 从父类，基类，超类（Base or super class) Animal 继承, 子类获得了父类的全部方法
class Animal(object):
	def run(self):
		print('Animal is running...')

class Dog(Animal):
	pass
class Cat(Animal):
	pass

dog = Dog()
dog.run()
cat = Cat()
cat.run()

# 多态
# 子类的 run() 覆盖了父类的run()
# 一个类其实就相当于一种数据类型，需要注意的是，子类仍然是父类，反之不成立
class Animal(object):
	def run(self):
		print('Animal is running...')

class Dog(Animal):
	def run(self):
		print('Dog is running')

dog = Dog()
dog.run() # Dog is running

a = list()
b = Animal()
c = Dog()

print(isinstance(a, list))	#True
print(isinstance(b, Animal))	#True
print(isinstance(c, Dog))	#True
print(isinstance(c, Animal))	#True
print(isinstance(b, Dog))	#False


# 鸭子类型:看起来像鸭子，走起路像鸭子，就可以视作鸭子
class Timer(object):
	def run(self):
		print('Duck is running...')

def func(Animal):
	Animal.run()	# 调用的时候不需要self参数，只有在类的内部定义需要self参数

a = Animal()
b = Dog()
c = Timer()
func(b)
func(a)
func(c)

# 尽管c Timer 不是Animal的子类，但是他也有run方法，也能作为func的参数，而java等静态语言不可以

```

## Processing class

```python
# 获取对象信息
# 判断对象的类型 
# 1. type() 
import types

print(type(123))
print(type('str'))
print(type(None))

def fn():
	pass
if type(123) == int:
	print('123 is int')
if type('str') == str:
	print('str is srt')
if type(fn) == types.FunctionType:
	print('fn is a function')

class Animal(object):
	pass
class Dog(Animal):
	pass
class Husky(Dog):
	pass

a = Animal()
b = Dog()
c = Husky()

if isinstance(c, Dog):
	print('Yes,c is Dog')	#T
if isinstance(c, Animal):
	print('Yes,c is Animal')	#T
if isinstance(b, Animal):
	print('Yes,b is Animal')	#T
if isinstance(a, Dog):
	print('Yes,a is Dog')	#F
# isinstance()可以判断指定类型，以及他的子类

# dir()获得一个对象的所有属性和方法
# 判断属性存在与设置属性
class MyObject(object):
	def __init__(self):
		self.x = 9
		def power(self):
			return self.x * self.x
obj = MyObject()

hasattr(obj, 'x')	# 有属性'x'吗
hasattr(obj, 'y')	# 有属性'y'吗
setattr(obj, 'y', 19) # 设置一个属性'y'
getattr(obj, 'y')	# 获取属性'y'

# Class and instance are different 
# 定义的类
# 实例instance的属性会覆盖类的属性，只有当实例的属性被删除后才会访问类的属性
class Student(object):
	name = 'Student'	# 不是init的, 是class拥有的一个属性
s = Student()
print(s.name) # Student
s.name = 'Michael' 
print(s.name) # Michael

# 一个用count 计数多少instance被初始化的例子

class Cou_Student(object):
	count = [0] # work
    # count = 0 + self.count = self.count + 1 doesn't work 
	def __init__(self, name, age):
		self.count[0] = self.count[0] + 1 # also work
		self.__name = name
		self.__age = age	
	def print_age(self):
		print('%s: %s' % (self.__name, self.__age))
	def set_age(self, age):
		self.__age = age
	def set_name(self, name):
		self.__name = name
	def get_number(self):
		#print(Cou_Student.count[0])
		print(self.count[0])
for i in range(1,10):
	x = Cou_Student('x', i)
	x.get_number()


# instance 绑定属性
# 当调用一个instance的属性或者方法的时候,优先查询instance的属性或者方法,因此instance的属性方法会屏蔽类的属性方法
# __slots__
class Student(object):
	pass

# 1. 给instance绑定属性
s = Student()
s.name = 'Michael'	# 给Student的实例s绑定属性name

# 2. 给instance绑定方法
from types import MethodType
def set_age(self, age):
	self.age = age
#s.set_age = set_age
s.set_age = MethodType(set_age, s)
if hasattr(s, 'set_age'):
	print('Yes,s has a set_age')

# 3. 给class 绑定属性的方法
Student.age = 18

# 4. 给class!!类!!在定义之后动态绑定方法
Student.set_age = set_age
s2 = Student()
if hasattr(s2, 'set_age'):
	print('Yes,s2 has a set_age attribute')

# 如果我们不想让实例的属性绑定太过于自由，例如只允许对Student添加 name or age 可以采用__slots__
# __slots__ 不会被子类继承
class Student(object):
	__slots__ = ('name', 'age')
class GraduateStudent(Student):
	pass
bart = Student()
# bart.score = 90	 wrong
bart_ = GraduateStudent()
bart_.score = 90 # OK, __slots__ 不会被子类继承
```

## 多重继承

```python
# 多重继承 Mixln
class Animal(object):
	pass

class Mammal(Animal):
	pass

class Bird(Animal):
	pass

class Parrot(Bird):
	pass

class Ostrich(Bird):
	pass

class Runnable(object):
	def run(self):
		print('Running...')

class Flyable(object):
	def fly(self):
		print('Flying...')

class Dog(Mammal, Runnable):
	pass

class Bat(Mammal, Flyable):
	pass

```

## Numpy

```python
import numpy as np
import  math

# 1. 用arange创建一个array
a = np.arange(12).reshape(3, 4)
print(a[0], a[1], a[2])  # 少于ndim的index给出的时候，默认索引的是整个切片,a[0]~a[0, :]
a[(0, 0)] = 5
print(a)

input('waiting...')

# 2. linespace创建array np.linspace(begin, end, len(array))

b = np.linspace(0, math.pi, 3)  # 0->pi 1X3 array
print(b)
# 3. 用array创建一个array
b = np.array([[1, 2, 3], [4, 5, 6]])
print(b.shape)
print(b[0, 0], b[1, 1])

input('waiting...')

# 4. Create special array
a = np.zeros((2, 2))    # 2X2 matrix of all zeros
print(a)
b = np.ones((1, 2),dtype = 'float64')     # 1X2 matrix of all ones
print(b)
c = np.full((2, 2), 7)  # 2X2 matrix of a constant array
print(c)
d = np.eye(2)   # 2X2 identity matrix
print(d)
e = np.random.random((2, 2))    # 2X2 matrix with random values between 0->1
print(e)
f = np.empty((2, 3))
print(f)
g = np.array([[1,2],[3,4]], dtype = complex)
print(g)

# reshape & resize
# reshape 不修改原对象，返回一个形状改变的对象
# resize 原地改变
a = np.arange(12).reshape(3,4)
print(a.shape)
a.resize(4,3)
print(a.shape)
```

```python
import numpy as np
import  math

# 一维数组 trivial

# 1. 多维数组
a = np.arange(12).reshape(3, 4)
a[(0, 0)] = 5   # 多维数组索引一个子元素由tuple给出index
print(a[0], a[1], a[2])  # 少于ndim的index给出的时候，默认未给出的维度索引是整个切片,a[0]~a[0, :]
print(a)

# 2. slice of matrix
# 切片的时候索引规则仍然是左开右闭
# 混合整型索引和切片索引得到的数组rank会降低
# 对索引矩阵修改会体现在原矩阵上
a = np.array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]])  # 3X4

print(a[:2, 1:3])

row_r1 = a[1, :]  # shape(4,)
row_r2 = a[1:2, :]  # shape(1,4)
print(row_r1, row_r1.shape)  # row_r1 ndim==1 即tuple的长度
print(row_r2, row_r2.shape)  # row_r2 ndim==2

input('waiting')

# 3. 整型索引
print(a[[0, 1, 2], [0, 1, 2]])  # 整型索引~ print(a[0, 0], a[1, 1], a[2, 2)
a[np.arange(3), [0, 1, 2]] += 10    # 整型索引一个作用是对矩阵特定值进行修改
print(a)
input('waiting...')

# 4. 条件索引(Bool 索引)
a = np.array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]])  # 3X4
bool_idx = (a > 3)
print(a)
print(bool_idx)
print(a[a > 3])  # rank1 array
input('waiting...')

# numpy提供很多对数组按元素进行运算的函数
# 数组的运算是按照元素进行的，矩阵乘法通过函数和矩阵对象实现

# 1. 对每个元素进行相同的处理
a = np.array([20, 30, 40, 50])
b = np.arange(4)
print(a-b)
print(b**2) # 所有元素平方
print(10 * np.sin(a))

a = np.random.random((2, 3))
print(a)
print(a.sum())
print(a.min())
print(a.max())

# 2. 矩阵乘法
A = np.array([[1, 1],
              [0, 1]])
B = np.array([[2, 0],
              [3, 4]])
print(A * B) # 对应元素相乘
print(np.dot(A, B)) # 矩阵乘法


# 3. 也可以把一些运算对特定轴进行
a = np.arange(12).reshape(3, 4)
print(a)
print(a.sum(axis=0))  # 沿着行加,即变量是行,所以得到的结果(a01+a11+21)
print(a.sum(axis=1))  # 变量是列
print(a.cumsum(axis=0)) # cumulative sum aloing the row
print(a.cumsum(axis=1))

input('waiting...')
# array的迭代
b = np.array([[0, 1, 2, 3],
              [10, 11, 12, 13],
              [20, 21, 22, 23],
              [30, 31, 32, 33],
              [40, 41, 42, 43]])
for row in b:   # 按行, 即变量是行，第一行，第二行，第三行..
    print(row)
for element in b.flat:  # 按元素
    print(element)
    
# 4. stack 组合不同的数组
a = np.floor(10*np.random.random((2, 2)))
b = np.floor(10*np.random.random((2, 2)))
print(a)
print(b)
print(np.vstack((a, b)))    # vstack沿着第一个轴组合(行为变量)
print(np.hstack((a, b)))    # hstack沿着第二个轴组合
```

## 拷贝

```python
# numpy 的拷贝分为 1.完全不拷贝 2.浅拷贝 3.深拷贝

import numpy as np
# 1.1 简单赋值二者指向同一个对象, 对任意一个的修改都会影响的对方	
a = np.arange(12)
b = a
if a is b:
    print('Yes, 简单赋值, a和b指向同一个对象!')

# 2.1 视图view()  浅拷贝,a与a.view()共享数据
# a 与 c 拥有相同的数据，但是地址不同，对c的shape改变不会影响到a，但是改变c的数据会影响到a
c = a.view()
print(a == c)
if not(a is c):
    print('No, a is not c!')
print(c.base is a)

# 2.2 对视图的shape改变并没有影响到a
c.resize(3,4)
print(c)
print(a)

input('waiting')

# 2.3 对视图数据改变对a也产生了影响
c.resize(1,12)
c[(0,0)] = 33
print(c)
print(a)


# 3.1 深拷贝: 完全复制 b doesn't share anything with a
a = np.arange(12)
b = a.copy()

if not (a is b):
    print('No! a is not b!')
print(b.base is a)

# 3.2 对b改变数据并不会影响到a
b[0] = 33
print(b)
print(a)
```

## random 随机数

```python
import numpy.random as random

# 1. 产生一个随机数矩阵,元素0->1
x = random.rand()   #   产生一个单一的[0,1)之间的float随机数
a = random.random((3,4))
print(a)
print(a*5 + 1)  # 可以这样得到不同范围内的随机数

input('waiting')
# 2. 产生整型随机数:
# random.randint(begin, end, number) 产生number个[begin, end) 的随机整数
print(random.randint(1, 6, 10))

input('waiting')
# 3. 概率分布随机数产生
# 3.1 正态分布 
# np.random.normal(loc=0.0, scale=1.0, size=None)
# np.random.randn(d0, d1, d2,...,dn) 返回一个d0*d1*d2*...*dn维的标准正态分布                  
norm = random.normal(10, 1, (3,3))
print(norm)
norm = random.randn(3,3)
print(norm)

input('waiting')
# 3.2 二项分布
# np.random.binomial(n, p, size=None)
print(sum(np.random.binomial(100,0.5,1000))/1000/100)

input('waiting')
# 5 随机打乱序列,多维数组只针对第一个轴进行打乱
x = list(range(1,10))
random.shuffle(x)
print(x)

# 6 随机抓取序列的一个元素
# numpy.random.choice(a, size=None, replace=True, p=None)
# 如果a是整数,就在range(a)中抓取,如果a是列表就在列表中抓取,size是抓取的次数
print(random.choice(['a', 'b', 'c', 'd', 'e']))
print(random.choice(5, 3, p=[0.1,0.3,0.2,0.3,0.1])) 


```

