#ifndef RING_BUFFER_H
#define RING_BUFFER_H
#include <stdint.h>

typedef struct
{
  uint8_t *buffer;
  uint32_t size;
  volatile uint32_t head;
  uint32_t tail;
} dma_info_t;

#endif