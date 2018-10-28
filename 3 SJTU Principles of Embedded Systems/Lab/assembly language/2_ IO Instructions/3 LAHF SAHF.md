> 1. 格式

LAHF

SAHF

> 2. 操作数

FLAGS and AH(隐含)

> 3. 执行

1. SAHF：将 AH 对应送到 PSW 的低字节 
2. LAHF：将 PSW 的低字节送到AH

> 4. 状态位

SAHF 会影响标志位的 SF, ZF, AF, PF, CF
