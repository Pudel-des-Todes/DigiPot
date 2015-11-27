
#ifndef MCP41HV51_DRIVER
#define MCP41HV51_DRIVER

#include "stm32f0xx_hal.h"


typedef enum {
	DEVICE_1,
	DEVICE_2
} MCP41HV51_devices;

typedef enum {
	CMD_OK 			= 0x00,
	CMD_ERR			= 0x01,
	CMD_HAL_ERROR   = 0x02,
	CMD_HAL_BUSY    = 0x03,
	CMD_HAL_TIMEOUT = 0x04
} MCP41HV51_status_t;


// avaliable addresses
#define MCP41HV51_addr_wiper	(0x00)
#define MCP41HV51_addr_TCON		(0x04)

// avaliable commands
#define MCP41HV51_read_cmd		(0x03)
#define MCP41HV51_write_cmd		(0x00)
#define MCP41HV51_incr_cmd		(0x01)
#define MCP41HV51_decr_cmd		(0x02)

// macro to format a command byte
#define MCP41HV51_command(addr,cmd) ((addr<< 4)|(cmd<<2)) 
// command error bit
#define MCP41HV51_CMDERR_bit 	(0x02)

// TCON bits
#define MCP41HV51_TCON_R0HW		(0x08) 
#define MCP41HV51_TCON_R0A		(0x04)
#define MCP41HV51_TCON_R0W		(0x02)
#define MCP41HV51_TCON_R0B		(0x01)

// nCS GPIO pins
#define MCP41HV51_nCS1_GPIOx GPIOB
#define MCP41HV51_nCS1_PINxx GPIO_PIN_4
#define MCP41HV51_nCS2_GPIOx GPIOB
#define MCP41HV51_nCS2_PINxx GPIO_PIN_5




uint8_t mcp41hv51_init(SPI_HandleTypeDef *spi_handle);
uint8_t mcp41hv51_read_wiper(void);



#endif
