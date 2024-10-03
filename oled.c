#include "oled.h"

// Includes
// ****************************************************
#include <avr/pgmspace.h>
#include "fonts.h"
// ****************************************************

// Private macros and constants
// ****************************************************
#define NUM_COLUMNS (int) 128
#define NUM_LINES (int) 8

#define LARGE_FONT_SIZE (int) 8
#define MEDIUM_FONT_SIZE (int) 5
#define SMALL_FONT_SIZE (int) 4
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

void OLED_Init(){
	volatile char * oled_command_mem = (char*) OLED_COMMAND_BASE_ADDRESS;
	
	 *oled_command_mem = (0xae); // display off
	 *oled_command_mem = (0xa1); //segment remap
	 *oled_command_mem = (0xda); //common pads hardware: alternative
	 *oled_command_mem = (0x12);
	 *oled_command_mem = (0xc8); //common output scan direction:com63~com0
	 *oled_command_mem = (0xa8); //multiplex ration mode:63
	 *oled_command_mem = (0x3f);
	 *oled_command_mem = (0xd5); //display divide ratio/osc. freq. mode
	 *oled_command_mem = (0x80);
	 *oled_command_mem = (0x81); //contrast control
	 *oled_command_mem = (0x50);
	 *oled_command_mem = (0xd9); //set pre-charge period
	 *oled_command_mem = (0x21);
	 *oled_command_mem = (0x20); //Set Memory Addressing Mode (page addressing mode)
	 *oled_command_mem = (0x02);
	 *oled_command_mem = (0xdb); //VCOM deselect level mode
	 *oled_command_mem = (0x30);
	 *oled_command_mem = (0xad); //master configuration
	 *oled_command_mem = (0x00);
	 *oled_command_mem = (0xa4); //out follows RAM content
	 *oled_command_mem = (0xa6); //set normal display
	 *oled_command_mem = (0xaf); // display on
} 

void OLED_EntireDisplayOn(){
	volatile char * oled_command_mem = (char *) OLED_COMMAND_BASE_ADDRESS;
	*oled_command_mem = 0xa5; // turn on entire display
}

void OLED_GoToLine(int line){
	volatile char * oled_command_mem = (char *) OLED_COMMAND_BASE_ADDRESS;
	*oled_command_mem = (0xb0 + line); // goto line
	*oled_command_mem = (0x00); // goto column 0 
	*oled_command_mem = (0x10); // goto first pixel of column 0
}

void OLED_ClearLine(int line){
	volatile char * oled_data_mem = (char *) OLED_DATA_BASE_ADDRESSS;
	OLED_GoToLine(line);
	for(int i = 0; i < NUM_COLUMNS; i++){
		*oled_data_mem = 0x0;
	}
}

void OLED_Reset(){
	volatile char * oled_command_mem = (char *) OLED_COMMAND_BASE_ADDRESS;
	*oled_command_mem = 0xa4; // Resume RAM content on display
	for(int line = 0; line < NUM_LINES; line++){
		OLED_ClearLine(line);
	}
	OLED_GoToLine(0); // Reset back to top line
}

void OLED_WriteData(char data){
	volatile char * oled_data_mem = (char *) OLED_DATA_BASE_ADDRESSS;
	char data_conv = data - 32; // convert from ASCII to how it is formatted in fonts.h
	// Large font 8x8
	for(int i = 0; i < LARGE_FONT_SIZE; i++){
		char byte = pgm_read_byte(&font8[data_conv][i]);
		*oled_data_mem = byte;
	}
}

void OLED_Print(char* string, int length){
	for(int i = 0; i < length; i++){
		OLED_WriteData(string[i]);
	}
}

void OLED_RightArrow(){
	volatile char * oled_data_mem = (char *) OLED_DATA_BASE_ADDRESSS;
	*oled_data_mem = (0b00011000);
	*oled_data_mem = (0b00011000);
	*oled_data_mem = (0b01111110);
	*oled_data_mem = (0b00111100);
	*oled_data_mem = (0b00011000);
}

void OLED_LeftArrow(){
	volatile char * oled_data_mem = (char *) OLED_DATA_BASE_ADDRESSS;
	*oled_data_mem = (0b00011000);
	*oled_data_mem = (0b00111100);
	*oled_data_mem = (0b01111110);
	*oled_data_mem = (0b00011000);
	*oled_data_mem = (0b00011000);
}

// ****************************************************