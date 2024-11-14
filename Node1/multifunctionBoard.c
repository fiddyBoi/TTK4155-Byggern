#include "multifunctionBoard.h"

// Includes
// ****************************************************
#include <stdint.h>
#include <avr/io.h>
#include "adc.h"
// ****************************************************

// Private macros and constants
// ****************************************************
// ****************************************************

// Private types
// ****************************************************
// ****************************************************

// Private global variables
// ****************************************************
int threshold = 20;
int zeroPos = 157; // default value, will be changed by JOY_Calibrate
// ****************************************************

// Private functions
// ****************************************************

// ****************************************************

// Implementation of the public functions
// ****************************************************

void JOY_Init(){
	// Configure PE2 to input (joystick button)
	DDRE &= ~(1 << PE2);
}

void JOY_Calibrate(){
	uint8_t avrage;
	uint8_t zeroX = ADC_Read(JOYSTICK_X_CHANNEL);
	uint8_t zeroY = ADC_Read(JOYSTICK_Y_CHANNEL);
	avrage = (int) (zeroX + zeroY) / 2;
	zeroPos = avrage;
}

JoystickPosition JOY_GetPosition(){
	JoystickPosition pos;
	uint8_t x = ADC_Read(JOYSTICK_X_CHANNEL);
	uint8_t y = ADC_Read(JOYSTICK_Y_CHANNEL);
	pos.x = (int) (x - zeroPos)*100/128;
	pos.y = (int) (y - zeroPos)*100/128;
	// Enforce -100 to 100 limit
	if(pos.x > 100){pos.x = 100;}
	if(pos.x < -100){pos.x = -100;}
	if(pos.y > 100){pos.y = 100;}
	if(pos.y < -100){pos.y = -100;}
	return pos; 
}

JoystickDirection JOY_GetDirection(){
	JoystickDirection dir = NEUTRAL;
	JoystickPosition pos = JOY_GetPosition();
	
	if(pos.x > threshold){
		dir = RIGHT;
	}
	if(pos.x < -threshold){
		dir = LEFT;
	}
	if(pos.y > threshold){
		dir = UP;
	}
	if(pos.y < -threshold){
		dir = DOWN;
	}

	return dir;
}

int JOY_GetButton(){
	// reads the value of PE2 (joystick button)
	return !((PINE) & (1 << PINE2));
}

SliderPositions SLIDE_GetPositions(){
	int left = ADC_Read(SLIDER_LEFT_CHANNEL)*100/255;
	int right = ADC_Read(SLIDER_RIGHT_CHANNEL)*100/255;
	SliderPositions pos = {left, right};
	return pos;
}

// ****************************************************