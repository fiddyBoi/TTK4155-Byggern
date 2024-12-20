/*
 * GccApplication1.c
 *
 * Created: 05.09.2024 09:29:02
 * Author : fredrbb
 */ 

#include "ATmega162.h" 
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "uart.h"
#include "xmem.h"
#include "adc.h"
#include "multifunctionBoard.h"
#include "oled.h"
#include "menu.h"
#include "spi.h"
#include "mcp2515.h"
#include "mcp2515_regs.h"
#include "can.h"
#include "messages.h"
#include "game.h"

// Test functions - prototypes
// **************************************************

// Outputs a square wave of period 2s on PB0 (ATmega162)
void IO_test();

// Listens to a byte sent over UART and echo's it back (ATmega162)
void UART_test();

// Test the linking of printf (ATmega162)
void PRINTF_test();

// Testing the SRAM by writing and retrieving to the SRAM
void SRAM_test();

// Testing ADC driver by reading and printing out values on a given channel
void ADC_test(uint8_t channelToTest);

// Testing the joystick
void JOY_test();

// Test joystick button
void JOY_testButton();

// Testing the slider
void SLIDE_test();

// Starts and tests the menu
void MENU_test();

// Tries to do an SPI transmit
void SPI_testTransmit();

// Tries to do an SPI receive
void SPI_testReceive();

// Tries to send an Reset command to the CAN controller 
void MCP2515_testReset();

// Tries to send and receive CAN in loopback mode
// NB: must have loopbackmode in init
void CAN_testLoopBack();

//Tries to send simple CAN message in Normal mode
// NB: must have Normal mode in init
void CAN_testNormalModeTx();

//Tries to receive a simple CAN message in Normal mode
// NB: must have Normal mode in init
void CAN_testNormalModeRx();

// Sends joystick data periodically to node 2
void MSG_Joystick();

// Sends applications messages
void MSG_test();

// STARTS THE GAME!!!!
void GAMELOOP();

// **************************************************

int main(void)
{
	// Init drivers
	UART_Init(MYUBRR);
	XMEM_Init();
	ADC_Init();
	JOY_Init();
	OLED_Init();
	SPI_Init();
	MCP2515_Init();
	CAN_Init();
	
	// test shit
	GAMELOOP();
}

 // Test functions - implementation
 // **************************************************
 
 void IO_test(){
	 int i = 0;
	 DDRB = 0x1; // set PB0 to output
	 while(1){
		 if(i == 0){
			 PORTB = 0x0; // set PB0 low
			 i = 1;
			 }else{
			 PORTB = 0x1; // set PB0 high
			 i = 0;
		 }
		 _delay_ms(1000);
	 }
 }

 void UART_test(){
	 UART_Init(MYUBRR);
	 while (1)
	 {
		 unsigned char echo = UART_Receive();
		 _delay_ms(500);
		 UART_Transmit(echo);
	 }
 }

 void PRINTF_test(){
	 UART_Init(MYUBRR);
	 printf("Testing linking of printf.");
 }

void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}

void ADC_test(uint8_t channelToTest){
	while(1){
		uint8_t valueRead = ADC_Read(channelToTest);
		printf("Value from ADC channel %d: %d \n", channelToTest, valueRead);
		_delay_ms(100);
	}
}

void JOY_test(){
	JOY_Calibrate();
	while(1){
		JoystickPosition pos = JOY_GetPosition();
		JoystickDirection dir = JOY_GetDirection();
		printf("Joystick position x:%d y:%d \n", pos.x, pos.y);
		printf("Joystick direction: %s \n", DIR_STRING[dir]);
		_delay_ms(500);
	}
}

void SLIDE_test(){
	while(1){
		SliderPositions pos = SLIDE_GetPositions();
		printf("Slider position left: %d right: %d \n", pos.left, pos.right);
		_delay_ms(500);
	}
}

void MENU_test(){
	OLED_Reset();
	Menu_Start();
	while(1){
		MENU_PollAndUpdate();
		_delay_ms(100);
	}
}

void JOY_testButton(){
	while(1){
		int button = JOY_GetButton();
		printf("Joystick button: %d \n", button);
		_delay_ms(100);
	}
}

void SPI_testTransmit(){
	while(1){
		unsigned char data = 0xAB;
		SPI_Ss(1);
		SPI_Transmit(data);
		SPI_Ss(0);
		_delay_ms(300);
	}
}

void SPI_testReceive(){
	while(1){
		SPI_Ss(1);
		unsigned char data = SPI_Receive();
		SPI_Ss(0);
		_delay_ms(100);
	}
}

void MCP2515_testReset(){
	while(1){
		MCP2515_Reset();
		_delay_ms(100);
	}
}

void CAN_testLoopBack(){
	CanMsg message = {
		.id = 5,
		.length = 2,
		.byte = {1,2}
	};
	_delay_ms(100);
	CAN_Tx(message);
	_delay_ms(100);
	while(1){
		_delay_ms(1000);
		if(CAN_Poll()){
			printf("CAN polled\n");
			CanMsg r_message;
			int status = CAN_Rx(&r_message);
			if(status){
				printf("id: %d\n",r_message.id);
				printf("length: %d\n", r_message.length);
				printf("data: %d , %d\n", r_message.byte[0], r_message.byte[1]);
			}else{
				printf("No message\n");
			}
		}
	}
}

void CAN_testNormalModeTx() {
	CanMsg message = {
		.id = 255,
		.length = 2,
		.byte = {1,2}
	};
	while(1) {
		_delay_ms(1000);
		CAN_Tx(message);
		printf("Message sent\n");
	}
}

void CAN_testNormalModeRx(){
	CanMsg message; 
	while(1){
		_delay_ms(50);
		if(CAN_Poll()){
			printf("CAN polled\n");
			int status = CAN_Rx(&message);
			if(status){
				printf("id: %d\n",message.id);
				printf("length: %d\n", message.length);
				printf("data: %d , %d\n", message.byte[0], message.byte[1]);
				}else{
				printf("No message\n");
			}
		}
	}
}

/*void MSG_Joystick(){
	JOY_Calibrate();
	while(1){
		//_delay_ms(100);
		JoystickPosition pos = JOY_GetPosition();
		printf("Joystick position x:%d y:%d \n", pos.x, pos.y);
		CanMsg msg = toCanMsg(pos);
		CAN_Tx(msg);
		printf("Message sent\n");
	}
}*/

void MSG_test(){
	JOY_Calibrate();
	while(1){
		//_delay_ms(100);
		JoystickPosition pos = JOY_GetPosition();
		int b = JOY_GetButton();
		ApplicationMsg m = {
			.x = pos.x,
			.y = pos.y,
			.button = b
		};
		printf("ApplicationMsg position x:%d y:%d b:%d\n", m.x, m.y, m.button);
		CanMsg msg = toCanMsg(m);
		CAN_Tx(msg);
		printf("Message sent\n");
	}
}

void GAMELOOP(){
	JOY_Calibrate();
	OLED_Reset();
	Menu_Start();
	while(1){
		MENU_PollAndUpdate();
		_delay_ms(100);
	}
}

 // **************************************************