/*
 * GccApplication1.c
 *
 * Created: 05.09.2024 09:29:02
 * Author : fredrbb
 */ 

#define F_CPU 4915200
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "xmem.h"

// Test functions - prototypes
// **************************************************

// Outputs a square wave of period 2s on PA0 (ATmega162)
void IO_test();

// Listens to a byte sent over UART and echo's it back (ATmega162)
void UART_test();

// Test the linking of printf (ATmega162)
void PRINTF_test();

// Testing the SRAM by writing and retrieving to the SRAM
void SRAM_test();

// **************************************************

int main(void)
{
	// Init drivers
	UART_Init(MYUBRR);
	XMEM_Init();
	
	// test shit
	SRAM_test();
}

 // Test functions - implementation
 // **************************************************
 
 void IO_test(){
	 int i = 0;
	 DDRA = 0x1; // set PA0 to output
	 while(1){
		 if(i == 0){
			 PORTA = 0x0; // set PA0 low
			 i = 1;
			 }else{
			 PORTA = 0x1; // set PA0 high
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
 // **************************************************