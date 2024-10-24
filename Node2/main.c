#define F_CPU 84000000UL
//#define F_CPU 4000000UL // somehow worked with this but idk
#define BAUD 9600UL

#include <stdio.h>
#include <stdlib.h>
#include <sam.h>
#include <sam3x8e.h>
#include "time.h"
#include "uart.h"
#include "can.h"
// Test functions - prototypes
// **************************************************
//IO test for Node 2
void IO_test();

//Tries to receive a message from node 1
void CAN_receiveTest();


// **************************************************

int main(void)
{
	// Init drivers
	SystemInit();
	uart_init(F_CPU, BAUD);
	//Set to 16 TQ
	//BAUDRATE 250000
	//Propag = 2
	//Phase1 = 6
	//Phase2 = 7
	//BRP = 9.5 because of BRP = (250ns * F_CPU) - 1
	can_init((CanInit){.brp = 9, .phase1 = 6, .phase2 = 7, .propag = 2, .sjw = 4}, 0); 

	// Disable watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	// test shit
	//CAN_receiveTest();
	CAN_receiveTest();
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

void CAN_receiveTest() {
	while(1) {
		time_spinFor(msecs(1000));
		CanMsg r_message;
		if (can_rx(&r_message)) {
			can_printmsg(r_message);
		}
		else {
			printf("No message\n");
		}
	}
}



 // **************************************************