#include <stdio.h>
#include <assert.h>
#include "ring_buffer.h"

extern int get_count(dma_info_t *y);
extern int advance(dma_info_t *z, uint8_t a);

int main(void)
{
  const int size1 = 10;
  uint8_t memory[size1];

  dma_info_t dma = {
      dma.buffer = memory,
      dma.size = size1,
      dma.head = 5,
      dma.tail = 0};

  int count_test = get_count(&dma);
  printf("Before Advance Count Test: %i\n", count_test);
  assert(count_test == 5);

  advance(&dma, 2);
  printf("After Advance, tail = %i\n", dma.tail);
  assert(dma.tail == 2);

  dma.tail = 8;
  dma.head = 1;
  assert(get_count(&dma) == 3);
  if (get_count(&dma) == 3)
  {
    printf("Wrap-around condition passed");
  }
};
