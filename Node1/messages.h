#ifndef messages_H
#define messages_H

// Includes
// ****************************************************
#include "can.h"
#include "multifunctionBoard.h"
// ****************************************************

// Constants
// ****************************************************
#define ID_Joystick 1
// ****************************************************

// Types
// ****************************************************
// ****************************************************

// Global variables
// ****************************************************
// ****************************************************

// Function prototypes
// ****************************************************
CanMsg toCanMsg(JoystickPosition pos);
JoystickPosition toJoyPos(CanMsg msg);
// ****************************************************
#endif