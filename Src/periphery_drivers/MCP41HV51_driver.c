#include "MCP41HV51_driver.h"


static SPI_HandleTypeDef *hspi= NULL;

static uint8_t tx_buffer[2] = { 0};
static uint8_t rx_buffer[2] = { 0};

static uint8_t chip_select (MCP41HV51_devices device, GPIO_PinState state);



	


uint8_t mcp41hv51_init(SPI_HandleTypeDef* spi_handle) {
	if (spi_handle == NULL) {
		return 1;
	}	
	hspi = spi_handle;
	chip_select(DEVICE_1,GPIO_PIN_SET);
	chip_select(DEVICE_2,GPIO_PIN_SET);	
	return 0;
}


static MCP41HV51_status_t mcp41hv51_cmd_8bit(MCP41HV51_devices device, uint8_t cmd) {
	
	HAL_StatusTypeDef hal_status;
	MCP41HV51_status_t status;
	
	tx_buffer[0] = cmd;
	tx_buffer[1] = 0xFF;
	
	chip_select(device,GPIO_PIN_RESET);	
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
	
	
	chip_select(device,GPIO_PIN_SET);
	
	return status;
}




static uint8_t chip_select (MCP41HV51_devices device, GPIO_PinState state) {
	GPIO_TypeDef *gpio;
	uint16_t pin;
	

	
		switch (device) {
			case DEVICE_1:
				gpio = MCP41HV51_nCS1_GPIOx;
				pin  = MCP41HV51_nCS1_PINxx;
				break;
			case DEVICE_2:
				gpio = MCP41HV51_nCS2_GPIOx;
				pin  = MCP41HV51_nCS2_PINxx;
				break;
			default:
				return 1;
		}
		HAL_GPIO_WritePin(gpio,pin,state);
		return 0;
}

