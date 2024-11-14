#include "menu.h"

// Includes
// ****************************************************
#include <string.h>
#include "oled.h"
#include "multifunctionBoard.h"
#include "game.h"
// ****************************************************

// Private macros and constants
// ****************************************************

#define NUM_HOME_OPTIONS (int) 4
#define NUM_DIFFICULTY_OPTIONS (int) 3

const char* homeOptions[NUM_HOME_OPTIONS] = {
	"Start",
	"High score",
	"Calibrate",
	"Set difficulty"
};

// sub menu
const char* difficultyOptions[NUM_DIFFICULTY_OPTIONS] = {
	"Hard",
	"Medium",
	"Easy"	
};

// ****************************************************

// Private types
// ****************************************************

typedef enum CurrentMenu{
	HOME_MENU,
	DIFFICULTY_MENU
}CurrentMenu;

// ****************************************************

// Private global variables
// ****************************************************

CurrentMenu state = HOME_MENU;

int selectedOption = 0; // the index in the current menu

// ****************************************************

// Private functions
// ****************************************************

// Prints the current menu state to the screen
void render(){
	OLED_Reset();
	switch(state){
		case HOME_MENU:
			for(int i = 0; i < NUM_HOME_OPTIONS; i++){
				OLED_GoToLine(i);
				if(i == selectedOption){
					OLED_RightArrow();
				}else{
					OLED_WriteData(' ');
				}
				int length = strlen(homeOptions[i]);
				OLED_Print(homeOptions[i], length);
			}
			break;
		case DIFFICULTY_MENU:
			for(int i = 0; i < NUM_DIFFICULTY_OPTIONS; i++){
				OLED_GoToLine(i);
				if(i == selectedOption){
					OLED_RightArrow();
					}else{
					OLED_WriteData(' ');
				}
				int length = strlen(difficultyOptions[i]);
				OLED_Print(difficultyOptions[i], length);
			}		
			break;
	}
}
// ****************************************************

// Implementation of the public functions
// ****************************************************

void Menu_Start(){
	render();
}

void MENU_PollAndUpdate(){
	// Direction handling
	JoystickDirection dir = JOY_GetDirection();
	switch(state){
		case HOME_MENU:
			switch(dir){
				case UP:
					selectedOption = (selectedOption - 1 + NUM_HOME_OPTIONS) % NUM_HOME_OPTIONS;
					render();
					break;
				case DOWN:
					selectedOption = (selectedOption + 1 + NUM_HOME_OPTIONS) % NUM_HOME_OPTIONS;
					render();
					break;
				case RIGHT:
					if(homeOptions[selectedOption] == "Set difficulty"){
						state = DIFFICULTY_MENU;
						selectedOption = 0;
						render();
					}
					break;
			}
			break;
		case DIFFICULTY_MENU:
			switch(dir){
				case UP:
					selectedOption = (selectedOption - 1 + NUM_DIFFICULTY_OPTIONS) % NUM_DIFFICULTY_OPTIONS;
					render();
					break;
				case DOWN:
					selectedOption = (selectedOption + 1 + NUM_DIFFICULTY_OPTIONS) % NUM_DIFFICULTY_OPTIONS;
					render();
					break;
				case LEFT:
					state = HOME_MENU;
					selectedOption = 0;
					render();
					break;
			}
			break;
	}
	
	// Button handling
	int buttonInput = JOY_GetButton();
	if(!buttonInput){
		return;
	}
	// Button is pressed
	switch(state){
		case HOME_MENU:
			if(homeOptions[selectedOption] == "Start"){
				printf("Start was selected!\n");
				OLED_Reset();
				GAME_Start();
				render();
			}
			else if(homeOptions[selectedOption] == "Calibrate"){
				printf("Calibrate was selected\n");
				JOY_Calibrate();
			}
			break;
		case DIFFICULTY_MENU:
			printf("Difficulty %s was selected\n",  difficultyOptions[selectedOption]);
			break;
	}
}

// ****************************************************