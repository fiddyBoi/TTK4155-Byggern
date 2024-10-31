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
		.byte = {pos.x, pos.y}
	};
	return message;
}

JoystickPosition toJoyPos(CanMsg msg){
	JoystickPosition pos = {
		.x = msg.byte[0],
		.y = msg.byte[1]
	};
	return pos;
}

// ****************************************************