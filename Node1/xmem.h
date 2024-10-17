#ifndef xmem_H
#define xmem_H

// Includes
// ****************************************************
#include <stdint.h>
// ****************************************************

// Constants
// ****************************************************
#define SRAM_BASE_ADDRESS 0x1800 // Base address of SRAM
// ****************************************************

// Types
// ****************************************************
// ****************************************************

// Global variables
// ****************************************************
// ****************************************************

// Function prototypes
// ****************************************************

// Enables external memory and masks the pins for JTAG
void XMEM_Init();

// Writes to BASE_ADDRESS + addr
void XMEM_Write(uint8_t data, uint16_t addr);

// Reads from BASE_ADDRESS + addr
uint8_t XMEM_Read(uint16_t addr);

// ****************************************************

#endif