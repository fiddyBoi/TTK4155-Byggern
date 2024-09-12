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

// Test functions
// **************************************************
// ATmega162
// Outputs a square wave of period 2s on PA0
void IO_test(){
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

// ATmega162
// Listens to a byte sent over UART and echo's it back
void UART_test(){
	UART_Init(MYUBRR);
	while (1)
	{
		unsigned char echo = UART_Receive();
		_delay_ms(500);
		UART_Transmit(echo);
	}
}

// **************************************************

int main(void)
{
	UART_test();
}


 