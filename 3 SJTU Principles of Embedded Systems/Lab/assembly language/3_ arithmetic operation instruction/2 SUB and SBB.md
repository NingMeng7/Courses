> 1. 格式

SUB/SBB DST, SRC

> 2. 操作数

同ADD/ADC

> 3. 执行

1. SUB：DST <- DST-SRC
2. SBB：DST <- DST-SRC-CF

> 4. 标志位

影响 AF,CF,OF,PF,SF,ZF

> 5. 示例程序

	SUB AL, 37H
	SUB DX, BX
	SUB CX, BETA[BX][DL]

	SBB BX, 1000H
	SBB CX, DX
	SBB AL, DATA1
	SBB [SI+6], 97H
