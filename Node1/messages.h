#ifndef messages_H
#define messages_H

// Includes
// ****************************************************
#include "can.h"
// ****************************************************

// Constants
// ****************************************************
#define ID_APPMESSAGE 1
// ****************************************************

// Types
// ****************************************************
typedef struct ApplicationMsg{
	int x; // -100 to 100 joystick
	int y; // -100 to 100 joystick
	int button;
} ApplicationMsg;
// ****************************************************

// Global variables
// ****************************************************
// ****************************************************

// Function prototypes
// ****************************************************
CanMsg toCanMsg(ApplicationMsg msg);
ApplicationMsg toAppMsg(CanMsg msg);
// ****************************************************
#endif