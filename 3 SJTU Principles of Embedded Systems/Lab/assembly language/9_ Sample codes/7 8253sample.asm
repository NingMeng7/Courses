COMMENT 1
一个包装箱可以装24瓶，装满一箱后，流水线停2s，然后继续装箱，用8253控制，CLK1位1KZ,地址位060H~063H
包装箱控制是一个负脉冲发生器：方式2， 定时器2s是一个单一负脉冲：方式1
通道0: 00 01 010 0
通道1：01 11 001 0
通道0的上升沿触发单稳态通道1的定时，通道1的低电平OUT1使得GATE0暂停。
1

MOV AL, 14H
OUT 63H, AL
MOV AL, 18H
OUT 60H, AL

MOV AL, 72H
OUT 63, AL
MOV AL, 2000
OUT 61, AL
MOV AL, AH
OUT 61, AL
