#include "can.h"
#include "mcp2515.h"
#include "mcp2515_regs.h"

// Includes
// ****************************************************
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

void CAN_Init(){
	// Set loop back mode
	MCP2515_Write(MCP_CANCTRL, MODE_LOOPBACK);
	// Enable receive interrupt
	MCP2515_Write(MCP_CANINTE, MCP_RX0IF);
	// more?
}

void CAN_Transmit(CanMessage message){
	// Fill a transmit buffer?
	// Transmit transmit buffer
	MCP2515_RequestToSend(MCP_RTS_TX0);
}

// ****************************************************