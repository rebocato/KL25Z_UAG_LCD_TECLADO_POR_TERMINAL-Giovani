#include "derivative.h" /* include peripheral declarations */
#include "LCD.h"
#include "UART.h"


int main(void)
   {
	vfnUART_Config();
	vfnLCD_Init();
	for(;;) 
	{
		vfnLCD_UART();
	}
	
	return 0;
}
