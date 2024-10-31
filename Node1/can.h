#ifndef can_H
#define can_H

// Includes
// ****************************************************
#include <stdio.h>
// ****************************************************

// Constants
// ****************************************************
#define BAUDRATE 250000
#define NUM_TQ 16
#define PROPAG 2
#define PHASE1 6
#define PHASE2 7
#define CAN_F_CPU 16000000
// ****************************************************

// Types
// ****************************************************

// Strict-aliasing-safe reinterpret-cast
#define union_cast(type, x) \
(((union { \
	typeof(x) a; \
	type b; \
})x).b)
// Dummy type for use with `union_cast`
typedef struct Byte8 Byte8;
struct Byte8 {
	uint8_t bytes[8];
};

typedef struct CanMsg CanMsg;
struct CanMsg {
	uint8_t id;
	uint8_t length;
	union {
		uint8_t     byte[8];
		uint32_t    dword[2];
		Byte8       byte8;
	};
};
// ****************************************************

// Global variables
// ****************************************************
// ****************************************************

// Function prototypes
// ****************************************************

// Remember to call MCP2515_Init() first.
void CAN_Init();

// Transmits the CAN message
void CAN_Tx(CanMsg message);

// Returns 1 if message was received and updates the 
// passed message
int CAN_Rx(CanMsg *message);

// Returns 1 if CAN controller interrupt pin is 1
int CAN_Poll();

// ****************************************************
#endif 