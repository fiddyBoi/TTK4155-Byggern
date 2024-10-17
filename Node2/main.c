//#define F_CPU 84000000UL
#define F_CPU 4000000UL // somehow worked with this but idk
#define BAUD 9600UL

#include <stdio.h>
#include <stdlib.h>
#include <sam.h>
#include <sam3x8e.h>
#include "time.h"
#include "uart.h"
// Test functions - prototypes
// **************************************************
void IO_test();
// **************************************************

int main(void)
{
	// Init drivers
	uart_init(F_CPU, BAUD);

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
		printf("up \n");
		PIOB->PIO_SODR = PIO_SODR_P13;
		time_spinFor(msecs(100));
		printf("down \n");
		PIOB->PIO_CODR = PIO_SODR_P13;
		time_spinFor(msecs(100));
	}

}
 // **************************************************