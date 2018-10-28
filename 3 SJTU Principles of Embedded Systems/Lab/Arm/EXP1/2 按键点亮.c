#include <stdint.h>
#include <stdbool.h>
#include "hw_memmap.h"
#include "debug.h"
#include "gpio.h"
#include "hw_types.h"
#include "pin_map.h"
#include "sysctl.h"


uint32_t delay_time,key_value1,key_value2,time;

void 		Delay(uint32_t value);
void 		S800_GPIO_Init(void);
void Twinkle0(void);
void Twinkle1(void);


int main(void)
{
	time = SysCtlClockFreqSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_25MHZ | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_320, 20000000);	
	S800_GPIO_Init();
	
	while(1) {
		key_value1 = GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0);				//read the PJ0 key value
		key_value2 = GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_1);
		
		if (key_value1	== 0) 		//USR_SW1-PJ0 pressed
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);			// Turn on the LED.
		else
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
		
		if (key_value2 ==0)		//USR_SW2-PJ1 pressed
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);			// Turn on the LED.
		else
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);				// Turn off the LED.
	}
	return 0;
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


