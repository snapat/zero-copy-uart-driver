#ifndef UART_DRIVER_H
#define UART_DRIVER_H
#include "ring_buffer.h"

extern dma_info_t uart_dma;

void uart_init(void);

#endif