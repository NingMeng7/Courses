> 1. 格式

DIV/IDIV SRC(字/字节)

> 2. 操作数

SRC可以是通用寄存器, 存储器操作数, 被除数是AX和DX

> 3. 执行

(AX)/SRC -> (AL, AH)

(DX,AX) / SRC -> (AX, DX)

前面那项是商, 后面那项是余数

IDIV: 四个均有符号, 余数和被除数符号相同

> 4. PSW

标志位未定义

当商超过寄存器表示的范围或者除以0，则溢出，执行0号中断，显示 DIVIDED OVERFLOW

> 5. 示例程序

		MOV DX, 1234H
		MOV AX, 5678H
		MOV BX, 3456H
		DIV BX ; AX = 590BH, DX=30C6H
