; Sample Code 1
; Description: 8255A在系统中占用 88~8BH号端口地址, 现在要令PA、PB、PC口全部为输出, PA、PB口工作于方式0，并将PC6置位, PC3复位
; CW: 10000000 = 80H
; PC6置位: 00001101 = 0DH
; PC3复位: 00000110 = 06H
MOV	AL, 80H
OUT 8BH, AL
MOV AL, ODH
OUT 8BH, AL
MOV AL, 06H
OUT 8BH, AL




; Sample Code 2

