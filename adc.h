#ifndef adc_H
#define adc_H
// Includes
// ****************************************************
#include <stdio.h>
// ****************************************************

// Constants
// ****************************************************
#define ADC_BASE_ADDRESS 0x1400 // Base address of ADC
#define JOYSTICK_X_CHANNEL 1
#define JOYSTICK_Y_CHANNEL 0
// ****************************************************

// Types
// ****************************************************
// ****************************************************

// Global variables
// ****************************************************
// ****************************************************

// Function prototypes
// ****************************************************

void ADC_Init();
uint8_t ADC_Read(uint8_t channel);

// ****************************************************

#endif