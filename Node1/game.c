#include "game.h"

// Includes
// ****************************************************
#include "multifunctionBoard.h"
#include "messages.h"
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

void GAME_Start(){
	while(1){
		JoystickPosition pos = JOY_GetPosition();
		int b = JOY_GetButton();
		ApplicationMsg m = {
			.x = pos.x,
			.y = pos.y,
			.button = b
		};
		CanMsg msg = toCanMsg(m);
		CAN_Tx(msg);
		
		// See if we should quit
		SliderPositions sPos = SLIDE_GetPositions();
		if(sPos.left == 100){
			return;
		}
	}
}

// ****************************************************