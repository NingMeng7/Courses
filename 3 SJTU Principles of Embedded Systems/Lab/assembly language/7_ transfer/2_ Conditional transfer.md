## 一. 条件转移指令
条件转移指令常常被用来构成分支结构，其执行分为两个过程，第一步，测试规定的条件，第二步，如果条件满足则转移到目的地址，否则继续顺序执行。条件转移指令只有一个操作数用来指明转移目的地址，但是它必须是一个短标号(-128~127)!. 大部分的条件转移指令(除了JCXZ) 将状态标志位的状态作为测试的条件，因此要配合着CMP 和 TEST 指令来使用，这两条指令不改变目标操作数的内容，但可以影响状态标志位。

    等于/零转移          JZ/JE        (ZF)=1  
    不等于/非零转移      JNZ/JNE       (ZF)=0
    正转移               JNS          (SF)=0
    负转移               JS           (SF)=1
    偶转移               JP            (PF)=1
    奇转移               JNP           (PF)=0
    低于则转移            JB           (CF) =1
    不低于则转移          JNB           (CF)=0
    高于则转移            JA            (CF)=0 且 ZF=0
    不高于则转移          JNA           （CF=1) 且 ZF=1
    CS等于0则转移         JCXZ           (CX=0)
 
## 1. 统计正负零元素
    
根据条件跳转到对应语句块，每个语句块加一份jmp next来结束这个语句块。
    
    XOR AL, AL
    MOV PLUS, AL
    MOV MINUS, AL
    MOV ZERO, AL  ; 清零累加器
    LEA SI, TABLE ; 取表首地址
    MOV CX. COUNT ; 表长
    CLD           ; 清状态标志位DF
    CHECK: LODSB  ；取一个数据到AL
    OR AL, AL
    JS X1         ; 负转移
    JZ X2         ; 零转移
    INC PLUS
    X1: INC MINUS
    JMP NEXT    
    X2: INC ZERO
    NEXT LOOP CHECK
    HLT

## 2. 根据开关状态执行(switch)

    MOV DX, 03FEH
    IN AL, DX
    CMP AL, 01H
    JZ SONE
    CMP AL, 02H
    JZ STWO
    CMP AL, 04H
    JZ STHREEE
    CMP AL, 08H
    JZ SFOUR
    CMP AL, 10h
    JZ SFIVE
    CMP AL, 20H
    JZ SSIX
    CMP AL, 40H
    JZ SSEVEN
    CMP AL, 80H
    JZ SEIGHT
    JMP OTHER

## 3. 统计Data段中数值等于/大于/小于8的字节的个数,AX保存结果

    MOV AX, DATA
    MOV DS, AX
    MOV BX, 0
    MOV AX, 0
    MOV CX, 8
  S:CMP BYTE PTR[BX], 8
    JNE NEXT; JNA NEXT; JNB NEXT
    INC AX
NEXT:INC BX
    LOOP S

## 二. 循环控制指令
> 1. Loop

先将CX减一，如果不等于0则转移，否则顺序执行下去，只能是短标号！ 对状态标志位没有影响
    mov cx, 10H
    s1: nop
        nop
        loop s1
        
> 2. LOOPE/LOOPZ

先将CX减一，如果CX不等于0 且 (ZF)=0(相等或者等于0条件) 则转移，否则顺序执行下去，只能是短标号！ 对状态标志位没有影响

> 3. LOOPNE / LOOPNZ
  
  ...
  
## 三. 过程调用指令
> 1. CALL near

> 2. CALL reg16/mem16

> 3. CALL far

先压CS，后压IP

> 4. CALL mem32

## 四. 返回指令格式

> 1. 从近距离返回

RET ; 取出栈里的IP

> 2. 从远过程返回

RET;  先取IP，后取CS

