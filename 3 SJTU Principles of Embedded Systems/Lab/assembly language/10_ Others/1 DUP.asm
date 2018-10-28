VAR1  DB  10, 2 ; 2byte
VAR2  DW  5 DUP(?), 0 ; 12bytes
VAR3  DB  'HOW ARE YOU?', '$' ;13bytes
VAR4  DD  -1, 1, 0  ;12bytes

; 存储器内容
; 0A 02 
; 00 00 00 00 00 00 00 00 00 00 00 00 
; 48 4F 57 20 41 52 45 20 59 4F 55 3F 24 
; FF FF FF FF 01 00 00 00 00 00 00 00
;
