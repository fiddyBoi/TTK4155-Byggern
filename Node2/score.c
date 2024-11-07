#include "score.h"

// Includes
// ****************************************************
#include "adc.h"
#include "time.h"
#include <stdio.h>
// ****************************************************

// Private macros and constants
// ****************************************************
const uint16_t THRESHOLD = 1500; // MODIFY THIS LATER
const uint64_t timeout = 1; // // min 1 second between points
// ****************************************************

// Private types
// ****************************************************
// ****************************************************

// Private global variables
// ****************************************************
uint64_t timestamp;
int score = 0;
uint64_t TIMEOUT; 
// ****************************************************

// Private functions
// ****************************************************
// ****************************************************

// Implementation of the public functions
// ****************************************************

void SCORE_Init(){
	TIMEOUT = seconds(timeout);
	timestamp = time_now();
}

void SCORE_Poll(){
	if(ADC_Read() < THRESHOLD){ // score! (MODIFY > or < LATER)
		if((time_now() - timestamp) > TIMEOUT){ // over 1 second since last time
			score += 1;
			timestamp = time_now();
		}
	}
}

int SCORE_GetScore(){
	return score;
}

// ****************************************************