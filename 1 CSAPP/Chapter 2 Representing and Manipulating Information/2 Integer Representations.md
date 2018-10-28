## 2.2 Integer Representations

In this section, we describe two different ways bits can be used to encode integers.

1. one can only represent nonnegative numbers
2. one can represent negative, zero, and positive numbers.

**Somr functions and symbols** 

| Symbol   | Type      | Meaning                         |
| -------- | --------- | ------------------------------- |
| B2Tw     | Function  | Binary to two's complement      |
| B2Uw     | Function  | Binary to unsigned              |
| U2Bw     | Function  | Unsigned to binary              |
| U2Tw     | Function  | Unsigned to two's complement    |
| T2Bw     | Function  | Two's complement to binary      |
| T2Uw     | Function  | Two's complement to unsigned    |
| TMinw    | Constant  | Minimum two's- complement value |
| TMaxw    | Constant  | Maximum two's-complement value  |
| UMaxw    | Constant  | Maximum unsigned value          |
| +(t, w)  | Operation | Two's-complement addition       |
| +(u, w)  | Operation | Unsigned addition               |
| *(t, w)  | Operation | Two's-complement multiplication |
| *(u, w)  | Operation | Unsigned multiplication         |
| -(t,  w) | Operation | Two's-complement negation       |
| -(u, w)  | Operation | Unsigned negation               |

### 2.2.1 Integer Data Types

C supports a variety of intergral data- ones that represent finite ranges of integers. The figure(P61) as follow shows the ranges of different types of integral data. **You probably notice that the ranges are not symmetric.** 



1. The C standards define minimum ranges of values that each data type must be able to represent.
2. The fixed-size data types guarantee that the ranges of values will be exactly those given by the typical numbers(P61).

### 2.2.2 Unsigned Encodings

PRINCIPLE: Definition of unsigned encoding: for vector 
$$
\vec x = [x_{w-1}， x_{w-2},....,x_0]  \\
B2U_w(\vec x) = \sum_{i=0}^{w-1}x_i2^i \\
B2U_w(\vec x) : \{0, 1\}^w \to \{0, 1, 2, ..., 2^w-1\}
$$
**Uniqueness of unsigned of encoding : Function B2Uw is a bijection!**

The function B2Uw maps each bit vector of length w to a unique number between 0 and 2^w - 1, and it has an reverse which we call U2Bw.

### 2.2.3 Two's-Complement Encodings

PRINCIPLE: Definition of two's-complement encoding: for vector
$$
\vec x = [x_{w-1}, x_{w-2}, ... , x_0] \\
B2T_w = -x_{w-1}2^{w-1} + \sum_{i=0}^{w-2} x_i2^i \\
B2T_w : {0, 1}^w \to \{-2^{w-1},...,2^{w-1}-1\}
$$
**Uniqueness of two's-complement encoding : Function B2T_w is a bijection**

### 2.2.4 Conversions between Signed and Unsigned

**The effect of casting is to keep the bit values identical but change how these bits are interpreted.**
$$
signed \to unsigned : T2U_w(x) = B2U_w(T2B_w(x)) = x + w_{w-1}2^w\\
unsigned \to signed : U2T_w(x) = B2T_w(U2B_w(x)) = -u_{w-1}2^w + u
$$
When mapping a signed number to its unsigned couterpart, negative numbers are converted to large positive numbers, while nonnegative numbers remain unchanged.



When TMin32(-2147483648 - 1) is cast to unsigned, it becomes 2147483648. In addition, if either operand is unsigned, then the other operand will be cast to unsigned before comparing.

Remark: -2147483648 is not alright



| Expression                   | Type     | Evaluation |
| ---------------------------- | -------- | ---------- |
| -2147483647-1 == 2147483648  | Unsigned | 1          |
| -2147483647-1 < 2147483647   | Signed   | 1          |
| -2147483647-1U < 2147483647  | Unsigned | 0          |
| -2147483647-1 < -2147483647  | Signed   | 1          |
| -2147483647-1U < -2147483647 | Unsigned | 1          |



