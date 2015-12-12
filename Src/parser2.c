
#include "stm32f0xx_hal.h"
#include "parser2.h"
#include "uart.h"
#include "data.h"
#include "string.h"
#include "utils.h"

#include "periphery_drivers\lcd_driver.h"
#include "periphery_drivers\MCP41HV51_driver.h"




static void TY_Function(uint8_t *pData) {
  uart2_transmit(VERSION);
}



static void WS_Function(uint8_t *pData) {
	uint8_t device = 0;
	uint8_t wiper = 0;
	
	if ( !ASCIItoBYTE(pData+3, &device)  ||
		 *(pData +5)  != ',' ||
		 !ASCIItoBYTE(pData+6, &wiper)	) {
		uart2_transmit("ws:error_format\r\n");	 
		return;
	}
	
	if (Pot_wiper_write(device,wiper) == CMD_OK){
		uart2_transmit("ws:ok\r\n");
	} else {
		uart2_transmit("ws:error\r\n");
	}	
}


static void WG_Function(uint8_t *pData) {
	uint8_t device = 0;
	uint8_t wiper;
	
	if ( !ASCIItoBYTE(pData+3, &device) ) {
		uart2_transmit("wg:error_format\r\n");	 
		return;
	}
	
	if (Pot_wiper_read(device,&wiper) == CMD_OK) {
		sprintf((char*)uart2_tx_buffer,"wg:%02X\r\n",wiper);
		uart2_transmit((char*)uart2_tx_buffer);
		
	}
}

static void WI_Function(uint8_t *pData) {
	uint8_t device = 0;
	uint8_t n = 0;
	
	if ( !ASCIItoBYTE(pData+3, &device)  ||
		 *(pData +5)  != ',' ||
		 !ASCIItoBYTE(pData+6, &n)	) {
		uart2_transmit("wi:error_format\r\n");	 
		return;
	}
	
	for (int i = 0; i < n; i++) {
		if (! Pot_wiper_increment(device) == CMD_OK){
			uart2_transmit("wi:error\r\n");
		}
	}	
	uart2_transmit("wi:ok\r\n");
}

static void WD_Function(uint8_t *pData) {
	uint8_t device = 0;
	uint8_t n = 0;
	
	if ( !ASCIItoBYTE(pData+3, &device)  ||
		 *(pData +5)  != ',' ||
		 !ASCIItoBYTE(pData+6, &n)	) {
		uart2_transmit("wd:error_format\r\n");	 
		return;
	}
	
	for (int i = 0; i < n; i++) {
		if (! Pot_wiper_decrement(device) == CMD_OK){
			uart2_transmit("wd:error\r\n");
		}
	}	
	uart2_transmit("wd:ok\r\n");
}



static void TS_Function(uint8_t *pData) {
	uint8_t device = 0;
	uint8_t wiper = 0;
	
	if ( !ASCIItoBYTE(pData+3, &device)  ||
		 *(pData +5)  != ',' ||
		 !ASCIItoBYTE(pData+6, &wiper)	) {
		uart2_transmit("ts:error_format\r\n");	 
		return;
	}
	
	if (Pot_tcon_write(device,wiper) == CMD_OK){
		uart2_transmit("ts:ok\r\n");
	} else {
		uart2_transmit("ts:error\r\n");
	}	
}


static void TG_Function(uint8_t *pData) {
	uint8_t device = 0;
	uint8_t wiper;
	
	if ( !ASCIItoBYTE(pData+3, &device) ) {
		uart2_transmit("tg:error_format\r\n");	 
		return;
	}
	
	if (Pot_tcon_read(device,&wiper) == CMD_OK) {
		sprintf((char*)uart2_tx_buffer,"tg:%02X\r\n",wiper);
		uart2_transmit((char*)uart2_tx_buffer);
	}
}



static void	RS_Function(uint8_t *pData) {
	uint8_t device = 0;
	uint8_t wiper;
	
	if ( !ASCIItoBYTE(pData+3, &device) ) {
		uart2_transmit("tg:error_format\r\n");	 
		return;
	}
	

}


// TC:00,A
static void TC_Function(uint8_t *pData) {
	uint8_t device = 0;
	uint8_t c;
	uint8_t s;
	uint8_t tcon_reg =0;
	uint8_t mask;
	
	if ( !ASCIItoBYTE(pData+3, &device) ) {
		uart2_transmit("tc:error_format\r\n");	 
		return;
	}
	c = *(pData+6);
	s = *(pData+7);
	
	if (s == '0' || s == '1') {
		s -= '0';
	} else { 
		uart2_transmit("tc:error_format\r\n");	
		return;
	}
	
	Pot_tcon_read(device,&tcon_reg);
	
	switch (c) {
		// Resistor 0 Hardware Configuration 
		case 'H':
			mask = MCP41HV51_TCON_R0HW;
			break;
		// terminal A
		case 'A':
			mask = MCP41HV51_TCON_R0A;
			break;
		case 'W':
			mask = MCP41HV51_TCON_R0W;
			break;
		// terminal B
		case 'B':
			mask = MCP41HV51_TCON_R0B;
			break;
		default:
			uart2_transmit("tc:error_format\r\n");	
			return;
	}
	
	if (s == 1) {
		tcon_reg |= mask;
	} else {
		tcon_reg &= ~mask;
	}
	Pot_tcon_write(device,tcon_reg);
	uart2_transmit("tc:ok\r\n");	
	return;
	
}

typedef struct {
	char chCommand[2];
	void (*Func)(uint8_t *);
} CMD3;

static const CMD3 Cmds3[] = {
	{ "TY", TY_Function },
	{ "WS", WS_Function }, 
	{ "WG", WG_Function }, 
	{ "WI", WI_Function }, 
	{ "WD", WD_Function },
	{ "TS", TS_Function }, 
	{ "TG", TG_Function },
	{ "TC", TC_Function },
	{ "RS", TC_Function },
};


uint8_t UART2_parser(void) {
	uint8_t i;
	uint8_t result = 1;
	
	if ( !uart2_recieved) {
		return result;
	}

	if (uart2_rx_buffer[2] == ':') {
		for (i = 0; i < (sizeof(Cmds3) / sizeof(CMD3)); i++) {
			if (!strncmp((char*)&uart2_rx_buffer[0], Cmds3[i].chCommand, 2)) {
				if (Cmds3[i].Func) {
					Cmds3[i].Func(&uart2_rx_buffer[0]);
					result = 0;
				}
			}
			
		}
		result = 2;
	
	} 
	uart2_recieved = 0;
	uart2_rx_index = 0;
	
	return result;	

}
