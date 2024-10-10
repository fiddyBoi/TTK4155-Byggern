#ifndef spi_H
#define spi_H

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

// Initializes and enables the SPI driver in mode 0:
// Sample (Rising), Setup (Falling)
// fclock / 16
void SPI_Init();

// Blocking transmit of one char over SPI
void SPI_Transmit(unsigned char data);

// Blocking receive of one char over SPI
unsigned char SPI_Receive();

// ****************************************************

#endif