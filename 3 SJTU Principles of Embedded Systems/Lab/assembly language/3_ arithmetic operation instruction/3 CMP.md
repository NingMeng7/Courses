> 1. 格式

CMP OPR1, OPR2

> 2. 操作数

同ADD/ADC

> 3. 执行

OPR1 - OPR2: 即SUB,但是结果不送OPR1, 只影响标志位

> 4. 示例程序

CMP 常常用来实现分支语句if或者switch, 通过CMP来得到标志位,再与条件转移指令配合选择不同的分支

		
		CMP AX, AX; ZF=1, PF=1,SF=0,CF=0,OF=0

		MOV AX, 8
		MOV BX, 3
		CMP AX, BX; (5) ZF=0 PF=1 SF=0 CF=0 OF=0

		CMP AX, BX
		; ZF=1 则 (AX) = (BX)
		; ZF=0 则 (AX)!=(BX)
		; CF=1 则 (AX) < (BX)
		; CF=0 则 (AX) >= (BX)
		; CF=0 且 ZF=0 (AX)>(BX)
		; CF=1 或者 ZF=1 则 (AX) <= (BX)
