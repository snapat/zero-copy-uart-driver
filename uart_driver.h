#ifndef UART_DRIVER_H
#define UART_DRIVER_H
#include "ring_buffer.h"

extern dma_info_t uart_dma;

void uart_init(void);
uint32_t uart_data_available(void);
uint8_t uart_read_byte(void);
uint8_t uart_write_byte(int8_t byte);

#endif