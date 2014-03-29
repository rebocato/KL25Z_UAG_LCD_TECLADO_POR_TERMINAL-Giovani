/*
 * UART.h
 *
 *  Created on: Mar 12, 2014
 *      Author: ANTONIO
 */

#ifndef UART_H_
#define UART_H_

void vfnUART_Config(void);
void vfnUART_Send(char bData);
void vfnUART_Send_String(char *pbArray);
void vfnLCD_UART(void);

#endif /* UART_H_ */
