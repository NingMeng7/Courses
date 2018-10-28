> 1. 格式

INC/DEC OPRD

> 2. 操作数

通用寄存器和存储器

> 3. 执行

1. INC：OPRD <- OPRD+1
2. DEC：OPRD <- OPRD-1

> 4. 标志位

**影响标志位AF, OF, PF, SF, ZF 但是不影响 CF**

主要用在循环中修改地址指针和循环次数计数

> 5. 示例程序

		MOV CX, 5
		MOV SI, 0
		CLC
S:
		MOV AL, DATA2[SI]
		ADC DATA1[SI], AL
		INC SI  ; 加一指令, 影响SF,ZF,AF,PF,OF,但不影响CF!!!! 不能对段寄存器操作
		LOOP S
		LT
