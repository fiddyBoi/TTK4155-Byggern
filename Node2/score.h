#ifndef score_H
#define score_H

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

// NB: Call ADC_Init prior to using this module!

// Sets the first internal timestamp
void SCORE_Init();

// Uses the ADC to read and update the internal score
// ignores spurious goals due to ball bouncing etc
void SCORE_Poll();

int SCORE_GetScore();

// ****************************************************
#endif




