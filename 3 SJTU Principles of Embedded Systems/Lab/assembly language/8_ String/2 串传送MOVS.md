> 1. 格式

[REP]MOVS [ES:] dststring, [seg:] srcstring

[REP]MOVSB

[REP]MOVSW

> 2. 执行

1. (ES):(DI) <- (DS:SI)
2. 更新SI/DI

> 3. 示例程序

		REP MOVS DATA2, DATA1 ; DATA1 和 DATA2 必须事先确定类型
		
		MOVS BUFFER2, ES:BUFFER1
		
		REP MOVS WORD PTR[DI], [SI]
		
		REP MOVSB
		
		MOVSW
		
		
		LEA SI, BUFFER1
		LEA DI, BUFFER2
		MOV CX, 200
		CLD
		REP MOVSB
		HLT
