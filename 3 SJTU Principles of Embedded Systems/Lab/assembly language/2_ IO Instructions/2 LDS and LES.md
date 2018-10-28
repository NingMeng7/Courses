> 1. 格式

LDS REG, SRC

LES REG, SRC

> 2. 操作数类型

1. SRC 必须是双字内存操作数
2. REG 必须是16位通用寄存器

> 3. 执行

1. (SRC)->REG, (SRC+2)->DS
2. (SRC)->REG, (SRC+2)->ES

> 4. 标志位

执行完后不影响标志位

> 5. 示例程序
		
		;(DS) = C000H	(C0010H)=0180H	(C0012H)=2000H
		LDS SI, [10H]
		;(SI) = (0180H)	(DS)=(2000H)
		
		
