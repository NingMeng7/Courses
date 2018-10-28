> 1. 格式

[REPE/REPNE] CMPS [SEG:] SRCSTRING, [ES:] DSTSTRING ; 注意目的和源与一般情况相反

[REPE/REPNE] CMPSB

[REPE/REPNE] CMPSW

> 2. 执行

1. (DS:SI) - (ES:DI)
2. 更新SI,DI

REPE/REPZ: CX!=0 and ZF=1 时继续比较, 相等且串未完继续比较

REPNE/REPNZ: CX!=0 ZF=1 不相等, 且串未完继续比较

> 3. 示例程序

    LEA SI, ST1
    LEA DI, ST2
    MOV CX, 20
    CLD
    REPE CMPSB
    JCXZ WE ; CX=0 说明完全相等
    
    DEC SI  ; 结束的时候下标会比不相等元素大1，做修正
    DEC DI
    HLT
    WE : MOV SI, 0
    MOV DI, 0
    HLT
