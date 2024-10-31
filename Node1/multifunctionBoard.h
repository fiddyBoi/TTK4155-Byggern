#ifndef multifunctionBoard_H
#define multifunctionBoard_H
// Includes
// ****************************************************
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

typedef struct SliderPositions{
	int left; // 0 to 100
	int right; // 0 to 100
} SliderPositions;

// ****************************************************

// Global variables
// ****************************************************
// ****************************************************

// Function prototypes
// ****************************************************

// Initializes joystick driver, remember to also call ADC_Init!
void JOY_Init();

// Resets the zeroPos to the current position
void JOY_Calibrate();

// Returns the analog position in a struct {%, %}
JoystickPosition JOY_GetPosition(); 

// Returns the direction. Sensitivity can be modified my changing threshold in .C file.
JoystickDirection JOY_GetDirection();

// Returns the value for the Joystick button
// 1 = button pressed 
// 0 = button not pressed
int JOY_GetButton();

// Returns the left and right slider positions in a struct 
SliderPositions SLIDE_GetPositions();
// ****************************************************
#endif