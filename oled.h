#ifndef oled_H
#define oled_H
// Includes
// ****************************************************
// ****************************************************

// Constants
// ****************************************************
#define OLED_COMMAND_BASE_ADDRESS 0x1000
#define OLED_DATA_BASE_ADDRESSS 0X1200
// ****************************************************

// Types
// ****************************************************
// ****************************************************

// Global variables
// ****************************************************
// ****************************************************

// Function prototypes
// ****************************************************

// NOTE: This driver disregards columns and always goes to 
// column 0 when using goto or reset. Therefore when going 
// back to a previous line, old data will we overwritten.
// However, when writing on the same line consecutively it will 
// not overwrite previous data.

// Initializes the OLED driver in page addressing mode
void OLED_Init();

// Clears all lines and returns to start of first line
void OLED_Reset();

// Puts cursor at start of specified line/page
void OLED_GoToLine(int line);

// Clears the whole specified line
void OLED_ClearLine(int line); 

// Print char at current position
void OLED_WriteData(char data);

// Print string at current position
void OLED_Print(char* string, int length);

// Prints out a right arrow at current position 
void OLED_RightArrow();

// Prints out right arrow at current position
void OLED_LeftArrow();

// Sets all the pixels ON until OLED_Reset() is called
// and previous RAM content is displayed
void OLED_EntireDisplayOn();

// ****************************************************

#endif