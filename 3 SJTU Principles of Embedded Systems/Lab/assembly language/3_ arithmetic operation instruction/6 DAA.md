> 1. 格式

DAA (紧跟在ADD/ADC/INC后面) ： 加法的BCD码调整

> 2. 操作数

隐含为AL

> 3. 执行

(AL)->(AL)

1. 如果(AL)^(0FH) > 9 或者 (AF)=1, 则 AL<-(AL)+06H AF<-1
2. 如果(AL)^(0F0H) > 9FH 或者 (CF)=1，则 AL<-(AL)+60H CF<-1
3. 如果以上两点都不成立，则，清除标志位AF和CF

> 4. 标志位

影响 AF, CF, PF, SF, ZF 不影响OF

> 5. 示例程序


		MOV AL, 28H
		ADD AL, 68H	; (AL)=90H
		DAA	; (AL)=96H CF=0, AF=1,SF=1
		
		mov al, 68h
		mov bl, 59h
		add al, bl ; (al)=c1h (af)=1
		daa ; (al)=27h (cf)=1 (af)=1
		
		
