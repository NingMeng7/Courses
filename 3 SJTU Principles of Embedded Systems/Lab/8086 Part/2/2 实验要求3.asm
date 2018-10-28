;-----------------------------------------------------------
;
;              Build this with the "Source" menu using
;                     "Build All" option
;
;-----------------------------------------------------------
;
;                           实验二示例程序 

;-----------------------------------------------------------
;                                                          |
;                                                          |
; 功能：控制7段数码管的显示                                |
; 编写：《嵌入式系统原理与实验》课程组                     |
;-----------------------------------------------------------
		DOSSEG
		.MODEL	SMALL		; 设定8086汇编程序使用Small model
		.8086				; 设定采用8086汇编指令集
;-----------------------------------------------------------
;	符号定义                                               |
;-----------------------------------------------------------
;
; 8255芯片端口地址 （Port number）分配:
PortA	EQU	90H		;10010000		Port A's port number in I/O space
PortB	EQU 	92H		;10010010 		Port B's port number in I/O space
PortC	EQU 	94H		;10010100 		Port C's port number in I/O space
CtrlPT	EQU 	96H		;10010110 		8255 Control Register's port number in I/O space
;
Patch_Protues	EQU		IN AL, 0	;	Simulation Patch for Proteus, please ignore this line，don't move this!
; 注意A0 A1接的是Addr1 Addr2
; PA作为输出端，高四位选通二极管（高电平选通），低四位选通数码管（低电平选通）
;-----------------------------------------------------------
;	定义数据段                                             |
;-----------------------------------------------------------
		.data					; 定义数据段;

DelayShort	dw	400   			; 短延时参量	
DelayLong	dw	40000			; 长延时参量

; 显示数字
DISCHAR DB 01,02,03,04

; SEGTAB是显示字符0-F，其中有部分数据的段码有错误，请自行修正
SEGTAB  DB 3FH	; 7-Segment Tube, 共阴极类型的7段数码管示意图		111111
		DB 06H	;						110
		DB 5BH	;            a a a				1011011
		DB 4FH	;         f         b				1001111
		DB 66H	;         f         b				1100110
		DB 6DH	;         f         b				1101101
		DB 7DH	;            g g g 				1111101
		DB 07H	;         e         c				111	
		DB 7FH	;         e         c				1111111
		DB 6FH	;         e         c				1101111
        DB 77H	;            d d d     h h h				1110111
		DB 7CH	; ----------------------------------		1111100
		DB 39H	;       b7 b6 b5 b4 b3 b2 b1 b0			111001
		DB 5EH	;       DP  g  f  e  d  c  b  a			1011110
		DB 79H	;						1111001
		DB 71H	;						1111110


;-----------------------------------------------------------
;	定义代码段                                             |
;-----------------------------------------------------------
		.code						; Code segment definition
		.startup					; 定义汇编程序执行入口点
;------------------------------------------------------------------------
		Patch_Protues				; Simulation Patch for Proteus,
									; Please ignore the above code line.
;------------------------------------------------------------------------


; Init 8255 in Mode 0
; PortA Output, PortB Output
;
		mov al,10001001B	;A:方式0输出	C口高四位低四位输入 	B:方式0输出	
		OUT CtrlPT,AL	
;
; 把数字1、2、3、4显示在数码管上
;

L1: 	    
      in al, PortC
	    mov bl, al
	    and al, 0F0H	;取高四位
	    add al, 0EH		
	    out PortA, al
	    call DELAY
	    
	    and bl, 0FH
	    mov al, SEGTAB[BX]
	    out PortB, al
	    call DELAY

	    JMP L1
	    
	    RET

;--------------------------------------------
;                                           |
; Delay system running for a while          |
; CX : contains time para.                  |
;                                           |
;--------------------------------------------

DELAY1 	PROC
    	PUSH CX
    	MOV CX,DelayLong	;
D0: 	LOOP D0
    	POP CX
    	RET
DELAY1 	ENDP


;--------------------------------------------
;                                           |
; Delay system running for a while          |
;                                           |
;--------------------------------------------

DELAY 	PROC
    	PUSH CX
    	MOV CX,DelayShort
D1: 	LOOP D1
    	POP CX
    	RET
DELAY 	ENDP


;-----------------------------------------------------------
;	定义堆栈段                                             |
;-----------------------------------------------------------
		.stack 100h				; 定义256字节容量的堆栈


		END						;指示汇编程序结束编译
