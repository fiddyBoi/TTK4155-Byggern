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
#include "servo.h"
#include "adc.h"
#include "score.h"
#include "encoder.h"
#include "motor.h"
#include "controller.h"
#include "solenoid.h"
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

// test SERVO/PWM 
void SERVO_test();

// SERVO/PWM test with Joystick
void SERVO_testWithJoystick();

// Reads the the ADC module output of the IR data
void ADC_testRead();

// Tests the score
void SCORE_test();

// Test encoder
void ENCODER_test();

// Test motor with joystick
void MOTOR_testWithJoystick();

// Test Controller
void CONTROLLER_test();

// Solenoid test
void SOLENOID_test();

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
	SERVO_Init();
	ADC_Init();
	SCORE_Init();
	ENCODER_Init();
	MOTOR_Init();
	//CONTROLLER_Init(1,1);
	SOLENOID_Init();
	
	// test shit
	printf("Start program:\n");
	SOLENOID_test();
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

void SERVO_test(){
	while(1){
		//normal 
		SERVO_Output(-100);
		printf("0.9 \n");
		time_spinFor(msecs(2000));
		SERVO_Output(100);
		printf("2.1 \n");
		time_spinFor(msecs(2000));
		SERVO_Output(0);
		printf("something \n");
		time_spinFor(msecs(2000));
		// fucked
		SERVO_Output(200);
		printf("fucked 2.1 \n");
		time_spinFor(msecs(2000));
		SERVO_Output(-200);
		printf("fucked 0.9 \n");
		time_spinFor(msecs(2000));
	}
}

void SERVO_testWithJoystick(){
		CanMsg r_message;
		while(1){
			//time_spinFor(msecs(200));
			if(CAN_Rx(&r_message)){
				can_printmsg(r_message);
				JoystickPosition pos = toJoyPos(r_message);
				printf("Joystick position x:%d y:%d \n", pos.x, pos.y);
				SERVO_Output(pos.x);
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

void ENCODER_test(){
	while(1){
		time_spinFor(msecs(200));
		uint32_t data = ENCODER_Read();
		int data_scaled = ENCODER_Scale(data);
		printf("ENCODER: %d\n",data);
		printf("ENCODER SCALED: %d\n", data_scaled);
	}
}

void MOTOR_testWithJoystick(){
	CanMsg r_message;
	while(1){
		//time_spinFor(msecs(200));
		if(CAN_Rx(&r_message)){
			//can_printmsg(r_message);
			JoystickPosition pos = toJoyPos(r_message);
			printf("Joystick position x:%d y:%d \n", pos.x, pos.y);
			MOTOR_Output(pos.x);
			SERVO_Output(pos.y);
			}else{
			//printf("No message \n");
		}
	}
}

void CONTROLLER_test(){
	CanMsg r_message;
	while(1){
		if(CAN_Rx(&r_message)){
			//can_printmsg(r_message);
			JoystickPosition pos = toJoyPos(r_message);
			printf("Joystick position x:%d y:%d \n", pos.x, pos.y);
			CONTROLLER_SetReference(pos.x);
			SERVO_Output(pos.y);
			}else{
			//printf("No message \n");
		}
	}
}

void SOLENOID_test(){
	while(1){
		time_spinFor(msecs(1000));
		SOLENOID_Hit();
	}
}
 // **************************************************