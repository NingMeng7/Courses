> 1. 格式 

AAM

> 2. 操作数

默认为 AL, AH

> 3. 执行

1. AH <- AL/0AH 的商
2. AL <- AL/0AH 的余数

> 4. 示例程序

		MOV AL, 6
		MOV AH, 7
		MUL AH ; 02AH
		AAM ; 0402H
		
