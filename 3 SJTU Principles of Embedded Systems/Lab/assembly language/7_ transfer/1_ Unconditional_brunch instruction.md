## 控制转移指令
转移是一种将程序控制从一处改到另一处的最直接的方法(一般而言指令是顺序执行的)，在CPU内部，通过将目的地址传送给IP来实现。转移指令包括无条件转移指令与条件转移指令。

## 无条件转移指令
无条件转移指令无条件地将程序转移到指令中指定地目标地址，对状态标志位没有影响。

> 1. 段内直接转移

JMP NearLabel   ; IP<-(IP)+disp(16位)

    JMP NEXT
    AND AL, 7FH
    NEXT: XOR AL, 7FH
    ;AND AL, 7FH 语句将会被跳过
    
> 2. 段内直接短转移

JMP ShortLabel  ; IP<-(IP)+disp(8位)

    Before: ....;
    JMP Before  ;  向前可以不加short
    
    JMP SHORT after
    ...
    after:

> 3. 段内间接转移

    JMP BX
    JMP WORD PTR[BX+DI]
    
> 4. 段间直接转移

指令操作数为一个远标号,其在另一个代码段中

    JMP FAR PTR NEXT
    JMP 8000H:0012H

> 5. 段间间接转移

    JMP DWORD PTR[BP][DI]   ; 前两个字节送IP，后两个送CS
    JMP VAR ;   DD 的一个数据
    
    
    
    
    
