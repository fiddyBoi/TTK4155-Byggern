#define F_CPU 84000000UL
#define BAUD 9600UL

#include <stdio.h>
#include <stdlib.h>
#include <sam.h>
#include <sam3x8e.h>
#include "time.h"
#include "uart.h"
#include "can.h"
#include "messages.h"
#include "pwm.h"
#include "adc.h"
#include "score.h"
// Test functions - prototypes
// **************************************************
//IO test for Node 2
void IO_test();

//Tries to receive a message from node 1
void CAN_receiveTest();

//Tries to send a can message
void CAN_transmitTest();

// Tries to receive joystick data
void MSG_Joystick();

// test PWM 
void PWM_test();

// PWM test with Joystick
void PWM_testWithJoystick();

// Reads the the ADC module output of the IR data
void ADC_testRead();

// Tests the score
void SCORE_test();

// **************************************************

int main(void)
{
	// Init drivers
	SystemInit();
	// Disable watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
		
	uart_init(F_CPU, BAUD);
	//Set to 16 TQ
	//BAUDRATE 250000
	//Propag = 2
	//Phase1 = 6
	//Phase2 = 7
	can_init((CanInit){.brp = 20, .phase1 = 6-1, .phase2 = 7-1, .propag = 2-1, .sjw = 4}, 0); 
	PWM_Init();
	ADC_Init();
	SCORE_Init();
	
	// test shit
	printf("Start program:\n");
	PWM_testWithJoystick();
	while(1){};
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
	CanMsg r_message;
	while(1){
		time_spinFor(msecs(200));
		if(CAN_Rx(&r_message)){
			can_printmsg(r_message);
		}else{
			printf("No message \n");
		}
	}	
}

void CAN_transmitTest(){
	CanMsg message = {
		.id = 5,
		.length = 2,
		.byte = {1,2}
	};
	while(1) {
		time_spinFor(msecs(200));
		CAN_Tx(message);
		printf("Message sent\n");
	}
}


void MSG_Joystick(){
	CanMsg r_message;
	while(1){
		time_spinFor(msecs(200));
		if(CAN_Rx(&r_message)){
			can_printmsg(r_message);
			JoystickPosition pos = toJoyPos(r_message);
			printf("Joystick position x:%d y:%d \n", pos.x, pos.y);
			}else{
			printf("No message \n");
		}
	}
}

void PWM_test(){
	while(1){
		//normal 
		PWM_Output(-100);
		printf("0.9 \n");
		time_spinFor(msecs(2000));
		PWM_Output(100);
		printf("2.1 \n");
		time_spinFor(msecs(2000));
		PWM_Output(0);
		printf("something \n");
		time_spinFor(msecs(2000));
		// fucked
		PWM_Output(200);
		printf("fucked 2.1 \n");
		time_spinFor(msecs(2000));
		PWM_Output(-200);
		printf("fucked 0.9 \n");
		time_spinFor(msecs(2000));
	}
}

void PWM_testWithJoystick(){
		CanMsg r_message;
		while(1){
			//time_spinFor(msecs(200));
			if(CAN_Rx(&r_message)){
				can_printmsg(r_message);
				JoystickPosition pos = toJoyPos(r_message);
				printf("Joystick position x:%d y:%d \n", pos.x, pos.y);
				PWM_Output(pos.x);
				}else{
				printf("No message \n");
			}
		}
}

void ADC_testRead(){
	while(1){
		uint16_t IRdata = ADC_Read();
		printf("IR data: %d\n",IRdata);
		time_spinFor(msecs(200));
	}
}

void SCORE_test(){
	while(1){
		SCORE_Poll();
		printf("SCORE: %d\n", SCORE_GetScore());
	}
}
 // **************************************************