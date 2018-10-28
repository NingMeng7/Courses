/*
Description: 这个函数是要实现一个虚拟指令集的功能，也就是说，上位机发送来一个事先约定好的命令，在单片机里根据命令做出对应的操作, 这里总共实现2条命
令，一条是查询班级号，一条是查询学号,  一开始的思路很简单，用一个数组接下整个字符串,并手动添加上C风格的结束符'\0' 然后调用 strcmp 和标准命令比较，
相同就执行,结果发现命令查询班级可以正常执行，查询学号就gg.

Debug Process: 我震惊了，这么相似的两个指令居然还能一个能跑一个不能跑的。
1. 我交换了两个判断的顺序, 结果不变
2. 我进行单步中断查看结果,发现正常运行！！！(我本该再跑一次,不使用单步中断跑起来的)
3. 我对不工作的指令逐步添加字符,发现指令字符数最多只能有8个，超过8个就gg
4. 我采取直接输出接到的字符串的方式，串口界面输出了我所传输过去的完整字符串，这使得我错误的认为数组接到了整个完整的字符串。
5. 我怀疑是strcmp的问题, 可能是在比较两个字符串的过程中别的异常事件对这个进行了打断(但是按照中断的执行过程，应该还会回到断点继续执行，我没有想明白)，
我自己实现了一个strcmp，然后发现还是8个字符串以上就gg, 考虑到我写的strcmp肯定不如库函数, 我再次怀疑是接收的过程出了问题。
6. 同学不开中断进入debug监测模式，发现确实只能接收到8个字符串，因此锁定了，是缓冲区设置的问题。
7. 第四步的结论是错的，由于串口输出是紧跟在上一次输出的后面，没有分隔符，所以所谓的完整字符串是分次输出的结果。

Solution: 
1. 设置两个标志位记录上一次的比较结果，将指令分成两部分，两次来完成比较
2. 用字符逐个处理
*/

// 解决方案2的程序
const char standar_str[2][20] = {"at+class", "at+student"};

//----------- UART ---------------------
void UARTStringPut(const char *cMessage)
{
	while(*cMessage!='\0')
		UARTCharPut(UART0_BASE,*(cMessage++));
}

void UARTStringPutNonBlocking(const char *cMessage)
{
	while(*cMessage!='\0')
		UARTCharPutNonBlocking(UART0_BASE,*(cMessage++));
}

/*
	Corresponding to the startup_TM4C129.s vector table UART0_Handler interrupt program name
*/
void UART0_Handler(void)
{
	int32_t uart0_int_status;
  	uint8_t k;
	char ch;
	uart0_int_status = UARTIntStatus(UART0_BASE, true);		// Get the interrrupt status.
  	UARTIntClear(UART0_BASE, uart0_int_status);			//Clear the asserted interrupts
	
	k = 0;
	type0 = 1;
	type1 = 1;
	while(UARTCharsAvail(UART0_BASE))    	// Loop while there are characters in the receive FIFO.
	{
		///Read the next character from the UART and write it back to the UART.
    		ch = tolower(UARTCharGetNonBlocking(UART0_BASE));
		if(ch != standar_str[0][k]){
			type0 = 0;
		}
		if(ch != standar_str[1][k]){
			type1 = 0;
	}
		GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1,GPIO_PIN_1);		
		k++;
	}
	
	if(type0 == 1){
		UARTStringPut(str1);
	}
	if(type1 == 1){
		UARTStringPut(str2);
	}
}


