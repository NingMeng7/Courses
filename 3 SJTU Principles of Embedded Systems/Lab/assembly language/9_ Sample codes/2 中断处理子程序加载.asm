COMMENT 1
中断类型号为60H

INT-INT PROC FAR
...   ;保护现场
SUB AX, AX
MOV ES, AX
MOV BX, OFFSET inthandler ; 取偏移量
MOV AX, SEG inthandler  ; 取段地址
MOV DI, 60H
SHL DI, 1
SHL DI, 1
MOV ES:[DI], BX
MOV ES:[DI]+2, AX
...   ; 恢复现场
RET
INT-INTENDP
