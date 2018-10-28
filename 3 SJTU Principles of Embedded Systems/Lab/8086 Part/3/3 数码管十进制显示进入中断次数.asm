;--------------------------------------------------------------------------
;
;              Build this with the "Source" menu using
;                     "Build All" option
;
;--------------------------------------------------------------------------
;
;                           实验三程序通用框架
;
;--------------------------------------------------------------------------
; 功能： 程序框架					                            				   |
; 编写：《嵌入式系统原理与实验》课程组                   				   |
; 版本：3.5
; 修订：B
;--------------------------------------------------------------------------


		DOSSEG
		.MODEL	SMALL		; 设定8086汇编程序使用Small model
		.8086				; 设定采用8086汇编指令集

;-----------------------------------------------------------
;	定义堆栈段                                             |
;-----------------------------------------------------------
	.stack 100h				; 定义256字节容量的堆栈

;-------------------------------------------------------------------------
;	符号定义                                                              |
;-------------------------------------------------------------------------
;
;
; 8253芯片端口地址 （Port Address):
L8253T0			EQU	100H			; Timer0's port number in I/O space
L8253T1			EQU 	102H			; Timer1's port number in I/O space
L8253T2			EQU 	104H			; Timer2's port number in I/O space
L8253CS			EQU 	106H			; 8253 Control Register's port number in I/O space
;
; 8255芯片端口地址 （Port Address):
L8255PA			EQU	121H			; Port A's port number in I/O space
L8255PB			EQU 	123H			; Port B's port number in I/O space
L8255PC			EQU 	125H			; Port C's port number in I/O space
L8255CS			EQU 	127H			; 8255 Control Register's port number in I/O space
;
;  中断矢量号定义
IRQNum			EQU	2CH			; 中断矢量号,要根据学号计算得到后更新此定义。

Patch_Protues	EQU		IN AL, 0	;	Simulation Patch for Proteus, please ignore this line

;=======================================================================
; 宏定义
;=======================================================================

; 修补Proteus仿真的BUG，参见程序段中的使用说明
    WaitForHWInt MACRO INTNum		; INTNum is the HW INT number
		MOV AL, INTNum   			;
		OUT 0,AL					;
		STI
		CLI
    ENDM



;-----------------------------------------------------------
;	定义数据段                                             |
;-----------------------------------------------------------
		.data					; 定义数据段;

DelayShort	dw	200				; 短延时参量	
DelayLong	dw	400			; 长延时参量


; SEGTAB是显示字符0-F，其中有部分数据的段码有错误，请自行修正
SEGTAB  
    DB 3FH	; 7-Segment Tube, 共阴极类型的7段数码管示意图
		DB 06H	;
		DB 5BH	;            a a a
		DB 4FH	;         f         b
		DB 66H	;         f         b
		DB 6DH	;         f         b
		DB 7DH	;            g g g 
		DB 07H	;         e         c
		DB 7FH	;         e         c
		DB 6FH	;         e         c
    DB 77H	;            d d d     h h h
		DB 7CH	; ----------------------------------
		DB 39H	;       b7 b6 b5 b4 b3 b2 b1 b0
		DB 5EH	;       DP  g  f  e  d  c  b  a
		DB 79H	;
		DB 71H	;

;-----------------------------------------------------------
;	定义代码段                                             |
;-----------------------------------------------------------
		.code						; Code segment definition
		.startup					; 定义汇编程序执行入口点
;------------------------------------------------------------------------
		Patch_Protues				; Simulation Patch for Proteus,
									; Please ignore the above code line.
;------------------------------------------------------------------------

START:								; 代码需要修改，否则无法编译通过
									; 代码需要修改，否则无法编译通过
									; 以下的代码可以根据实际需要选用
		CLI							; 关中断
		MOV AX, @DATA				
		MOV DS, AX				; 初始化DS段寄存器
		MOV SI, 0H				; 累加器归0
		CALL INIT8255
		CALL INIT8253				; 初始化8253
		
		MOV  BL, IRQNum				; 取得中断矢量号
		CALL INT_INIT				; 初始化中断向量表
		STI
Display_Again:
		CALL DISPLAY8255			; 驱动四位七段数码管显示							; 以下的代码可以根据实际需要选用

;===================================================================================
; Attention:
; The following codes is a Patching for Proteus 8086 Hardware Simulation Bug.
; Use these codes in the case you want the 8086 to halt and waiting for HW INT only! 
; You can treat it as if it doesn't exist. 
;
; If you need use HW INT, please uncomment it, or
; Don't modify it, leave it here just as it is.
;		WaitForHWInt IRQNum		; 8086中断仿真补丁代码，直接忽略此代码行的存在即可
;====================================================================================
		JMP	Display_Again

		HLT							; 停止主程序运行
