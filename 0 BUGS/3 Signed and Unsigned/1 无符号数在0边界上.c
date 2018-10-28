/*
Description: 对C语言来说，Signed and Unsigned 之间的转化遵循的原则是，位层面的0/1信息不变，变化的是对这个二进制串的解释方式，当同时处理signed 和 unsigned，注意到一个负数实际上是
一个很大的正的unsigned，我们要小心一些意想不到的隐式转化。
*/

// 对逻辑表达式如果一方是无符号数，那么在比较之前，会将另一个操作数强制转换为无符号数再进行比较

-2147483647 - 1 == 2147483648u // unsigned 1

// WARNING: This is buggy code
float sum_elements(float a[], unsigned length)
{
	int i;
	float result = 0;
	
	for(i = 0; i <= length-1; i++)
		result += a[i];
	return result;
}

/*
当传递参数length = 0，for循环的判断条件将会变成一个很大的正数，导致数组索引越界
*/


