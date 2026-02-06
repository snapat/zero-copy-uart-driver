#include <stdio.h>
#include <assert.h>
#include "ring_buffer.h"
#include "uart_driver.h"

extern int get_count(dma_info_t *dma);
extern int advance(dma_info_t *dma, uint32_t len);

volatile uint8_t received_data = 0;
volatile uint32_t bytes_processed = 0;

int main(void)
{
  uart_init();
  uint8_t tx_byte = 'A';
  while (1)
  {
    UART_write_byte(tx_byte);
    tx_byte++;
    if (tx_byte > 'Z')
    {
      tx_byte = 'A';
    }

    if (uart_data_available > 0)
    {
      received_data = uart_read_byte();
      bytes_processed++;
    }
    for (volatile int i = 0; i < 4000000; i++)
      ;
  }
};
