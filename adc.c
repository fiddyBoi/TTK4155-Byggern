#include "adc.h"

// Includes
// ****************************************************
#include <avr/io.h>
#include <stdio.h>
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

void ADC_Init(){
	// Start 5 MHz PWM signal for ADC's external clock (PD4)
	TCCR0 = (1 << WGM01) | (1 << WGM00) | (1 << CS02) | (1 << CS01);
	OCR0 = 127; // 50% duty cycle
	DDRD |= (1 << PD4);
	// Do some config on the ADC?
}

uint8_t ADC_Read(uint8_t channel){
	volatile char * adc_mem = ( char *) BASE_ADDRESS ;
	volatile adc_mem[channel] = 1; // not sure about this...
	// busy wait (for BUSY signal)
	// OR calculate convertion time (see datasheet) and wait that amout
	uint8_t value = adc_mem[channel];
	return value; 
}

// ****************************************************