### 2.2.5 Expanding the bit representation of a number 

The operation to convert from a smaller to a larger integer type while retaining the same numeric value should always be possible.

**(1) unsigned**

To convert an unsigned number to a larger data type, we can simply add leading zeros to the representation.

PRINCIPLE: Expansion of an unsigned number by zero extension
$$
\vec u = [u_{w-1}, u_{w-2}, ... , u_0] \to \vec u' = [0, ..., 0, u_{w-1},...,u_{w-2}] \\
B2U_w(\vec u ) = B2U_w(\vec u')
$$
**(2) signed**

PRINCIPLE: Expansion of an two's-complement number by sign extension
$$
\vec x = [x_{w-1}, x_{w-2}, ... ,x_0] \to \vec x' = [x_{w-1}, x_{w-1}， ... , x_{w-1},x_{w-2},...,x_0] \\
B2T_w(\vec x) = B2T_w(\vec x')
$$
This principle is corresponding to the arithmetic shift.

### 2.2.6 Truncating Numbers

Suppose that rather than extending a value with extra bits, we reduce the number of bits representing a number. 

​	

​	int x = 53191;

​	short sx = (short) x;	// Casting x to be short will truncate a 32-bit int to 16-bit short

​	int y = sx;



PRINCIPLE: Truncation of an **unsigned number**


$$
\vec x = [x_{w-1},...,x_0] \qquad \vec x' = [x_{k-1}, ... , x_0] \\
x' = x \quad  mod  \quad 2^k
$$
PRINCIPLE: Truncation of a two's-complement number 
$$
\vec x = [x_{w-1},...,x_0] \qquad \vec x' = [x_{k-1}, ... , x_0] \\
x' = U2T_k(x \quad  mod  \quad 2^k)
$$
简而言之，就说按位截断(mod完成的事情)，然后再进行不同的解释。

### 2.3.1 Unsigned addition

**An arithmetic operation is said to overflow when the full integer result cannot fit within the word size limits of the data type.**

Considering two nonnegative integers x and y, such that 0 <= x,y <= 2^w. Then, we get 0 <= x+y <= 2^(w+1) - 2.  Although some programming languages, such as Lisp, actually support arbitrary size arithmetic, more commonly, programming languages support fixed-size arithmetic.

**PRINCIPLE: Unsigned addition, for x and y such that 0 <= x, y < 2^w**
$$
x +^u_wy = 
\begin{equation} 
\left\{
	\begin{array}{lr}
	x + y 	\qquad 	x + y < 2^w Normal \\ 
	x + y - 2^w 	\qquad 2^w \leq x + y < 2^{w+1} Overflow
	\end{array}
\right.
\end{equation}
$$
**PRINCIPLE: Detecting overflow of unsigned addition**

For x and y in the range 0 <= x,y <= UMaxw, let s = x +(u,w) y. Then the computation of s overflowed if and only if s < x.



int uadd_ok(unsigned x, unsigned y)	// Determine whether arguments can be added withut overflow

{

​	unsigned s = x + y;

​	return sum >= x;

}

Modular addition forms a mathematical structure known as an abelian group. That is, it is commutative and associativel; it has an identity element 0, and every element has an additive inverse.

**PRINCIPLE: Unsigned negation**

For any number x such that 0 <= x < 2^w, its w-bit unsigned negation -(u, w) x is given by the following:
$$
-^u_wx = 
\begin{equation} 
\left\{
	\begin{array}{lr}
	x  	\qquad 	x = 0  \\ 
	2^w - x \qquad x > 0
	\end{array}
\right.
\end{equation}
$$
**Observe that the result can be obtained by performing binary addition of the operands and truncating the result to 4 bits!**  所谓上下溢，就是按照补码的二进制加法，然后再进行截断的结果！

/* Determine whether arguments can be added without overflow */

int tadd_ok(int x, int y)

{

​	int sum = x + y;

int neg_over = x < 0 && y < 0 && sum >=0;

int pos_over = x >=0 && y >= 0 && sum < 0;

return !neg_over && !pos_over;

}

