#include "can.h"
#include "mcp2515.h"
#include "mcp2515_regs.h"

// Includes
// ****************************************************
#include <avr/io.h>
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
	// Enable receive interrupt
	MCP2515_Write(MCP_CANINTE, MCP_RX_INT);
	// Make interrupt pin input
	DDRE &= ~(1 << PE0);
	// Enable Rollover (fill RX1 if RX0 is full)
	unsigned char MCP_ROLLOVER = 0x2;
	MCP2515_Write(MCP_RXB0CTRL, (1 << MCP_ROLLOVER));
	// Set loop back mode
	MCP2515_Write(MCP_CANCTRL, MODE_LOOPBACK);
}

void CAN_Tx(CanMessage message){
	// Fill a transmit buffer TX0
	MCP2515_LoadTxBuffer(MCP_LOAD_TX0, message.id, message.data, message.length);
	// Transmit transmit buffer
	MCP2515_RequestToSend(MCP_RTS_TX0);
}

int CAN_Rx(CanMessage *message){
	// Read register
	unsigned char canint_reg = MCP2515_Read(MCP_CANINTF);
	int Rx0IF = canint_reg & MCP_RX0IF;
	int Rx1IF = canint_reg & MCP_RX1IF;
	// Decode 
	if(Rx0IF){
		MCP2515_ReadRxBuffer(MCP_READ_RX0, &(message->id), &(message->data), &(message->length));
		return 1; 
	}
	
	if(Rx1IF){
		MCP2515_ReadRxBuffer(MCP_READ_RX1, &(message->id), &(message->data), &(message->length));
		return 1;
	}
	return 0;
}

int CAN_Poll(){
	return !((PINE) & (1 << PINE0));
}

// ****************************************************