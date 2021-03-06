; Description：在内存DATA单元存放有一个字的数据，统计其中含有0的个数，送到RESULT单元

DAT SEGMENT
	DATA	DW	0F7F7H
	RESULT	DB	?
DAT	ENDS

STACK SEGMENT
	ST	DB	100 DUP(?)
STACK ENDS

CODE 	SEGMENT
		ASSUME CS:CODE, DS:DAT, SS:STACK

MAIN	PROC	FAR
STACK:	MOV		AX, STACK
		MOV		SS, AX
		PUSH	DS	;返回DOS用
		MOV		AX, 0
		PUSH	AX
		MOV		AX, DAT
		MOV		DS, AX
		MOV		CX, 16
		MOV		BL, 0
		MOV		AX, DATA
L:		SHL		AX, 1
		JC		NEXT	;CF=1则jmpNEXT 跳过BL增加
		INC		BL
NEXT:	LOOP	L
		
		MOV		RESULT, BL
MAIN	ENDP
CODE	ENDS
		END		START
	
