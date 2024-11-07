#include "encoder.h"

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

void ENCODER_Init(){
	
	// ENCODER
	// encoder pins: PC25, PA29
	// Enable encoder pins and configure as input
	PIOC->PIO_PER |= PIO_PER_P25;
	PIOC->PIO_ODR |= PIO_PER_P25;
	PIOA->PIO_PER |= PIO_PER_P29;
	PIOA->PIO_ODR |= PIO_PER_P29;
	// Enable clock for PIOA and PIOC
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | PMC_PCR_PID(ID_PIOA);
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | PMC_PCR_PID(ID_PIOC);
	PMC->PMC_PCER0 |= (1 << ID_PIOA);
	PMC->PMC_PCER0 |= (1 << ID_PIOC);
}

// ****************************************************