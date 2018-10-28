> 1. 格式

DAS

> 2. 操作数

隐含为AL

> 3. 执行

1. if (AL^0FH)>9 或 (AF)=1 则 AL<-(AL)-06H AF<-1
2. if (AL)>9FH 或 (CF)=1 则 (AL)<-(AL)-60H CF<-1

> 4. 标志位

DAS 影响 AF, CF, SF, ZF, PF 不影响OF

> 5. 示例程序

		MOV AL, 83H
		MOV BL, 38H
		SUB AL, BL ; (AL)=4BH
		DAS ; (AL)=45H
