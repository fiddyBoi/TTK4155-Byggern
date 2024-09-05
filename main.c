/*
 * GccApplication1.c
 *
 * Created: 05.09.2024 09:29:02
 * Author : fredrbb
 */ 

#define F_CPU 4915200

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main(void)
{
//     /* Replace with your application code */
// 	UART_Init();
//     while (1) 
//     {
// 		unsigned char echo = UART_Receive();
// 		UART_Transmit(echo);
//     }

int i = 0; 
DDRA = 0x1; // set PA0 to output
while(1){
	if(i == 0){
		PORTA = 0x0; // set PA0 low
		i = 1; 
	}else{
		PORTA = 0x1; // set PA0 high
		i = 0; 
	}
	_delay_ms(1000);
}

}

 