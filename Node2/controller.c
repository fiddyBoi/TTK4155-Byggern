#include "controller.h"

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
int Kp;
int Ki;
int T = 20; // Sampling period ms
int Integrator_value = 0;
int reference = 0;
// ****************************************************

// Private functions
// ****************************************************
// ****************************************************

// Implementation of the public functions
// ****************************************************

void CONTROLLER_Init(int p, int i){
	// Set regulator parameters
	Kp = p; 
	Ki = i; 
	
	// Enable clock for RTT
	PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | PMC_PCR_PID(ID_RTT);
	PMC->PMC_PCER0 |= (1 << ID_RTT);
	
	// Configure RTT
	RTT->RTT_MR = RTT_MR_RTPRES(32) | RTT_MR_ALMIEN; // 1khz, alarm mode
	RTT->RTT_AR = RTT_AR_ALMV(T); // period
	
	// Enable interrupt
	NVIC_EnableIRQ(ID_RTT);
}

int PI_Controller(int reference, int measurement){
	int error = reference - measurement;
	Integrator_value += error; 
	int output = Kp*error + T/1000*Ki*Integrator_value;
	return output;
}

void CONTROLLER_SetReference(int r){
	reference = r; 
}

void RTT_Handler(void){
	// Read status register 
	uint32_t rtt_sr = RTT->RTT_SR;
	// Measure motor position 
	int measurement = ENCODER_Scale(ENCODER_Read());
	// Calculate output
	int output = PI_Controller(reference, measurement);
	// Control the motor
	MOTOR_Output(output);
	// Reset clock
	RTT->RTT_MR |= RTT_MR_RTTRST;
	// Clear
	NVIC_ClearPendingIRQ(ID_RTT);
};

// ****************************************************