#include "solenoid.h"

// Includes
// ****************************************************
#include "sam.h"
#include "time.h"
// ****************************************************

// Private macros and constants
// ****************************************************
const uint64_t timeout_soleoid = 500; // min 500ms between hits
// ****************************************************

// Private types
// ****************************************************
// ****************************************************

// Private global variables
// ****************************************************
uint64_t timestamp;
uint64_t TIMEOUT; 
// ****************************************************

// Private functions
// ****************************************************
// ****************************************************

// Implementation of the public functions
// ****************************************************

void SOLENOID_Init(){
	// Will use PA16 (A0)
	
	// Enable clock for PIOA
	PMC->PMC_PCER0 |= (1 << ID_PIOA);
	// Enable control of PA16 and set as output
	PIOA->PIO_PER = PIO_PER_P16;
	PIOA->PIO_OER = PIO_OER_P16;
	PIOA->PIO_SODR = PIO_SODR_P16;
	// Set timeout
	TIMEOUT = msecs(timeout_soleoid);
	timestamp = time_now();
}

void SOLENOID_Hit(){
	if((time_now() - timestamp) > TIMEOUT){ // over 1 second since last time
		timestamp = time_now();
		PIOA->PIO_CODR = PIO_CODR_P16;
		time_spinFor(msecs(100));
		PIOA->PIO_SODR = PIO_SODR_P16;
	}
}

// ****************************************************