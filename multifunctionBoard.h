#ifndef multifunctionBoard_H
#define multifunctionBoard_H
// Includes
// ****************************************************
#include <stdint.h>
// ****************************************************

// Constants
// ****************************************************
// ****************************************************

// Types
// ****************************************************

typedef struct JoystickPosition{
	int x; // -100 to 100
	int y; // -100 to 100
} JoystickPosition;

typedef enum JoystickDirection{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL
} JoystickDirection;

static const char *DIR_STRING[] = {
	"LEFT", "RIGHT", "UP", "DOWN", "NEUTRAL",
};

// ****************************************************

// Global variables
// ****************************************************
// ****************************************************

// Function prototypes
// ****************************************************

// Resets the zeroPos to the current position
void JOY_Calibrate();

// Returns the analog position in a struct {%, %}
JoystickPosition JOY_GetPosition(); 

// Returns the direction. Sensitivity can be modified my changing threshold in .C file.
JoystickDirection JOY_GetDirection();

// ****************************************************
#endif