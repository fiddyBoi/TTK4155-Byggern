#include <stdio.h>
#include <stdlib.h>
#include <sam.h>
#include <sam3x8e.h>
#include "time.h"
// Test functions - prototypes
// **************************************************
void IO_test();
// **************************************************

int main(void)
{
	// Init drivers
	
	// Disable watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	// test shit
	IO_test();
}

 // Test functions - implementation
 // **************************************************
void IO_test(){
	// Enable clock for PIOB
	PMC->PMC_PCER0 |= (1 << ID_PIOB);
	// Enable control of PB13 and set as output
	PIOB->PIO_PER = PIO_PER_P13;
	PIOB->PIO_OER = PIO_OER_P13;
	while(1){
		// Write
		PIOB->PIO_SODR = PIO_SODR_P13;
		time_spinFor(msecs(200));
		PIOB->PIO_CODR = PIO_SODR_P13;
		time_spinFor(msecs(200));
	}

}
 // **************************************************