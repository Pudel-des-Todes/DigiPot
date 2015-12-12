#include "MCP41HV51_driver.h"


static SPI_HandleTypeDef *hspi= NULL;

static uint8_t tx_buffer[2] = { 0};
static uint8_t rx_buffer[2] = { 0};


// prptotypes 
static uint8_t chip_select (uint8_t , GPIO_PinState );
static MCP41HV51_status_t mcp41hv51_cmd_8bit(uint8_t , uint8_t );
MCP41HV51_status_t mcp41hv51_cmd_16bit(uint8_t , uint8_t , uint8_t ,uint8_t *);

// public functions 
MCP41HV51_status_t Pot_wiper_increment(uint8_t device_nr) {
	return mcp41hv51_cmd_8bit (device_nr,MCP41HV51_wiper_incr);
}

MCP41HV51_status_t Pot_wiper_decrement(uint8_t device_nr) {
	return mcp41hv51_cmd_8bit (device_nr,MCP41HV51_wiper_decr);
}

MCP41HV51_status_t Pot_wiper_read(uint8_t device_nr, uint8_t *dataOut) {
	return mcp41hv51_cmd_16bit (device_nr,MCP41HV51_wiper_read, 0xFF,  dataOut);
}

MCP41HV51_status_t Pot_wiper_write(uint8_t device_nr, uint8_t dataIn) {
	return mcp41hv51_cmd_16bit (device_nr,MCP41HV51_wiper_write, dataIn, NULL );
}

MCP41HV51_status_t  Pot_tcon_read (uint8_t device_nr, uint8_t *dataOut) {
	return mcp41hv51_cmd_16bit (device_nr,MCP41HV51_TCON_read, 0xFF,  dataOut);
}

MCP41HV51_status_t  Pot_tcon_write (uint8_t device_nr, uint8_t dataIn) {
	return mcp41hv51_cmd_16bit (device_nr,MCP41HV51_TCON_write, dataIn , NULL );
}
	

// private functions 	
static MCP41HV51_status_t mcp41hv51_cmd_8bit(uint8_t device_nr, uint8_t cmd) {
	
	HAL_StatusTypeDef hal_status;
	MCP41HV51_status_t status;
	
	tx_buffer[0] = cmd;
	tx_buffer[1] = 0xFF;
	
	chip_select(device_nr,GPIO_PIN_RESET);	
	hal_status = HAL_SPI_TransmitReceive(hspi,tx_buffer, rx_buffer,1,1);	
	if (hal_status != HAL_OK) {
		switch(hal_status) {
			case HAL_ERROR: status = CMD_HAL_ERROR; break;
			case HAL_BUSY: status = CMD_HAL_BUSY; break;
			case HAL_TIMEOUT: status = CMD_HAL_TIMEOUT; break;
		}
	} else {
		if ( !(rx_buffer[0] & MCP41HV51_CMDERR_bit) ) {
			status = CMD_ERR;
		} else {
			status = CMD_OK;			
		}
	}
	
	chip_select(device_nr,GPIO_PIN_SET);	
	return status;
}

static MCP41HV51_status_t mcp41hv51_cmd_16bit(uint8_t device_nr, uint8_t cmd, uint8_t dataIn,uint8_t *dataOut) {
	
	HAL_StatusTypeDef hal_status;
	MCP41HV51_status_t status;
	
	tx_buffer[0] = cmd;
	tx_buffer[1] = dataIn;
	if ( dataOut != NULL) {
		*dataOut = 0;
	}
	
	chip_select(device_nr,GPIO_PIN_RESET);	
	hal_status = HAL_SPI_TransmitReceive(hspi,tx_buffer, rx_buffer,2,100);	
	if (hal_status != HAL_OK) {
		switch(hal_status) {
			case HAL_ERROR: status = CMD_HAL_ERROR; break;
			case HAL_BUSY: status = CMD_HAL_BUSY; break;
			case HAL_TIMEOUT: status = CMD_HAL_TIMEOUT; break;
		}		
	} else {
		if ( !(rx_buffer[0] & MCP41HV51_CMDERR_bit) ) {
			status = CMD_ERR;
		} else {
			status = CMD_OK;
			if (dataOut != NULL) {
				*dataOut = rx_buffer[1];
			}						
		}
	}
	
	
	chip_select(device_nr,GPIO_PIN_SET);	
	return status;
}

uint8_t mcp41hv51_init(SPI_HandleTypeDef* spi_handle) {

	if (spi_handle == NULL) {
		return 1;
	}	
	hspi = spi_handle;
	chip_select(0,GPIO_PIN_SET);
	chip_select(1,GPIO_PIN_SET);	
	return 0;
}

static uint8_t chip_select (uint8_t device_nr, GPIO_PinState state) {
	GPIO_TypeDef *gpio;
	uint16_t pin;

		switch (device_nr) {
			case POT100k:
				gpio = MCP41HV51_nCS1_GPIOx;
				pin  = MCP41HV51_nCS1_PINxx;
				break;
			case POT10k:
				gpio = MCP41HV51_nCS2_GPIOx;
				pin  = MCP41HV51_nCS2_PINxx;
				break;
			default:
				return 1;
		}
		HAL_GPIO_WritePin(gpio,pin,state);
		return 0;
}

