# 1.1 Information is Bits + Context 

(1)	We begin our study of systems by tracing the life time Hello.c

	#include <stdio.h>
	
	int main()
	{
		printf("Hello, world\n");
		return 0;
	}

　Our hello program begins life as a **source file** that the programmer creates with an editor and saves in a text file called hello.c. In fact, the source file is a sequence of bits, each with a value of **0 or 1**, organized in 8-bit chunks called **byte**. As you may know, most of the computers systems represent text characters using the **ASCII** standard, i.e., the standard represents each character with a unique byte-size integer value.

　The hello pragram illustrates a fundamental idea: **All information in system-including disk files, programs, stored in memory, user data stored in memory, and data transferred across a network——is represented as a bunch of bits. The only thing that distinguishes different data objects is the context in which we view them.** For instance, you may know the example of assembly. We treat the data as our code if and only if by the value of cs:ip.

# 1.2 Programs are translated by other programs into different forms

　The hello program begins life as a high-level C program since it can be read and understand by human beings in that form! However, the individual C statements must be translated by other programs into a sequence of **low-level machine-language** instructions in order to be run on the system. These instructions are packaged in a form called an **executable object program** and stored as a binary disk file. Object Programs are also referred to as **executable object files**.

## Translation performed in the sequence of four phase
(1)	Preprocessing phase
	
　The preprocessor(cpp) modifies the original C program according to directives that begin with the '#' character. For instance, the #include<stdio.h> command tells the preprocessor to read the contents of the system header file stdio.h and **insert it directly into the program text**. You must be careful about the difference between <> and "". After this phase, we get another C program typically with the .i suffix.

(2)	Compilation phase 
　
　The compiler translates the text file hello.i into the text file hello.s, which contains an **assembly-languare** program. Assembly languare is useful because it provide a common output language for different compilers for types of high-level languages.

(3)	Assembly phase

　Next, the assembler translates hello.s into **machine-language instructions**, packages them into a form known as a **relocatable object program**, and stores the result in the object file hello.o. This file is a binary file and if we veiw it with a text editor, it would appear to be gibberish.

(4) Linking phase

　Notice that the program did calls the printf function which is part of the standard C library provided by every C compiler.It resides in a separate precompiled object file called printf.o which must somehow be merged with our hello.o program. The merging is handled by the linker. The output of linking phase is an executable object file called hello file, which is ready to be loaded into memory and executed by the system.

# 1.3 It pays to Understand How Compilation Systems Work

	(1)    Is a switch statement always more efficient than a sequence of if-else statements?
	(2)	How much overhead is incurred by a function call?
	(3)	While loop vs for loop, which one is more efficient?
	(4)	Are pointer references more efficient than array indexes?
	(5)	Why does our loop run much faster if we sum into a local variable instead of an arguement that is passed by reference?
	(6)	How can a function run faster when we simply rearrange the parentheses in an arithmetic expression? 
	(7)    What does it mean when the linker reports that it can't resolve a reference?
	(8)	What is the difference between a static variable and a global variable?
	(9)	What happens if you define two global variable in different C files with the same name?
	(10)   What's the difference between a static library and a dynamic library?
	(11)   What does it matter what order we list libraries on the command line?
	(12)   Why do some linker-related errors not appear until run time?
	(13)   These problems shall be handled within one year!
	
　There are some significant reasons why programmers need to understand how the compilation systems work:

	a)  Optimizing program performance.
	b)  Understanding link-time errors.
	c)	Avoiding security holes. 	

# 1.4 Processors Read and Interpret Instructions Stored in Memory
### 1.4.1 Hardware Organization of a System

(1) Buses: Running through the system is a collection of **electrical conduits** called buses that carry bytes of information back and forth between the components. We regard **word size** as a fundamental parameter of a sepcific system.

(2) I/O Devices: IO devices are the system's connection to the external world. Each I/O device is connected to the I/O bus by either a controller or an adapter. The distinction between the two is mainly one of packaging. Controllers are chip sets in the di\evice itself or on the system's main printed circuit board(often called motherboadrd). An adapter is a card that plugs into a slot on the motherboadrd. Regardless, each of two holds the purpose to transfer information back and forth between the I/O bus and an I/O device.

(3) Main Memory: The main memory is a temporary storage device that holds both a program and the data it manipulates while the processor is executing the program. Physically, main memory consists of a collection of *danamic random access memory* (**DRAM**) chips. Logically, memory is organized as a linear array of **bytes**(basic memory unit), each with its own unique address(array index) starting at zero.

(4) Processor: The central processing unit (CPU), or simply processor, is the engine that interprets (or executes) instructions stored in main memory. At its core is a word-size storage device (or register) called the program counter(PC). At any point in time, the PC points at (by containing the address of) some machine-languare instruction in main memory. We distinguish the instruction from the common datas by CS:IP!
In general, the processor execute a single instruction involving a series of steps: 
	
	(i)	The processor reads the instruction from memory pointed at by the PC
	(ii)   Interpret the bits in the instruction
	(iii)  Perform some simple instruction wchih may or may not be contiguous in memory to the instruction that was just executed.

**This example of hello.c run on the hardware system should present some intuitions to you. Typically, a system spends a lot of time moving information from one place to another.**

# 1.5 Caches Matter
　The hello program are originally stored on disk. When the program is loaded, they are copied to main memory. As the processor runs the program, instructions are copied from main memory into the processor. Similarly, in order to display the data, the data string shall be copied from main memory to the display device. All the processes above indicate that how faster data can be tranferred matters. 

