#include "uart.h"

// Includes
// ****************************************************
#include <stdio.h>
#include <avr/io.h>
// ****************************************************

// Private macros and constants 
// ****************************************************
// ****************************************************

// Private types 
// ****************************************************
// ****************************************************

// Private global variables 
// ****************************************************
// ****************************************************

// Private functions 
// ****************************************************
// ****************************************************

// Implementation of the public functions
// ****************************************************

void UART_Init(unsigned int ubrr){
	/* Set baud rate */
	UBRR0H = (unsigned char)((ubrr)>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}

void UART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char UART_Receive()
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}

// ****************************************************