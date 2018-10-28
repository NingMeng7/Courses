# Introduction： We start by some simple examples:
 
# Great Reality 1：   Ints are not Integers, Floats are not Reals!
  	
	printf("400 * 500 * 600 * 300 = %d\n", 400 * 500 * 600 * 300);  //  1640261632
	printf("50000 * 50000 = %d\n", 50000 * 50000);  //  -1794967296

# Great Reality 2：    (x+y)+z != x+(y+z)
  	printf("1e20 - 1e20 + 3.14 = %f\n", 1e20 - 1e20 + 3.14);  // 3.140000
	printf("1e20 +(- 1e20 + 3.14) = %f\n", 1e20+(- 1e20 + 3.14));  //   0.000000


(2) Computer Arithmetic

a)  Arithmetic operations have important mathematical properties

b)  We can't assume all "usual" mathematical properties
    
	(i)   due to finiteness of representations
    (ii)  Integer operations satisfy "ring" properties
                    Commutativity, associativity, distributivity
    (iii)  Floating point operations satisfying "ordering" properties
                    Monotonicity, values of signs

(3)  Understanding assembly is key to machine-level execution model!

# Great Reality 3：   Memory Matters: Memory is not unbounded
    
a)  The program doesn't exactly check the bound.

b)  copy_ij(row by row) does a much better job than copy_ji(column by column)

(5)  Course Perspective: for programmers
	Most Systems courses are builder-centric
	
	a)	Computer Architectures
		Design pipelined processor in verilog
	b)	Operating Systems
		Implement sample portions of operating system
	c)	Compilers
		Write compiler for simple languare
	d)	Networking
		Implement and simulate network protocols
