;-----------------------------------------------------------
;Created by JY_ZH on 2018_4_7
;-----------------------------------------------------------
		.MODEL	SMalL			; 设定8086汇编程序使用Small model
		.8086				; 设定采用8086汇编指令集
;-----------------------------------------------------------
;	端口常量符号定义，由于I/O端口号不会进行改变，所以用equ而不是db来进行定义
;-----------------------------------------------------------
;
Portin	equ	80h	;定义输入端口号
Portout	equ	88h	;定义输出端口号
;-----------------------------------------------------------
;	定义堆栈段                                             |
;-----------------------------------------------------------
		.stack 100h				; 定义256字节容量的堆栈
;-----------------------------------------------------------
;	Definition of Code Segment                                             |
;-----------------------------------------------------------
		.code						; Code segment definition
		.startup					; 定义汇编程序执行入口点
;--------------------------------------------

;	State0      全是红灯
mov al, 36H
out Portout, al
call Delaylong

Again:

;	State1      南北绿灯,东西红，delay long  
mov al, 33H
out Portout, al	; 向输出端口Portout输出33H
call Delaylong;

;	State2      东西红,南北绿灯闪转黄灯
mov cx, 5H
s1:   mov al, 33H ; 
      out Portout, al
      call Delayshort
      mov al, 31H ; 
      out Portout, al
      call Delayshort
      loop s1

;	State3    南北红灯，东西绿灯
mov al, 1EH
out Portout, al
call Delaylong


;	State4     南北红灯闪转黄灯，东西绿灯
mov cx, 5H
s2:    mov al, 1EH	
       out Portout, al
       call Delayshort
       mov al, 0EH	
       out Portout, al
       call Delayshort
       loop s2;



; 函数循环重复进行交通灯变化
jmp Again


;三个不同时间的delay函数用来确定实现红绿灯，闪烁，黄灯的停留
;--------------------------------------------
;                                           |
; long delay for (red & green) light              |
;                                           |
;--------------------------------------------

Delaylong PROC ; 子程序
    	push cx
    	mov cx, DelayL	;
D0: 	nop
	    nop
    	nop
    	nop
	loop D0
    	pop cx
    	ret
Delaylong ENDP

;--------------------------------------------
;                                           |
; short delay for blingbling of light       |
;                                           |
;--------------------------------------------

Delayshort 	PROC
    	push cx
    	mov cx, DelayS
D1: 	loop D1
    	pop cx
    	ret
Delayshort ENDP


;-----------------------------------------------------------
;	定义数据段                                             |
;-----------------------------------------------------------
		.data					; 定义数据段
DelayS		dw	1FFFH			; 短延时参量	
DelayL		dw	0FFFFH			; 长延时参量


END;指示汇编程序结束编译
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	