　However, because of physical laws, large storage devices are slower than smaller storage devices. And faster devices are more expensive to build than their slower counterparts. For example, the disk drive on a typical system might be 1000 times larger than the main memory, but it might take the processor 10000000 times longer to read a word from disk than from memory. There is a severe processor-memory gap. The processor can read data from the register file almost 100 times faster than from memory! To deal with the processor-memory gap, **cache memories** serve as temporary staging areas for information that the processor is likely to read in the very near future.

　An **L1 cache** can holds tens of thousands of bytes and can be accessed nearly as fast as register file. A larger **L2 cache** with hundreds of thousands to millions of bytes is connected to the processor by a special bus and it might take 5 times longer for the processor to read data than from L1 cache, however, this is still 5 to 10 times faster than accessing the main memory. By the way, the L1 and L2 caches are implemented with a hardware technology known as *static random access memory* (**SRAM**).	

# 1.6 Storage Devices Form a Hierarchy
The notion presented above that inserting a smaller, faster device(e.g. cache memory) between the preocessor and a larger, slower 
(e.g., main memory) to handle the gap turns out to be a general idea. The main idea of a memory hierarchy is that **storage at one level serves as a cache for storage at the next lower level**.

# 1.7 The Operating System Manages the Hardware
We can think of the operating system as a layer of software interposed between the application program and the hardware. All attempts by an application program to manipulate the hardware must go through the operating system. For example, when we run our hello program, the program accesses the keyboard, display, disk or main memory indirectly. They rely on the services provided by the operating system. 

The operating sysytem has two primary purposes:

    (a) to protect the hardware from misuse by runaway applications (and computer virus?)
    (b) to provide applications with simple and uniform mechanisms for manipulating complicated and often wildly different 
        low-level hard devices.
In order to achieve both goals, the operating system realizes some abstractions: **processes, virtual memory, and files**.

    (a) files: abstraction for I/O devices.
    (b) virtual memory: abstraction for both the main memory and disk I/O devivces
    (c) processes: abstractions for the processor, main memory, and I/O devices.
    
## 1.7.1 Processes

When a program such as our hello program runs on a modern system, the operating system provides an illusion that the program is the only one running on the system. The illusion is provided by the notion of process, one of the most important and successful ideas in computer science.

According to our intuitions, the operating system can run multiple processes at one time since we can listen to music and type at the same time. We will show you the implement of this illusion.

A process is the operating system's abstraction for a running program. Multiple processes run **concurrently** on the same system, and each process appears to have exclusive use of the hardware. By **concurrently**, we mean that the instructions of one process are interleaved with the instructions of another process!

A single CPU can appear to execute multiple processes concurrently by having the processor switch among them. At any point in time, a uniprocessor system can only execute the code for a single process. However, the operating system keeps track of all the state information that the process needs in order to run. The state, which is known as the **context**, includes information such as the current values of PC, the register file, and the contents of main memory. When the operating system decides to transfer control from the current process to some new processes, it performs a **context switch** by saving the context of the current process, restoring the context of the new process, and then passing control to the new process. The new process picks up exactly where it left off!

## 1.7.2 Threads

Although we normally think of a process as having a single control flow, in modern systems a process can actually consist of multiple execution units, called *threads*, each running in the context of the process and sharing the same code and global data. Threads are easier to share data than multiple processes. Threads are typically more efficient than processes and multi-threading is also one way to make programs run faster when multiple processors are available.

## 1.7.3 Virtual memory
*Virtual Memory* is an abstraction that provides each process with the ilusion that it has exclusive use of the main memory. Each process has the same uniform view of memory: **virtual address space**.

    From the bottom(lowest addresses) to the top region of our address space:

    a) Program code and data: Code begins at the same fixed address for all processes, followed by data 
       locations that correspond to global C variables. The code and data areas are initialized indirectly
       from the contents of an executable object file. The area is fixed in size once the process begins 
       running.

    b) Heap. The code and data areas are followed immediately by the run-time heap. The heap expands and 
       contracts dynamically at run time as a result of calls to C standard library routines such as malloc
       and free.

    c) Shared libraries: Near the middle of the address space is an area that holds the code and data for 
       *shared libraries*.

    d) Stack: At the top of the user's virtual address space is the user stack that the compiler uses to 
       implement function calls. The stack expands and contracts dynamically during the execution of the 
       program.

    e) Kernel virtual memory: The top region of the address space is reserved for the kernel. application 
       programs are not allowed to read/write the contents of this are or to directly call functions 
       defined in the kernel code. Instead, they must invoke the kernel to perform these operations.
       
## 1.7.4 Files
A file is a sequence of bytes, nothing more and nothing less. We can model every I/O device, including disks, keyboards, displays and even networks as a file. The uniform veiw of all the varied I/O devices let the application programmers who manipulate the contents of a disk file are blissfully unaware of the specific disk technology.

## 1.8 Amdahl's Law
TO significantly speed up the entire system, we must improve the speed of a very large fraction of the overall system.        

## 1.9 Concurrency and Parallelism
Concurrency is when two or more tasks can start, run, and complete in overlapping time periods. It doesn't necessarily mean they'll ever both be running at the same instant. For example, multitasking on a single-core machine.

Parallelism is when tasks literally run at the same time, e.g., on a multicore processor

