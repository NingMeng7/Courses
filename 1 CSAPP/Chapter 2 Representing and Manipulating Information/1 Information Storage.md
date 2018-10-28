# Representing and Manipulating Information
## 0 Introduction
6Computer representations use a limited number of bits to encode a number, and hence some operations can overflow when the results are too large to be represented.

    //On most of today's computers(those using a 32-bit representation for data type int):
    (500 * 400) * (300 * 200)
    ((500 * 400) * 300) * 200
    ((200 * 500) * 300) * 400
    400 * (200 * (300 * 500))
    // The computer will generate the unexpected result: -884,901,888, but at least it's consistent.
    // The order of int operating doesn't matter
    
    (3.14+1e20) - 1e20 // ~ 0.0
    3.14+(1e20-1e20) // ~3.14
    // The order of floating-point arithmetic matters.

The different mathematical properties of integetr versus floating-point arithmetic stem from the difference in how they 
handle the finiteness of their representations - integer representations can encode a comparatively small range of values, but do so precisely,
while floating-point representations can encode a wide range of values, but only approximately.

## 2.1 Information Storage
Rather than accessing individual bits in memory, most computers regard bytes(blocks of 8 bits) as the smallest and basic addressable unit of memory. A machine-level program views the memory as a very large array of bytes, referred to as virtual memory. Every byte of memory is identified by a unique number, known as its address.

## 2.1.2 Data Size
Every computer has a fundamental parameter referred to **word size**, indicating the nominal size of **pointer data**.  （?)
Since a virtual address is encoded by such a word, the most important system parameter determined by the word size is the maximum size of the virtual address space. For instance, if the word size is w, the virtual addresses can range from 0 -> 2^w - 1, giving the program access to at most 2^w bytes.

Most 64-bit machines can also run programs compiled for use on 32-bit machines, a form of backward compatibility. Computers and compilers support multiple data formats using different ways to encode data(e.g. int, float...) as well as different different lengths. The exact numbers of bytes for some data types depends on how the program is compiled. To avoid the cagaries of relying on "typical" sizes and different compiler settings, ISO C99 introduced a class of data types where the data sizes are fixed regardless of compiler and machine settings.

Programmers should stive to make their programs portable across different machines and compiler, that is, to make the program insensitive to the exact sizes of the different data types. For instance, many programmers historically assumed that an object declared as type int could be used to store a pointer(32-bit), but it leads to problems for 64-bit programs.

## 2.1.3 Addressing and Byte Ordering
In virtually all machines, a multi-byte object is stored as a contiguous sequence of bytes. We must establish two conventions:

    a) What the address of the object will be?
    b) How we will order the bytes in memory?

Supposing that the address of the object given by the smallest address of the bytes used, a variable x of type int(4 bytes) has address 0x100; that is, the value of the adress expression &x = 0x100. Then the 4 bytes of x would be stored in memory locations 0x100, 0x101, 0x102, 0x103.

Here comes the egg issue. 

    a) Little endian: Storing the object in memory ordered from least significant byte to most. (least comes first) 
    b) Big endian:    Storing the object in memory ordered from most significant byte to least. (most comes first)

Suppose the variable x of type int and at address ox100 has a hexadecimal value of 0x01234567. THe ordering of the bytes within the address range 0x100 -> 0x013 depends on the type of machine:

    Little endian:   0x100       0x101      0x102       0x103       //  I like yaya anyway~
                      67          45          23          01
    Big endian:       01          23          45          67

For most application programmers, the byte orderings used by their machines are totoally invisible. But sometimes we may take this into consideration.
>(a) The communicating of binary data over a network between different machines. When the datas produced by a big-endian mechine are sent to a little-endian machine, or vice versa, it may result in some problems.

>(b) When inspecting machine-level programs, i.e, looking at the byte sequences.

>(c) When programs are written that circumvent the normal type system. (*a cast or a union* in C)

        #include <stdio.h>
    
        typedef unsigned char * byte_pointer;
    
        void show_bytes(byte_pointer start, size_t len) 
        {
            size_t i;
            for (i = 0; i < len; i++)
                printf(" %.2x", start[i]);
            printf("\n");
        }
        
        void show_int(int x) 
        {
            show_bytes((byte_pointer) &x, sizeof(int));
        }
    
        void show_float(float x)
        {
            show_bytes((byte_pointer) &x, sizeof(float));
        }
    
        void show_pointer(void *x)
        {
            show_bytes((byte_pointer) &x, sizeof(void *));
        }
        
        void test_show_bytes(int val)
        {
            int ival = val;
            float fval = (float) ival;
            int * pval = &ival;
            show_int(ival);
            show_float(fval);
            show_pointer(pval);
        }
    
        Byte representations of different data values.
    
        Machine 　　　Value　　　　　Type 　　　　　　　　Bytes(hex)
    
        linux32      12,345         int                39 30 00 00
        windows      12,345         int                39 30 00 00
        sun          12,345         int                00 00 30 39
        linux64      12,345         int                39 30 00 00
    
        linux32      12,345.0       float              00 e4 40 46
        windows      12,345.0       float              00 e4 40 46
        sun          12,345.0       float              46 40 e4 00
        linux64      12,345.0       float              00 e4 40 46
    
        linux32      &ival          int *              e4 f9 ff bf
        windows      &ival          int *              b4 cc 22 00
        sun          &ival          int *              ef ff fa 0c
        linux64      &ival          int *              b8 11 e5 ff ff 7f 00 00

