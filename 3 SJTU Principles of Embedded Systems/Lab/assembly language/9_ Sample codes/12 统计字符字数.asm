; Description: 统计从40000H开始的16K单元中'A'的个数，结果放在DX

DAT SEGMENT 
  BUFDB 1024 DUP('GIVE AN EXAMPLE!')
DAT ENDS

STACK SEGMENT
  ST  DB  100 DUP(?)
STACK ENDS

CODE  SEGMENT
  ASSUME  CS:CODE, DS:DAT, SS:STACK, ES:DAT
MAIN  PROC  FAR
START:  MOV AX, STACK
        MOV SS, AX
        PUSH DS
        MOV AX, 0
        PUSH AX
        MOV AX, DAT
        MOV DS, AX
        MOV ES, AX
        MOV DX, 0
        MOV CX, 16384
        LEA DI, BFU
        MOV AL, 'A'
        CLD
NEXT2:  SCASB
        JNZ NEXT1 ; 不是A就跳到INC DX
        INC DX
NEXT1:  NOP
        LOOP  NEXT2
        RET
MAIN  ENDP
CODE  ENDS
      END START
