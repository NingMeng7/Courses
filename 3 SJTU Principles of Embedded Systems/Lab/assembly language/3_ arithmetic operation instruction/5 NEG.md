> 1. 格式

NEG OPR

> 2. 操作数

1. 通用寄存器
2. 存储器

> 3. 执行

OPR <- 0-OPR

> 4. 标志位

影响 AF,CF,OF,PF,SF,ZF

只有对-128或者-32768求相反数的时候OF=1，只有对0求相反数的时候CF=0

> 5. 示例程序

		MOV AX, 93A4H
		NEG AX	; (AX)=6C5CH
		NEG AX 	; (AX)=93A4H