;=====================================================================================




;--------------------------------------------
;	子程序定义
;
;--------------------------------------------
;                                           |
; INIT 8255 					            |
;                                           |
;--------------------------------------------
INIT8255 PROC
   mov al, 10000001B   ;A0输出 B0输出 C低in高out
   mov dx, L8255CS
   out dx,al
   RET
INIT8255 ENDP

;--------------------------------------------
;                                           |
; INIT 8253 					            |
;                                           |
;--------------------------------------------
INIT8253 PROC

;设定Timer0的初始值
	mov dx, L8253CS
	mov al, 00110110B
	out dx, al
	mov dx, L8253T0
	mov al, 10H
	out dx, al
	mov al, 27H
	out dx, al

;	设定Timer1的初始值
	mov dx, L8253CS
	mov al, 01010110B
	out dx, al
	mov dx, L8253T1
	mov al, 64H	;1s = 10ms * 100
	out dx, al

		RET
INIT8253 ENDP

;--------------------------------------------
;                                           |
;	SETPC6                              |
;--------------------------------------------
SETPC6 PROC
  mov dx,L8255PC
	in  al, dx
	push ax
	and al,00000001B
	cmp al, 0H
	je RESETPC6;if al == 0 reset
	pop ax
	or al,01000000B
	jmp OUTPUT
RESETPC6:	pop ax
	        and al, 10111111B
OUTPUT:		out dx, al
		RET
SETPC6 ENDP

;--------------------------------------------
;                                           |
; DISPLAY  STUDENTS ID				 		|
;                                           |
;--------------------------------------------

DISPLAY8255 PROC		
		mov al, 0FDH
		mov dx, L8255PA
		out dx, al
		mov dx, L8255PB
		mov ax, si
		mov bl, 0AH
		div bl
		mov bl, ah
		mov bh, 0H
		mov al, SEGTAB[bx]
		out dx, al
		call DELAYL
		
		mov al, 0FEH
		mov dx, L8255PA
		out dx, al
		mov dx, L8255PB
		mov ax, si
		mov bl, 0AH
		div bl	; ah余数 al商
		mov ah, 0H
		mov bl, 0AH
		div bl
		mov bl, ah
		mov bh, 0H
		mov al, SEGTAB[bx]
		out dx, al
		call DELAYL
		
		RET
	
DISPLAY8255 ENDP


;--------------------------------------------------------------
;                                                             |                                                            |
; Function：DELAY FUNCTION                                    | 
; Input：None												  |
; Output: None                                                |
;--------------------------------------------------------------

DELAY 	PROC
    	PUSH CX
    	MOV CX, DelayShort
D1: 	LOOP D1
    	POP CX
    	RET
DELAY 	ENDP

;--------------------------------------------------------------
;                                                             |                                                            |
; Function：DELAY FUNCTION                                    | 
; Input：None												  |
; Output: None                                                |
;--------------------------------------------------------------

DELAYL 	PROC
    	PUSH CX
    	MOV CX, DelayLong
D1: 	LOOP D1
    	POP CX
    	RET
DELAYL 	ENDP

;-------------------------------------------------------------
;                                                             |                                                            |
; Function：INTERRUPT Vector Table INIT						  |
; Input: BL = Interrupt number								  |
; Output: None			                                	  |
;                                                             |
;-------------------------------------------------------------	
INT_INIT	PROC FAR			; 此部分程序有删节，需要修改
	CLI						; Disable interrupt
	MOV AX, 0
	MOV ES, AX
	MOV AX, CS
	mov word ptr es:[IRQNum*4], offset MYIRQ
	mov word ptr es:[IRQNum*4+2], AX
	mov di, IRQNum
	RET
	;准备操作中断向量表
	
; Put your code here

; 提示：可参考使用SET、OFFSET运算子获取标号的段地址值和段内偏移量
		
INT_INIT	ENDP

		
;--------------------------------------------------------------
;                                                             |                                                            |
; FUNCTION: INTERRUPT SERVICE  Routine （ISR）				  | 
; Input::                                                     |
; Output:                                                     |
;                                                             |
;--------------------------------------------------------------	
		
MYIRQ 	PROC FAR				; 此部分程序有删节，需要修改
   inc si ; 计数器
   
   push ax
   push bx
   push dx
   mov dx, L8255PC
   in al, dx
   xor al, 10000000B
   out dx, al
   pop dx
   pop bx
   pop ax 
   IRET; 中断返回
MYIRQ 	ENDP

	END						; 指示汇编程序结束编译
