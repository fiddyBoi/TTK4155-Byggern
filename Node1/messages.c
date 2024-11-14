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

CanMsg toCanMsg(ApplicationMsg msg){
	CanMsg message = {
		.id = ID_APPMESSAGE,
		.length = 3,
		.byte = {(uint8_t)msg.x,(uint8_t)msg.y,(uint8_t)msg.button}
	};
	return message;
}

ApplicationMsg toAppMsg(CanMsg msg){
	ApplicationMsg m = {
		.x = (int8_t)msg.byte[0],
		.y = (int8_t)msg.byte[1],
		.button = (int8_t)msg.byte[2]
	};
	return m;
}

// ****************************************************