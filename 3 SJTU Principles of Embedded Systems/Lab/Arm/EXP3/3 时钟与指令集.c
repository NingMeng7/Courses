#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "hw_memmap.h"
#include "debug.h"
#include "gpio.h"
#include "hw_i2c.h"
#include "hw_types.h"
#include "i2c.h"
#include "pin_map.h"
#include "sysctl.h"
#include "systick.h"
#include "interrupt.h"
#include "uart.h"
#include "hw_ints.h"
#include <string.h>

#define SYSTICK_FREQUENCY		1000			//1000hz

#define	I2C_FLASHTIME				500				//500mS
#define GPIO_FLASHTIME			300				//300mS
//*****************************************************************************
//
//I2C GPIO chip address and resigster define
//
//*****************************************************************************
#define TCA6424_I2CADDR 					0x22
#define PCA9557_I2CADDR						0x18

#define PCA9557_INPUT							0x00
#define	PCA9557_OUTPUT						0x01
#define PCA9557_POLINVERT					0x02
#define PCA9557_CONFIG						0x03

#define TCA6424_CONFIG_PORT0			0x0c
#define TCA6424_CONFIG_PORT1			0x0d
#define TCA6424_CONFIG_PORT2			0x0e

#define TCA6424_INPUT_PORT0				0x00
#define TCA6424_INPUT_PORT1				0x01
#define TCA6424_INPUT_PORT2				0x02

#define TCA6424_OUTPUT_PORT0			0x04
#define TCA6424_OUTPUT_PORT1			0x05
#define TCA6424_OUTPUT_PORT2			0x06




void 		Delay(uint32_t value);
void 		S800_GPIO_Init(void);
uint8_t 	I2C0_WriteByte(uint8_t DevAddr, uint8_t RegAddr, uint8_t WriteData);
uint8_t 	I2C0_ReadByte(uint8_t DevAddr, uint8_t RegAddr);
void		S800_I2C0_Init(void);
void 		S800_UART_Init(void);
void 		UARTStringPut(uint8_t *cMessage);
void 		UARTStringGet(uint32_t ui32Base,char *cMessage,const char Iden);

void SetTime(char * uart_receive_string);
void IncTime(char * uart_receive_string);
void GetTime(char * uart_receive_string);

//systick software counter define
volatile uint16_t systick_1s_couter,systick_200ms_couter; //1s?100ms???
volatile uint8_t	systick_1s_status,systick_200ms_status; //1s?100ms????

volatile uint8_t cnt,key_value,gpio_status;
volatile uint8_t rightshift = 0x01;
uint32_t ui32SysClock;//,ui32IntPriorityGroup,ui32IntPriorityMask;
//uint32_t ui32IntPrioritySystick,ui32IntPriorityUart0;

