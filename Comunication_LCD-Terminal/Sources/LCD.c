/*
 * LCD_Init.c
 *
 *  Created on: Nov 19, 2013
 *      Author: ANTONIO
 */
#include "derivative.h"
#include "LCD.h"


void vfnLCD_Init(void)
{
	// turn on clocks
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK;
	
	//LCD pins
	PORTB_PCR0= PORT_PCR_MUX(1);
	PORTB_PCR1= PORT_PCR_MUX(1);
	PORTB_PCR2= PORT_PCR_MUX(1);
	PORTC_PCR0= PORT_PCR_MUX(1);
	PORTC_PCR1= PORT_PCR_MUX(1);
	PORTC_PCR2= PORT_PCR_MUX(1);      //configure as GPIO
	PORTC_PCR3= PORT_PCR_MUX(1);
	PORTC_PCR4= PORT_PCR_MUX(1);
	PORTC_PCR5= PORT_PCR_MUX(1);
	PORTC_PCR6= PORT_PCR_MUX(1);
	PORTC_PCR7= PORT_PCR_MUX(1);
	
	GPIOB_PDDR=GPIOB_EN_MASK | GPIOB_RS_MASK | GPIOB_RW_MASK; //set LCD enable,RS and RW as outputs
	GPIOC_PDDR=GPIOD_DATA_MASK; //set LCD data pins as outputs
	
	vfnLCD_Write(INS,CLEAR); //clear screen
	vfnLCD_Write(INS,0x0E);//turn on screen
	vfnLCD_Write(INS,SECOND_LINE_EN);//enable second line
	
	vfnLCD_Write(INS,UP);
}
/*****************************************************************/

void vfnSet_RS(void)
{
	GPIOB_PSOR=GPIOB_RS_MASK; //Set RS pin 
}

/*****************************************************************/

void vfnClear_RS(void)
{
	GPIOB_PCOR=GPIOB_RS_MASK; //Clear RS pin
}

/*****************************************************************/

void vfnEnable(void)
{
	short hwDelay=WAIT_TIME;
	
	GPIOB_PSOR=GPIOB_EN_MASK;  //set enable
	while(hwDelay--);  //wait time
	GPIOB_PCOR=GPIOB_EN_MASK; //clear enable
}

/*****************************************************************/

void vfnLCD_Write(char bINS, char bData)
{
	if(bINS) //if INS
	{
		vfnClear_RS();  //turn off RS to write INS
		GPIOC_PDOR=bData;//load data in output
		vfnEnable();    
		vfnSet_RS(); //turn on RS to write char
	}
	else //if char
	{
		GPIOC_PDOR=bData; //load data in output
		vfnEnable();
	}
}

/****************************************************************/

void vfnLCD_Write_Array(char bcounter,char * pbArray)
{
	while(bcounter--)//set number of writes
	{
		vfnLCD_Write(CHAR,* pbArray);//write char
		pbArray++; //increase pointer
	}
}
