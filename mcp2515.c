#include "mcp2515.h"
#include "mcp2515_regs.h"

// Includes
// ****************************************************
#include "spi.h"
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

void MCP2515_Init(){
	MCP2515_Reset() ; // Send reset - command
	
	// More initialization?
}

void MCP2515_Reset(){
	SPI_Ss(1);
	SPI_Transmit(MCP_RESET);
	SPI_Ss(0);
}

unsigned char MCP2515_Read(unsigned char address){
	unsigned char result;
	SPI_Ss(1);
	SPI_Transmit(MCP_READ);
	SPI_Transmit(address);
	result = SPI_Receive();
	SPI_Ss(0);
	return result;
}

void MCP2515_Write(unsigned char address, unsigned char data){
	SPI_Ss(1);
	SPI_Transmit(MCP_WRITE);
	SPI_Transmit(address);
	SPI_Transmit(data);
	SPI_Ss(0);
}

void MCP2515_RequestToSend(unsigned char RTS){
	SPI_Ss(1);
	SPI_Transmit(RTS);
	SPI_Ss(0);
}

void MCP2515_BitModify(unsigned char address, unsigned char mask, unsigned char data){
	SPI_Ss(1);
	SPI_Transmit(MCP_BITMOD);
	SPI_Transmit(address);
	SPI_Transmit(mask);
	SPI_Transmit(data);
	SPI_Ss(0);
}

unsigned char MCP2515_ReadStatus(){
	unsigned char status;
	SPI_Ss(1);
	SPI_Transmit(MCP_READ_STATUS);
	status = SPI_Receive();
	SPI_Ss(0);
	return status;
}

// ****************************************************