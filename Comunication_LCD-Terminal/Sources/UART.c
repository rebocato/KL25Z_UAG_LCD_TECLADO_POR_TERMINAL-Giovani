/*
 * UART.c
 *
 *  Created on: Mar 12, 2014
 *      Author: ANTONIO
 */

#include "derivative.h"
#include "UART.h"
#include "LCD.h"

char gbUART;
char gbWrite;
char gbCount;

void vfnUART_Config(void)
{
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
		
	UART0_BDL = UART0_BDL_SBR(137);
	UART0_C2 = UART0_C2_RE_MASK | UART0_C2_RIE_MASK;
	
	PORTA_PCR1= PORT_PCR_MUX(2) | PORT_PCR_PE_MASK; 
	PORTA_PCR2= PORT_PCR_MUX(2) | PORT_PCR_PE_MASK;
	
	NVIC_ISER = 1<<12;
}

void vfnUART_Send(char bData)
{
   	while(!(UART0_S1&UART_S1_TDRE_MASK));
   	UART0_D = bData;
}

void vfnUART_Send_String(char *pbArray)
{
	while(*pbArray != '\0')
	{
		vfnUART_Send(*pbArray);
		pbArray++;	
	}
}

void vfnLCD_UART(void)
{
	if(gbWrite)
	{
		if(gbUART == 0x08)
		{
			if(gbCount)
			{
				gbCount--;
				if(gbCount==15)
				{
					vfnLCD_Write(INS,UP+15);
					vfnLCD_Write(CHAR,' ');
					vfnLCD_Write(INS,BACKSPACE);
				}
				else
				{
					vfnLCD_Write(INS,BACKSPACE);
					vfnLCD_Write(CHAR,' ');
					vfnLCD_Write(INS,BACKSPACE);
				}
			}
		}
		else if(gbUART == 0xD)
		{
			vfnLCD_Write(INS,DOWN);
			gbCount = 16;
		}
		else
		{
			if(gbCount<32)
			{
				gbCount++;
				vfnLCD_Write(CHAR,gbUART);
				if(gbCount == 16)
				{
					vfnLCD_Write(INS,DOWN);
				}
			}
			
		}
		gbWrite = 0;
	}
}

void UART0_IRQHandler(void)
{
	gbUART = UART0_D;
	gbWrite = 1;
}
