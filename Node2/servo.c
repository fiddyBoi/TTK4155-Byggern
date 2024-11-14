#include "servo.h"

// Includes
// ****************************************************
#include "sam.h"
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

void SERVO_Init(){
	// We will use PWMH1, peripheral B, PB13
	
	// Enable pwm I/O
	PIOB->PIO_ABSR |= PIO_PB13B_PWMH1;
	PIOB->PIO_PDR |= PIO_PB13B_PWMH1;
	
	// Enable clock for pwm
	PMC->PMC_PCER1 |= 1 << (ID_PWM - 32);
	
	// PWM Clock / mode
	PWM->PWM_CLK |= PWM_CLK_PREA(0) | PWM_CLK_DIVA(84); // divide by 84 so we get 1Mhz (FCPU is 8.4Mhz)
	PWM->PWM_CH_NUM[1].PWM_CMR = PWM_CMR_CPRE_CLKA | PWM_CMR_CPOL; // clock A, active high, left-align
	
	// PWM Period
	PWM->PWM_CH_NUM[1].PWM_CPRD = PWM_CPRD_CPRD(20000); // 20ms
	
	// Set to a legal duty cycle
	PWM->PWM_CH_NUM[1].PWM_CDTY = PWM_CDTY_CDTY(1500); // 1.5ms
	
	// Enable PWM channel 1
	PWM->PWM_ENA = PWM_ENA_CHID1;
}

void SERVO_Output(int input){
	// force input into -100 to 100 range
	if(input < -100){
		input = -100;
	}
	if(input > 100){
		input = 100;
	}
	
	// convert to 0.9-2.1ms
	// -100 -> 900, 100 -> 2100
	int output = 6*input + 1500;
	
	// set duty cycle
	PWM->PWM_CH_NUM[1].PWM_CDTY = PWM_CDTY_CDTY(output);
}

// ****************************************************