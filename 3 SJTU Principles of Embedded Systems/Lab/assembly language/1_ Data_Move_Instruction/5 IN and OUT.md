> 1. 格式:

1. IN AX/AL, 端口地址(8位直接/DX间接)
2. OUT 端口地址(8位直接/DX间接), AX/AL

> 2. 操作数

1. 端口地址在0~255可以直接用立即数给出, 当端口地址是0~65536考虑用DX
2. 注意，寄存器只能用AL/AX, DX

> 3. Warning

不影响标志位

    MOV DX, 210H
    IN AL, DX
    NOT AL
    OUT 20H, AX
