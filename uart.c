#include "uart.h"

// Includes
// ****************************************************
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

void UART_Init(){
	/* Set baud rate */
	UBRRH = (unsigned char)(UBRR>>8);
	UBRRL = (unsigned char)UBRR;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}

void USART_Transmit( unsigned int data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR = data;
}

unsigned char USART_Receive()
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR;
}

// ****************************************************