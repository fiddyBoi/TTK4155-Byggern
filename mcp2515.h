#ifndef mcp2515_H
#define mcp2515_H

// Includes
// ****************************************************
// ****************************************************

// Constants
// ****************************************************
// ****************************************************

// Types
// ****************************************************
// ****************************************************

// Global variables
// ****************************************************
// ****************************************************

// Function prototypes
// ****************************************************

// Initializes the mcp2515 driver
// Call SPI_Init prior to this
void MCP2515_Init();

// Returns the value at a given address on the CAN controller
// See mcp2515_regs.h for addresses
unsigned char MCP2515_Read(unsigned char address);

// Writes value at a given address on the CAN controller 
// See mcp2515_regs.h for addresses 
void MCP2515_Write(unsigned char address, unsigned char data);

// Request instructs the controller to begin a message transmission
// sequence for any of the transmit buffers. 
// RTS: MCP_RTS_TX0-2 or  MCP_RTS_ALL found in mcp2515_regs.h
void MCP2515_RequestToSend(unsigned char RTS);

// Provides a means for setting or clearing individual bits in specific 
// status and control registers. This command is not available for all
// registers (see "register map" in datasheet)
void MCP2515_BitModify(unsigned char address, unsigned char mask, unsigned char data);

// Eliminates the eight-bit addresss required by normal Write command. 
// TxN: MCP_LOAD_TX0 etc in mcp2515_regs.h
void MCP2515_LoadTxBuffer(unsigned char TxN, unsigned char id, unsigned char* data, unsigned char length);

// Same as LoadTxBuffer but for read. Clears flag automatically
void MCP2515_ReadRxBuffer(unsigned char RxN, unsigned char * id, unsigned char * data, unsigned char * length);

// Re-initializes the internal registers and set 
// Configuration mode
void MCP2515_Reset();

// Returns the controller's status bits
unsigned char MCP2515_ReadStatus();

// ****************************************************

#endif