#include "spi.h"

// Includes
// ****************************************************
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

void SPI_Init(){
	DDRB |= (1 << PB5) | (1 << PB7) | (1 << PB4); // MOSI, SCK and SS output
	DDRB &= ~(1 << PB6); // MISO input
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_Transmit(unsigned char data){
	/* Start transmission */
	PORTB &= ~(1 << PB4); // Set SS low
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF))){};
	PORTB |= (1 << PB4); // Set SS high
}

unsigned char SPI_Receive(){
	/* Start transmission */
	PORTB &= ~(1 << PB4); // Set SS low
	SPDR = 0; // need to add a dummy byte to start the transmission
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF))){};
	PORTB |= (1 << PB4); // Set SS high
	/* Return data register */
	return SPDR;
}

// ****************************************************