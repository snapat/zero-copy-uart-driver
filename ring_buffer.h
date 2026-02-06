#ifndef RING_BUFFER_H
#define RING_BUFFER_H
#include <stdint.h>

int get_count(dma_info_t *dma);
void advance(dma_info_t *dma, uint32_t len);

typedef struct
{
  uint8_t *buffer;
  uint32_t size;
  volatile uint32_t head;
  uint32_t tail;
} dma_info_t;

#endif