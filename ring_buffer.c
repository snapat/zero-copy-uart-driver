#include <stdint.h>
#include "ring_buffer.h"

int get_count(dma_info_t *dma)
{
  if (dma->head >= dma->tail)
  {
    return dma->head - dma->tail;
  }
  else
  {
    return (dma->size - dma->tail) + dma->head;
  }
}

void advance(dma_info_t *dma, uint32_t len)
{
  dma->tail += len;
  dma->tail %= dma->size;
}
