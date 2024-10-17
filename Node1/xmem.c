#include "xmem.h"

// Includes
// ****************************************************
#include <avr/io.h>
#include <stdint.h>
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

void XMEM_Init(){
	// Enable external memory
	MCUCR |= (1 << SRE ); // enable XMEM
	SFIOR |= (1 << XMM2 ); // mask bits / reduce bus width
}

void XMEM_Write(uint8_t data, uint16_t addr){
	volatile char * ext_mem = ( char *) SRAM_BASE_ADDRESS ;
	ext_mem [ addr ]= data ;
}

uint8_t XMEM_Read(uint16_t addr){
	volatile char * ext_mem = ( char *) SRAM_BASE_ADDRESS ;
	uint8_t ret_val = ext_mem [ addr ];
	return ret_val ;
}
// ****************************************************