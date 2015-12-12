#include "stm32f0xx_hal.h"
#include "uart.h"
#include "string.h"

static UART_HandleTypeDef* huart2 = NULL;

uint8_t uart2_tx_buffer[TX_BUFFER_SIZE] = {0};
uint8_t uart2_rx_buffer[TX_BUFFER_SIZE] = {0};

uint8_t uart2_recieved = 0;

uint8_t uart2_rx_index =0;
uint8_t uart2_rx_byte =0;


void uart2_transmit(char* string) {	
	HAL_UART_Transmit_DMA(huart2,(uint8_t*)string,strlen(string));
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART2) {
		
		 __HAL_UART_FLUSH_DRREGISTER(huart2);
		
		if ( uart2_rx_index < TX_BUFFER_SIZE-1 ) {
			uart2_rx_buffer[uart2_rx_index++] = uart2_rx_byte;
			
		} else {
			uart2_rx_index =0;
			return;
		}
		
		if (uart2_rx_buffer[uart2_rx_index -1] == '\n' && 
			uart2_rx_buffer[uart2_rx_index -2] == '\r' ) {
			uart2_rx_buffer[uart2_rx_index] = '\0';	
			uart2_recieved =1;
		}
		
		
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	// nothing to do at the moment
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
	// nothing to do at the moment
}


void uart2_start(UART_HandleTypeDef *huart) {
	huart2 = huart;
	__HAL_UART_FLUSH_DRREGISTER(huart);
	HAL_UART_Receive_DMA(huart, &uart2_rx_byte, 1);
}


