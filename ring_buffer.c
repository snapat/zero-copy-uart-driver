#include <stdint.h>
#include "ring_buffer.h"

int get_count(dma_info_t *dma)
{
  uint32_t head = dma->head;
  uint32_t tail = dma->tail;
  uint32_t size = dma->size;
  if (head >= tail)
  {
    return head - tail;
  }
  else
  {
    return (size - tail) + head;
  }
}

void advance(dma_info_t *dma, uint32_t len)
{

  dma->tail += len;
  dma->tail %= dma->size;
}
