> 1. 格式

[REP]STOS [ES:] dst-string

[REP]STOSB
[REP]STOSW

> 2. 执行

1. (ES):(DI) <- AL/AX
2. 更新DI
3. 加上REP将会一直执行直到CX=0

> 3. 示例程序

    LEA DI, AREA
    MOV AX, '##'
    MOV CX, 100
    CLD
    REP STOSW
    HLT
