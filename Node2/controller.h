#ifndef controller_H
#define controller_H
// Includes
// ****************************************************
// ****************************************************

// Constants
// ****************************************************
// ****************************************************

// Types
// ****************************************************

// ****************************************************

// Global variables
// ****************************************************
// ****************************************************

// Function prototypes
// ****************************************************

// We assume the motor starts in the middle position!
// Initializes the motor PI controller, p and i are 
// regulator parameters. 
// When started in the middle position the encoder
// measurement will yield positions in the range 
// -100 to 100 where 0 is the middle position.
void CONTROLLER_Init(int p, int i);

// The joysticks -100 to 100 signal is used as a reference for
// the motor position. Call this function to update the reference
void CONTROLLER_SetReference(int r);

// ****************************************************
#endif