Our argument 12,345 has hexadecimal representation 0x00003039. For the int data, we get identical results for all machines, except for the byte ordering. So does the float type. On the other hand, the pointer values are completely different.

**Different patterns between int and float for the same numeric value:**

00003039H

0000 0000 0000 0000 0011 0000 0011 1001 B   //  12345

4640E400H

0100 0110 0100 0000 1110 0100 0000 0000 B

This is not coincidental. We have seen the difference focus on the float and int: precise versus broder range. The implements of this two data type account for it. We will return to this examole when we study floating-point formats.

## 2.1.4 Representing Strings

A string in C is encoded by an array of characters terminated by the null('\0') character. By representing the string "abcdef", we get the result: 61 62 63 64 65 66. The result is based on the fact that letters 'a' through 'z' have ASCII codes 0x61 through 0x7A and strlen ignores 
'\0'.

## 2.1.5 Representing Code
Consider the following C function:

    int sum(int x, int y)
    {
        return x + y;
    }

When we compiled on the sample machines, we generate the machine-level code:

    linux32     55 89 e5 8b 45 0c 03 45 08 c9 c3
    windows     55 89 e5 8b 45 0c 03 45 08 5d c3
    sun         81 c3 e0 08 90 02 00 09
    linux64     55 48 89 e5 89 7d fc 89 75 f8 03 45 fc c9 c3

A fundamental concept of computer system is that a program, from the perspective of the machine, is simply a sequence of bytes. And we can see that the binary codes generate by different machines are incompatible. Binary code is seldom portable across different combinations of machines and operating systems.

## 2.1.6 Introduction to Boolean Algebra

You may get the related knowlege from discrete math part.

One useful application of bit vectors is to represent finite sets. We can encode any subset A $\subseteq$ {0, 1, ..., w -1} with a bit vector [$a_{w-1}$, ..., $a_1$, $a_0$]. For instance, when we apply the Bayes classifier for texts, we make the feature vector x standing for a email. Then, considering A = {0, 3, 5, 6} is encoded as vector a = [01101001] and B = {0, 2, 4, 6} is encoded as vector b = [01010101]. The operation a & b yields bit vector [01000001] while $A \cap B$ = {0, 6}.

## 2.1.7 Bit-Level Operations in C
Boolean operations in C:

    | for or
    & for and
    ~ for not
    ^ for exclusive~or
    
    ~0x41        ~[0100 0001]  =>    [1011 1110]
    ~0x00        ~[0000 0000]  =>    [1111 1111]
    0x69 & 0x55  [0110 1001] & [0101 0101] => [0100 0001]
    0x69 & 0x55  [0110 1001] | [0101 0101] => [0111 1101]

Example1:    Notice that a^a = 0, and 0 ^ a = a
    
    void inplace_swap(int *x, int *y)
    {
        *y = *x ^ *y;
        *x = *x ^ *y;
        *y = *x ^ *y;
    }

Example2:   

    void reverse_array(int a[], int cnt)    
    {
        int first, last;
        for (first = 0, last = cnt - 1; first <= last; first++, last-->)
            inplace_swap(&a[first], &a[last]);
    }
    //  This function works whenever the lengh of array is even and if the lenght is odd, it set the middle element to zero.(Notice that a^a=0)
    //  1234    =>      4321
    //  12345   =>      54021  
    //  There is no need to swap the middle one, so (first < last) will make this function work

One common use of bit-level operations is to implement *masking operations*, where a mask is a bit pattern that indicates a selected set of bits within a word.    

## 2.1.9 Logical Operations in C

    !0X41           =>      0x00    //  False  
    !0x00           =>      0x01    //  True
    !!0x41          =>      0x01
    0x69 && 0x55    =>      0x01
    0x69 || 0x55    =>      0x01

RK1: The behaviours of logical operations match that of a bitwise operation only in the special case in which the arguments are restricted to 0 or 1.

RK2: The logical operators '&&' and '||' **do not evaluate their second argument if the result of the expression can be determined by evaluating the first argument.**

## 2.1.10 Shift Operations in C
For an operand x having bit representation [$x_{w-1}, x_{w-2}, ..., x_0$]. the C expresison x << k yields a value with bit representation $[x_{w-k-1}, x_{w-k-2}, ..., x_0, 0,...,0]$ That is, x is shifted k bits to the left, dropping off the k most significant bits and filling the right end k zeros. x << j << k is equivalent to (x << j) << k.

And there is a corresponding right shift operation, written in C as x >> k, but it has a slightly subtle behaviour.

case1(*Logical*) : x >> k => 
$$
[0,...,0,x_{w-1},x_{w-2},...,x_k]
$$


 

case2(*Arithmetic*) : x >> k => 
$$
[x_{w-1},...,x_{w-1},x_{w-2},...,x_k]
$$


Example:

    Argument x          [01100011]          [10010101]
    x << 4              [00110000]          [01010000]
    x >> 4(logical)     [00000110]          [00001001]
    x >> 4(arithemetic) [00000110]          [11111001]

The C standards do not precisely define which type of right shift should be used with signed. In practice, however, almost all compiler/machine combinations will use arithmetic right shifts for signed data, and many programmers assume this to be the case. For unsigned data, on the other hand, right shifts must be logical.

Referred to the operator precedence issues: When in doubt, put in parentheses!
      
