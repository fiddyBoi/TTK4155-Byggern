#ifndef uart_H
#define uart_H

// Includes 
// ****************************************************
// ****************************************************

// Constants 
// ****************************************************
#define F_CPU 4915200
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
// ****************************************************

// Types 
// ****************************************************
// ****************************************************

// Global variables 
// ****************************************************
// ****************************************************

// Function prototypes 
// ****************************************************

// Initializes the UART driver
void UART_Init(unsigned int ubrr);
void UART_Transmit(unsigned char data);
unsigned char UART_Receive();
// ****************************************************

#endif