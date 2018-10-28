> 1. 格式

AND OR XOR dst, src

> 2. 操作数

1. 两个操作数不能同时为存储器
2. 立即数只能作为源操作数

> 3. 执行

按位与/或/异或

> 4. 状态位

CF、OF清零, 影响SF,ZF,PF

> 5. 示例程序
		
		AND AL, 11111101B ; 置第二位为0
		
		OR  AL, 00000010B ; 置第二位为1
		
		XOR AL, 00000010B ; 置第二位为反
		
		XOR AL, AL ; 清零AL
		
		AND AX, 0FH ; ASCII -> 二进制
		
		OR AX, 30H ; 二进制 -> ASCII
		
		AND AL, 7FH ; 奇校验
		JNP NEXT
		OR AL, 80H
		NEXT:...
