#include "encoder.h"

// Includes
// ****************************************************
#include "sam.h"
// ****************************************************

// Private macros and constants
// ****************************************************
#define ENCODER_MAX (int32_t)5610
#define ENCODER_HALF (int32_t)ENCODER_MAX/2
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
	// encoder pins: PC25 D4, PC26 D5 (PA29)
		
	// Enable clock for PIOC
	PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | PMC_PCR_PID(ID_PIOC);
	PMC->PMC_PCER0 |= (1 << ID_PIOC);
	
	// Enable clock for TC2 
	PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | PMC_PCR_PID(ID_TC2);
	// PMC->PMC_PCER0 |= (1 << ID_TC2);
	PMC->PMC_PCER1 |= (1 << 1); // Mistake in datasheet??? TC2 is PID 29 and should use PCER0
	
	// Select I/O to TC2 (peripheral B)
	PIOC->PIO_ABSR |= PIO_ABSR_P25 | PIO_ABSR_P26;
	PIOC->PIO_PDR |= PIO_PDR_P25 | PIO_PDR_P26; 
	
	// disable/enable clock for channel 0 during setup
	TC2->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKDIS; 
	
	// Set block mode register for TC2
	TC2->TC_BMR = TC_BMR_QDEN | TC_BMR_POSEN | TC_BMR_EDGPHA;
	
	// Set XC0 as the selected clock channel for channel 0
	TC2->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_XC0; 
	
	// disable/enable clock for channel 0 during setup
	// SWTRG resets the counter and starts the clock
	TC2->TC_CHANNEL[0].TC_CCR |=  TC_CCR_CLKEN | TC_CCR_SWTRG; 
}

uint32_t ENCODER_Read(){
	return TC2->TC_CHANNEL[0].TC_CV;
}

int ENCODER_Scale(uint32_t encoder_value){
	// -ENCODER_MAX/2 -> -100,  ENCODER_MAX/2 -> 100
	int32_t data = (int32_t) encoder_value;
	return 100*data/(ENCODER_HALF);
}

// ****************************************************