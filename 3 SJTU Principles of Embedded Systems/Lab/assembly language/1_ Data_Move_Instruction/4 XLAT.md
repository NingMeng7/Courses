## 4. XLAT str-table

1. XLAT指令根据表中元素序号查表，应该预先把表的首地址传送到BX寄存器，元素的序号(位移量)送到AL，执行XLAT后，表中指令序号的元素存在AL，寻址表最大长度255个字节(AL限制).
2. 不影响标志位

		ASCII DB 30H,31H,32H,33H,34H,35H,36H,37H,38,39H

		MOV AL, 5
    	MOV BX, OFFSET ASCII
    	XLAT	 ; 则(AL) = 35H
    
    	MOV AL, 6
    	XLATB    ; 则(AL) = 36H
   

XLAT    ;不写操作数

XLAT src-table  ; 写操作数

XLATB   ; B 表示字节类型 

XLAT ES: src-table  ;段超越
