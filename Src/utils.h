#ifndef UTILS_H
#define UTILS_H

#define ASCII2HEX_ERROR	0x00
#define ASCII2HEX_OK 	0x01

uint8_t ASCIItoHEX(uint8_t src , uint8_t *dest);
uint8_t HEXtoASCII(uint8_t src , uint8_t *dest);

uint8_t ASCIItoBYTE(uint8_t *src, uint8_t *dest);

#endif
