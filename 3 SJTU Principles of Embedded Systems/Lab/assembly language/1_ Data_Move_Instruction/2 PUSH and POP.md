1. PUSH 和 POP 都是堆栈指令，堆栈指令只能对字操作数进行。
2. SS:SP随时指在堆栈段的栈顶上(开始在堆栈段最高地址加1)
3. **不影响标志位**

> 1. PUSH SRC(字)

SP-2->SP

SRC->(SS:SP)

操作数可以是 **16位通用寄存器、段寄存器、存储器**，不能是立即数

> 2. POP DST(字)

(SS:SP)->DST
SP+2->SP

操作数可是是 **16位通用寄存器、段寄存器(除了CS)、存储器**，不能是立即数


高位在高地址，1234，12在高地址

    MOV AX, 1000H
    PUSH AX
    POP BX
    
    PUSH CS
    POP AX

    PUSH [DI]
    PUSH [BX+DI+05H]
    POP CX
