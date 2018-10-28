> 1. 格式

AAS

> 2. 操作数

隐含为AL 和 AH

> 3. 执行

1. if AL ^ 0FH > 9 或 (AF)=1, 则 AL<-(AL)-06H AH<-(AH)-1 AF<-1 CF<-(AF)
2. 否则, AL <- AL^0FH
3. 清除AL高四位

> 4. 标志位

影响AF, CF

> 5. 示例程序

		MOV AX, 0105H
		MOV BL, 04H
		SUB AL, BL ; AL=01H
		AAS ; AL=01H
		
		mov ax, 0a535h
		sub al, 39h ; A5FC,AF=1
		aas ; A4 06
