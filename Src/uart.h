
#ifndef UART_H
#define UART_H

#define TX_BUFFER_SIZE 128
#define RX_BUFFER_SIZE 128

extern uint8_t uart2_tx_buffer[TX_BUFFER_SIZE];
extern uint8_t uart2_rx_buffer[TX_BUFFER_SIZE];

extern uint8_t uart2_recieved;

extern uint8_t uart2_rx_index;
extern uint8_t uart2_rx_byte;


void uart2_start(UART_HandleTypeDef *huart);


void uart2_transmit(char* string);



#endif
