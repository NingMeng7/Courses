> 1. 格式

LEA REG, SRC

取SRC的偏移地址给REG

> 2. 操作数

1. SRC必须是内存操作数
2. REG必须是16位通用寄存器

> 3. 标志位

**不影响标志位**

> 4. 示例程序

		LEA SI, VAL
		LEA BX, [100H]
		LEA AX, [BX+SI+62H]
		LEA BX, ASCII
		MOV BX, OFFSET ASCII
		
		
