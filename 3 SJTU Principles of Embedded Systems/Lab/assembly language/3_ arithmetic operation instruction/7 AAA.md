> 1. 格式

AAA

> 2. 操作数

AL,AH,CF

> 3. 执行

(AL)->(AL)
(AH)+CF->AH

1. 如果(AL)^(0FH) > 9 或者 (AF)=1, 则: (AL)<-(AL)+06H (AH)<-(AH)+1 AF<-1
2. 否则 CF<-(AF), AL<-(AL^0FH)
3. 再将al高四位清零

将一位十六进制数转换成非压缩的ASCII码

> 4. 状态位

对AF,CF有影响,其他无定义

> 5. 示例程序

		MOV AX, 6
		ADD	AX, 7	; (AX) = 0DH
		AAA	; DX=0103H
		
		MOV AX, A535H
		ADD AL, 39H	 ; (AX) = A56EH
		AAA	; (AX) = A604H, AF=CF=1
