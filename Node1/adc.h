#ifndef adc_H
#define adc_H
// Includes
// ****************************************************
#include <stdio.h>
// ****************************************************

// Constants
// ****************************************************
#define ADC_BASE_ADDRESS 0x1400 // Base address of ADC
#define SLIDER_RIGHT_CHANNEL 3
#define SLIDER_LEFT_CHANNEL 2
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

// Starts the PWM signal for the ADC's external clock
void ADC_Init();

// Returns the value for the given channel
uint8_t ADC_Read(uint8_t channel);

// ****************************************************

#endif