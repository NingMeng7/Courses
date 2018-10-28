; Description: 从BUF单元开始存放15个字节型数据, 将其中的负数和0分别送往MINUS 和 ZERO

DAT SEGMENT
  BUF DB 17H, 23H, 0F8H, 0, 4FH, 73H, 4EH, 0FBH
  DB 0, 0F0H, 9EH, 51H, 82H, 9CH, 0
  MINUS DB 15 DUP(?)  
  ZERO  DB 15 DUP(?)
DAT ENDS

STACK SEGMENT
  ST  DB  100 DUP(?)
STACK ENDS

CODE SEGMENT
  ASSUME  CS:CODE, DS:DAT, SS:STACK
MAIN PROC FAR
START:  MOV AX, STACK
        MOV SS, AX
        PUSH DS
        MOV AX, 0
        PUSH AX
        MOV AX, DAT
        MOV DS, AX
        
        MOV CX, 15
        MOV DI, OFFSET BUF
        MOV SI, OFFSET MINUS
        MOV BX, OFFSET ZERO
NEXT1:  MOV AL, [DI]
        TEST AL, 80H
        JNZ MI
        CMP AL, 0
        JZ  ZO
        JMP NEXT2
ZO:     MOV [BX], AL
        INC BX
        JMP NEXT2
MI:     MOV [SI], AL
        INC SI
NEXT2:  INC DI
        LOOP  NEXT1
        RET
MAIN  ENDP
CODE  ENDS
      END START
