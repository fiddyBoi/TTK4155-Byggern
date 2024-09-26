#include "adc.h"

// Includes
// ****************************************************
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "ATmega162.h"
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
	// Set pin PD4 to output
	DDRD |= (1 << PD4);

	// Start 0.5-5 MHz PWM signal for ADC's external clock (16 bit fast mode)
	// Results in: 2.45 Mhz (But less significant digits changes a bit) 
	TCCR3A = (1 << WGM31) | (1 << WGM30) | (1 << COM3A0);
	TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS30);
	OCR3A = 0; // max duty cycle
}

uint8_t ADC_Read(uint8_t channel){
	volatile char * adc_mem = ( char *) ADC_BASE_ADDRESS ;
	int numberOfChannels = 4;
	uint8_t value;
	
	// write to create new sample
	*adc_mem = 0;

	// calculate convertion time (see datasheet) and wait that amount
		// int N = 4; // number of channels converted
		// int f_clk = 2450000; // 2.45 Mhz
		// int t_conv = (9 * N * 2)/f_clk;  
	_delay_ms(0.01618);
	
	for(int i=0; i<numberOfChannels; i++){
		uint8_t read = *adc_mem;
		if(i == channel){
			value = read;
		}
	}
	return value; 
}

// ****************************************************