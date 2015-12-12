
#ifndef MCP41HV51_DRIVER
#define MCP41HV51_DRIVER

#include "stm32f0xx_hal.h"


#define POT100k 0
#define POT10k 1

typedef enum {
	CMD_OK 			= 0x00,
	CMD_ERR			= 0x01,
	CMD_HAL_ERROR   = 0x02,
	CMD_HAL_BUSY    = 0x03,
	CMD_HAL_TIMEOUT = 0x04
} MCP41HV51_status_t;


//  Command format
//  b0 b1 b3 b3 b4 b5 b6 b7 | b8 b9 bA bB bC bD bE bF
//   ^           ^     ^  ^    ^
//   |           |     |  |    +--- Data
//   |           |     |  |	
//   |           |     |  +- Not Used
//   |           |     +----CMDERR_bit
//   |           +------Command
//   +---- Address
//   
// avaliable commands
#define MCP41HV51_wiper_read	(0x0C)
#define MCP41HV51_wiper_write	(0x00)
#define MCP41HV51_wiper_incr	(0x04)
#define MCP41HV51_wiper_decr	(0x08)
#define MCP41HV51_TCON_read		(0x4C)  // terminal control
#define MCP41HV51_TCON_write	(0x40)


// macro to format a command byte
// command error bit
#define MCP41HV51_CMDERR_bit 	(0x02)

// // terminal control TCON bits
#define MCP41HV51_TCON_R0HW		(0x08) 
#define MCP41HV51_TCON_R0A		(0x04)
#define MCP41HV51_TCON_R0W		(0x02)
#define MCP41HV51_TCON_R0B		(0x01)

// nCS GPIO pins
#define MCP41HV51_nCS1_GPIOx GPIOB
#define MCP41HV51_nCS1_PINxx GPIO_PIN_4
#define MCP41HV51_nCS2_GPIOx GPIOB
#define MCP41HV51_nCS2_PINxx GPIO_PIN_5


MCP41HV51_status_t Pot_wiper_increment(uint8_t );
MCP41HV51_status_t Pot_wiper_decrement(uint8_t );
MCP41HV51_status_t Pot_wiper_read(uint8_t , uint8_t *);
MCP41HV51_status_t Pot_wiper_write(uint8_t , uint8_t );

MCP41HV51_status_t Pot_tcon_read (uint8_t device_nr, uint8_t *dataOut);
MCP41HV51_status_t Pot_tcon_write (uint8_t device_nr, uint8_t dataIn);

uint8_t mcp41hv51_init(SPI_HandleTypeDef *spi_handle);
uint8_t mcp41hv51_read_wiper(void);



#endif
