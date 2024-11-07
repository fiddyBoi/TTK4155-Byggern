#include "adc.h"

// Includes
// ****************************************************
#include "sam.h"
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
	// Uses PA2 (A7 on shield), channel 0
	
	// ADC mode: freerun (never wait for any trigger), 12-bit resolution
	ADC->ADC_MR = ADC_MR_FREERUN | ADC_MR_PRESCAL(0);
	// Enable ADC
	ADC->ADC_CHER = ADC_CHER_CH0;
	// Enable clock for ADC
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | PMC_PCR_PID(ID_ADC);
	PMC->PMC_PCER1 |= 1<<(ID_ADC - 32);
	// Begin Conversion 
	ADC->ADC_CR = ADC_CR_START;
}

uint16_t ADC_Read(){
	return ADC->ADC_CDR[0];
}

// ****************************************************