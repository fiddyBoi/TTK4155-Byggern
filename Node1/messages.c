#include "messages.h"

// Includes
// ****************************************************
// ****************************************************

// Private macros and constants
// ****************************************************
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

CanMsg toCanMsg(JoystickPosition pos){
	CanMsg message = {
		.id = ID_Joystick,
		.length = 2,
		.byte = {(uint8_t)pos.x,(uint8_t)pos.y}
	};
	return message;
}

JoystickPosition toJoyPos(CanMsg msg){
	JoystickPosition pos = {
		.x = (int8_t)msg.byte[0],
		.y = (int8_t)msg.byte[1]
	};
	return pos;
}

// ****************************************************