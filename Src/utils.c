#include "stm32f0xx_hal.h"
#include "utils.h"


uint8_t ASCIItoHEX(uint8_t src , uint8_t *dest) {
	if ((src >= '0') && (src <= '9')) {
		*dest = (src - '0');
		return ASCII2HEX_OK;
	}		
	if ((src <= 'F') && (src >= 'A')) {
		*dest = (src - 'A' + 10);
		return ASCII2HEX_OK;
	}
	return ASCII2HEX_ERROR;
}

uint8_t HEXtoASCII(uint8_t src , uint8_t *dest) {
	if (src > 0x0f) {
		return ASCII2HEX_ERROR;
	}
	if (src <= 0x09) {		
		*dest = (src + '0');
		return ASCII2HEX_OK;
	}
	if (src >= 0x0a) {	
		*dest = (src + 'A' - 10);	
		return ASCII2HEX_OK;
	}
	return ASCII2HEX_ERROR;
}

uint8_t ASCIItoBYTE(uint8_t *src, uint8_t *dest)
{
	unsigned char temp;

	 
	if (ASCIItoHEX(*src++, dest) != ASCII2HEX_ERROR) {
	   if (ASCIItoHEX(*src, &temp) != ASCII2HEX_ERROR) {
		*dest = (*dest * 16) + temp;
		return ASCII2HEX_OK;
	  }
	}
	return ASCII2HEX_ERROR;
}


/*
uint8_t ASCIItoINT(uint8_t *source, uint16_t *word)
{
	unsigned char qty, temp;

	*word = 0;
	for (qty = 0; qty < 4; qty++) {
	  temp = ASCIItoHEX(*source++);
	  if (temp != ASCII2HEX_ERROR) {
		  *word = (*word * 16) + temp;
	  } else {
		  return ASCII2HEX_ERROR;
	  }
	}
	return ASCII2HEX_OK;
}
*/
