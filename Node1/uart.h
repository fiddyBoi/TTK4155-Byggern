#ifndef uart_H
#define uart_H

// Includes 
// ****************************************************
// ****************************************************

// Constants 
// ****************************************************
// ****************************************************

// Types 
// ****************************************************
// ****************************************************

// Global variables 
// ****************************************************
// ****************************************************

// Function prototypes 
// ****************************************************

// Initializes the UART driver and links printf to the driver
void UART_Init(unsigned int ubrr);

// Blocking transmit of one char over UART
void UART_Transmit(unsigned char data);

// BLocking receive of one char over UART
unsigned char UART_Receive();

// ****************************************************

#endif