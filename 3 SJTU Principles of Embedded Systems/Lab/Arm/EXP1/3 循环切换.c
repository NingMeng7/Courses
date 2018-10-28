#include <stdint.h>
#include <stdbool.h>
#include "hw_memmap.h"
#include "debug.h"
#include "gpio.h"
#include "hw_types.h"
#include "pin_map.h"
#include "sysctl.h"


#define   FASTFLASHTIME			(uint32_t) 500000
#define   SLOWFLASHTIME			(uint32_t) 4000000

uint32_t delay_time,oldkey_value,newkey_value,time;


void 		Delay(uint32_t value);
void 		S800_GPIO_Init(void);
void Twinkle0(void);
void Twinkle1(void);


int main(void)
{
	uint32_t loop = 0;
	time = SysCtlClockFreqSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_25MHZ | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_320, 20000000);	
	S800_GPIO_Init();
	oldkey_value = newkey_value = 1;
	
	while(1) {
		newkey_value = GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0);	//read the PJ0 key value
		
		if(oldkey_value == 0) {	// 之前按下，现在没按下，捕捉上升沿
			if(newkey_value)
				loop = (loop+1) % 4;
		}
		
		oldkey_value = newkey_value;
		
		switch(loop){
			case 0:	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0, 0x0);
				GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1, 0x0);
				break;
			case 1: Twinkle0();
				break;
			case 2: GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0, 0x0);
				GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1, 0x0);
				break;
			case 3: Twinkle1();
				break;
			default:;
		}
	}		
	return 0;
}


void Twinkle0(void)
{
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_PIN_0);
	Delay(FASTFLASHTIME);
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,0x0);
	Delay(FASTFLASHTIME);
}

void Twinkle1(void)
{
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,GPIO_PIN_1);
	Delay(FASTFLASHTIME);
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0x0);
	Delay(FASTFLASHTIME);
}


void Delay(uint32_t value)
{
	uint32_t ui32Loop;
	for(ui32Loop = 0; ui32Loop < value; ui32Loop++){};
}


void S800_GPIO_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);			//Enable PortF
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));		//Wait for the GPIO moduleF ready	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);			//Enable PortJ	
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ));		//Wait for the GPIO moduleJ ready	
	
  	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_3);	//Set PF0 as Output pin
	
	GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE,GPIO_PIN_0 | GPIO_PIN_1);	//Set the PJ0,PJ1 as input pin
	
	GPIOPadConfigSet(GPIO_PORTJ_BASE,GPIO_PIN_0 | GPIO_PIN_1,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
	
}

