#ifndef can_H
#define can_H

// Includes
// ****************************************************
// ****************************************************

// Constants
// ****************************************************
// ****************************************************

// Types
// ****************************************************
typedef struct CanMessage{
	unsigned char id; // MSB id
	unsigned char length;
	unsigned char data[8];
} CanMessage;
// ****************************************************

// Global variables
// ****************************************************
// ****************************************************

// Function prototypes
// ****************************************************

// Remember to call MCP2515_Init() first.
void CAN_Init();

// Transmits the CAN message
void CAN_Tx(CanMessage message);

// Returns 1 if message was received and updates the 
// passed message
int CAN_Rx(CanMessage *message);

// Returns 1 if CAN controller interrupt pin is 1
int CAN_Poll();

// ****************************************************
#endif 