//uint8_t seg7[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x58,0x5e,0x079,0x71,0x5c};
char uart_receive_string[100];
uint8_t seg7[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77};	
uint8_t led7[] = {0x03,0x06,0x0c,0x18,0x30,0x60,0xc0,0x81};
uint8_t bit7[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

const char * standard_command[3] = {"SET", "INC", "GET"};

uint32_t hour=10, min = 58, sec = 58;
bool press_sw1 = false, press_sw2 = false;

int main(void)
{
	
	volatile uint32_t now, cnt=0; //now?"??*100+?",cnt?????,?1000,100,10,1
	volatile uint8_t num; //num???????
	
	volatile uint16_t	i2c_flash_cnt,gpio_flash_cnt;
	ui32SysClock = SysCtlClockFreqSet((SYSCTL_OSC_INT | SYSCTL_USE_PLL |SYSCTL_CFG_VCO_480), 20000000);
	
  SysTickPeriodSet(ui32SysClock/SYSTICK_FREQUENCY);
	SysTickEnable();
	SysTickIntEnable();																		//Enable Systick interrupt
	  

	S800_GPIO_Init();
	S800_I2C0_Init();
	S800_UART_Init();
	
	IntEnable(INT_UART0);
	UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);	//Enable UART0 RX,TX interrupt
	IntMasterEnable();
	
	IntPriorityGroupingSet(3);														//Set all priority to pre-emtption priority
	IntPrioritySet(INT_UART0,0);													//Set INT_UART0 to highest priority
	IntPrioritySet(FAULT_SYSTICK,0xe0);									//Set INT_SYSTICK to lowest priority
	
	while (1)
	{
		//?????????
		I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT2,(uint8_t)(0));				//???? ??     //1<<num  ??num?

		if (cnt == 0) {
			now = hour * 10000 + min * 100 + sec;
			cnt = 100000;
			num = 0;
		}
	
		if (num != 2 && num != 5)
		{
			I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT1,seg7[now/cnt]);			//write port 1 				
			I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT2,bit7[num]);	//write port 2: No.num    //?????????  ????
			now %= cnt; cnt /= 10; num++;
		}
		else if(num == 5) {
			I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT1,0x40);								//write port 1: "-"				
			I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT2,bit7[num]);		//write port 5: No.3
			num++;
		}
		else  //???????"-"
		{
			I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT1,0x40);								//write port 1: "-"				
			I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_OUTPUT_PORT2,bit7[num]);		//write port 2: No.3
			num++;
		}

		//update time
		if (systick_1s_status) //1s???
		{
			systick_1s_status	= 0; //??1s????
			if (!press_sw1 && !press_sw2) ++sec;
		}

		if (systick_200ms_status) //200ms???,????sw1?sw2???
		{
			systick_200ms_status	= 0; //??200ms????
			if (press_sw1) ++sec;
			if (press_sw2) ++min;
		}
		
		if (GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0)	== 0)	{					//USR_SW1-PJ0 pressed
			press_sw1 = true;
		} else { 	//USR_SW1-PJ0 released
			if (press_sw1) ++sec; //????????
			press_sw1 = false;
		}
		if (GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_1)	== 0)	{					//USR_SW1-PJ0 pressed
			press_sw2 = true;
		} else { 	//USR_SW1-PJ1 released
			if (press_sw2) ++min; //????????
			press_sw2 = false;
		}
		
		if (sec >= 60) {
			++min; 
			sec = 0;
		}
		if (min >= 60) { 
			++hour;
			min = 0;
		}
		if (hour >= 24)
			hour = 0;
		SetTime(uart_receive_string);
		IncTime(uart_receive_string);
		GetTime(uart_receive_string);
	}
}

void Delay(uint32_t value)
{
	uint32_t ui32Loop;
	for(ui32Loop = 0; ui32Loop < value; ui32Loop++){};
}


void UARTStringPut(uint8_t *cMessage)
{
	while(*cMessage!='\0')
		UARTCharPut(UART0_BASE,*(cMessage++));
}

void UARTStringPutNonBlocking(const char *cMessage)
{
	while(*cMessage!='\0')
		UARTCharPutNonBlocking(UART0_BASE,*(cMessage++));
}

void UARTStringGet(uint32_t ui32Base,char *cMessage,const char Iden)	//Iden????????,?????
{
    while(1)
	{
	  *cMessage=UARTCharGet(ui32Base);
	  if(*cMessage!=Iden)
	  {
    	cMessage=cMessage+1;
	  }
  	  else
	  {
	   *cMessage='\0';
  	    break;
	  }		
	}	
}

void S800_UART_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);						//Enable PortA
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));			//Wait for the GPIO moduleA ready

	GPIOPinConfigure(GPIO_PA0_U0RX);												// Set GPIO A0 and A1 as UART pins.
  GPIOPinConfigure(GPIO_PA1_U0TX);    			

  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	// Configure the UART for 115,200, 8-N-1 operation.
  UARTConfigSetExpClk(UART0_BASE, ui32SysClock,115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
	UARTStringPut((uint8_t *)"\r\nHello, world!\r\n");
}
void S800_GPIO_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);						//Enable PortF
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));			//Wait for the GPIO moduleF ready
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);						//Enable PortJ	
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ));			//Wait for the GPIO moduleJ ready	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);						//Enable PortN	
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)){};			//Wait for the GPIO moduleN ready		
	
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);			//Set PF0 as Output pin
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);			//Set PN0 as Output pin
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);			//Set PN1 as Output pin	

	GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE,GPIO_PIN_0 | GPIO_PIN_1);//Set the PJ0,PJ1 as input pin
	GPIOPadConfigSet(GPIO_PORTJ_BASE,GPIO_PIN_0 | GPIO_PIN_1,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
}

void S800_I2C0_Init(void)
{
	
  SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinConfigure(GPIO_PB2_I2C0SCL);
  GPIOPinConfigure(GPIO_PB3_I2C0SDA);
  GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
  GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

	I2CMasterInitExpClk(I2C0_BASE,ui32SysClock, true);										//config I2C0 400k
	I2CMasterEnable(I2C0_BASE);	

	I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_CONFIG_PORT0,0x0ff);		//config port 0 as input
	I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_CONFIG_PORT1,0x0);			//config port 1 as output
	I2C0_WriteByte(TCA6424_I2CADDR,TCA6424_CONFIG_PORT2,0x0);			//config port 2 as output 

	I2C0_WriteByte(PCA9557_I2CADDR,PCA9557_CONFIG,0x00);					//config port as output
	I2C0_WriteByte(PCA9557_I2CADDR,PCA9557_OUTPUT,0x0ff);				//turn off the LED1-8
	
}


