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

void SPI_Ss(int ss){
	if(ss == 1){
		// Select
		PORTB &= ~(1 << PB4); // Set SS low
	}
	if(ss == 0){
		// De-select
		PORTB |= (1 << PB4); // Set SS high
	} 
}

void SPI_Transmit(unsigned char data){
	/* Start transmission */
	SPDR = data;
	
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF))){};
}

unsigned char SPI_Receive(){
	/* Start transmission */
	SPDR = 0; // need to add a dummy byte to start the transmission
	
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF))){};
		
	/* Return data register */
	return SPDR;
}

// ****************************************************