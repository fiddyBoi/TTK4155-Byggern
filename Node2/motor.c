#include "motor.h"

// Includes
// ****************************************************
#include "sam.h"
#include <stdlib.h>
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

void MOTOR_Init(){
	// ENABLE/PWM pin PB12
	// PHASE/DIR pin PC23
	
	// ENABLE/PWM
	// ************************************************
	// Enable pwm I/O
	PIOB->PIO_ABSR |= PIO_PB12B_PWMH0;
	PIOB->PIO_PDR |= PIO_PB12B_PWMH0;
	
	// Enable clock for pwm
	PMC->PMC_PCER1 |= 1 << (ID_PWM - 32);
	
	// PWM Clock / mode
	PWM->PWM_CLK |= PWM_CLK_PREA(0) | PWM_CLK_DIVA(84); // divide by 84 so we get 1Mhz (FCPU is 8.4Mhz)
	PWM->PWM_CH_NUM[0].PWM_CMR = PWM_CMR_CPRE_CLKA | PWM_CMR_CPOL; // clock A, active high, left-align
	
	// PWM Period
	PWM->PWM_CH_NUM[0].PWM_CPRD = PWM_CPRD_CPRD(20000); // 20ms
	
	// Set to a legal duty cycle
	PWM->PWM_CH_NUM[0].PWM_CDTY = PWM_CDTY_CDTY(0); // 0.0ms to begin with
	
	// Enable PWM channel 0
	PWM->PWM_ENA = PWM_ENA_CHID0;
	// ************************************************
	
	// PHASE/DIR
	// ************************************************
	// Enable clock for PIOC
	PMC->PMC_PCER0 |= (1 << ID_PIOC);
	// Enable control of PC23 and set as output
	PIOC->PIO_PER = PIO_PER_P23;
	PIOC->PIO_OER = PIO_OER_P23;
	// ************************************************
}

void MOTOR_Output(int input){
	// force input into -100 to 100 range
	if(input < -100){
		input = -100;
	}
	if(input > 100){
		input = 100;
	}
	// Decide and set direction 
	if(input < 0){
		PIOC->PIO_SODR = PIO_SODR_P23;
	}
	if(input >= 0){
		PIOC->PIO_CODR = PIO_SODR_P23;
	}
	
	// convert to 0-20ms
	// 0 -> 0, +-100 -> 20000
	int output = 200*abs(input);
	
	// set duty cycle
	PWM->PWM_CH_NUM[0].PWM_CDTY = PWM_CDTY_CDTY(output);
}

// ****************************************************