uint8_t I2C0_WriteByte(uint8_t DevAddr, uint8_t RegAddr, uint8_t WriteData)
{
	uint8_t rop;
	while(I2CMasterBusy(I2C0_BASE)){};
	I2CMasterSlaveAddrSet(I2C0_BASE, DevAddr, false);
	I2CMasterDataPut(I2C0_BASE, RegAddr);
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
	while(I2CMasterBusy(I2C0_BASE)){};
	rop = (uint8_t)I2CMasterErr(I2C0_BASE);

	I2CMasterDataPut(I2C0_BASE, WriteData);
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
	while(I2CMasterBusy(I2C0_BASE)){};

	rop = (uint8_t)I2CMasterErr(I2C0_BASE);
	return rop;
}

uint8_t I2C0_ReadByte(uint8_t DevAddr, uint8_t RegAddr)
{
	uint8_t value;
	while(I2CMasterBusy(I2C0_BASE)){};	
	I2CMasterSlaveAddrSet(I2C0_BASE, DevAddr, false);
	I2CMasterDataPut(I2C0_BASE, RegAddr);
//	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);		
	I2CMasterControl(I2C0_BASE,I2C_MASTER_CMD_SINGLE_SEND);
	while(I2CMasterBusBusy(I2C0_BASE));
	I2CMasterErr(I2C0_BASE);
	Delay(1);
	//receive data
	I2CMasterSlaveAddrSet(I2C0_BASE, DevAddr, true);
	I2CMasterControl(I2C0_BASE,I2C_MASTER_CMD_SINGLE_RECEIVE);
	while(I2CMasterBusBusy(I2C0_BASE));
	value=I2CMasterDataGet(I2C0_BASE);
		Delay(1);
	return value;
}

/*
	Corresponding to the startup_TM4C129.s vector table systick interrupt program name
*/
void SysTick_Handler(void)
{
	if (systick_200ms_couter == 0)
	{
		systick_200ms_couter = SYSTICK_FREQUENCY/5;
		systick_200ms_status = 1;
	}
	else
		systick_200ms_couter--;
	
	if (systick_1s_couter	== 0)
	{
		systick_1s_couter	 = SYSTICK_FREQUENCY;
		systick_1s_status  = 1;
	}
	else
		systick_1s_couter--;	
	
}

/*
	Corresponding to the startup_TM4C129.s vector table UART0_Handler interrupt program name
*/
void UART0_Handler(void)
{
  int32_t uart0_int_status;
  uart0_int_status 		= UARTIntStatus(UART0_BASE, true);		// Get the interrrupt status.

  UARTIntClear(UART0_BASE, uart0_int_status);					//Clear the asserted interrupts
	
	while(UARTCharsAvail(UART0_BASE))
	{
	UARTStringGet(UART0_BASE,uart_receive_string,'@'); //???????????,?@?????,??????????????
  } 
}


void SetTime(char * uart_receive_string)
{
	int i;
	for(i=0;i<3;i++){
		if(uart_receive_string[i] != standard_command[0][i])
			return;
	}
	uart_receive_string[0]='O';
	hour = (uart_receive_string[3]-48)*10 + (uart_receive_string[4]-48);
	min = (uart_receive_string[6]-48)*10 + (uart_receive_string[7]-48);
	sec = (uart_receive_string[9]-48)*10 + (uart_receive_string[10]-48);
}


void IncTime(char * uart_receive_string)
{
	int i;
	for(i=0;i<3;i++){
		if(uart_receive_string[i] != standard_command[1][i])
			return;
	}
	uart_receive_string[0]='O';
	hour += (uart_receive_string[3]-48)*10 + (uart_receive_string[4]-48);
	min += (uart_receive_string[6]-48)*10 + (uart_receive_string[7]-48);
	sec += (uart_receive_string[9]-48)*10 + (uart_receive_string[10]-48);
}

void GetTime(char * uart_receive_string)
{
	int i;
	for(i=0;i<3;i++){
		if(uart_receive_string[i] != standard_command[2][i])
			return;
	}
	uart_receive_string[0]='O';
}
