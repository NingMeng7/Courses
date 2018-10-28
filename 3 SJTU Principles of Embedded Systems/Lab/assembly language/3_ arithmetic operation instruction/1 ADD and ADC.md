> 1. 格式

ADD/ADC DST, SRC (字节/字)

> 2. 操作数

1. GR1<-GR1+GR2
2. MEM<-MEM+GR
3. GR<-MEM+GR
4. MEM<-立即数+MEM
5. GR<-立即数+GR
6. 不能两个都是存储器!
7. 不能有段寄存器

> 3. 执行

1. ADD: DST <- DST+SRC
2. ADC: DST <- DST+SRC+CF

> 4. 标志位

对 CF, OF, PF, SF, ZF, AF 有影响.

> 5. 示例程序
    
    ;  Description: 完成32位加法, DX作为高位, AX作为低位
    DATA SEGMENT
    ONE DW  9998H, 1110H
    TWO DW  8887H, 2221H
    DATA ENDS
    
    CODE SEGMENT
    MOV AX, DATA
    MOV DS, AX
    MOV AX, [ONE]
    ADD AX, [TWO]
    
    MOV DX, [ONE+2]
    ADC AX, [TWO+2]
    
    CODE ENDS
