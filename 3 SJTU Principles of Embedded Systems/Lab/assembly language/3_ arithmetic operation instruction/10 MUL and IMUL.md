> 1. 格式

MUL/IMUL SRC(字/字节)

> 2. 操作数

SRC可以是通用寄存器, 存储器操作数, 但不能是立即数，另一个乘数是累加器AX/AL

需要注意的是, 存储器操作数一定要指明是byte还是word

> 3. 执行

1. (AL)*SRC -> (AX)

2. (AX)*SRC -> (DX,AX)

> 4. 状态位

影响CF,OF

如果运算结果的高半位(AH或者DX)等于0，那么CF=OF=0, 否则CF=OF=1, 表明AH或者DX是否含有有效位

> 5. 示例程序

		MUL AL ; AL*AL
		MUL BX ; AX*BX
		MUL BYTE PTR [DI+6] ; AL * 字节型存储器单元
		
		MOV AL, 14H
		MOV CL, 05H
		MUL CL; (AX)=0064H, (CF)=(OF)=0
		
		MOV AX, 04E8H ; IMUL 默认认为是带符号数进行乘法
		MOV BX, 4E20H
		IMUL BX ; (DX:AX) = (017FH:4D00H) CF=OF=1	
