#include "uart_driver.h"

#define UART_BUFFER_SIZE 1024

#define APB1_BUS_ADDR 0x40000000UL
#define AHB1_BUS_ADDR (0x40020000UL)

#define AHB1_RCC_ADDR (AHB1_BUS_ADDR + 0x3800UL)
#define AHB1_DMA1_ADDR (AHB1_BUS_ADDR + 0x6000UL)
#define USART2_PERIPH_ADDR (APB1_BUS_ADDR + 0x4400UL)

#define RCC_AHB1ENR *((volatile uint32_t *)(AHB1_RCC_ADDR + 0x30))
#define RCC_APB1ENR *((volatile uint32_t *)(AHB1_RCC_ADDR + 0x40))
#define GPIOA_MODER_ADDR *((volatile uint32_t *)(AHB1_BUS_ADDR))
#define GPIOA_AFRL *((volatile uint32_t *)(AHB1_BUS_ADDR + 0x20))

#define DMA1_S5CR *((volatile uint32_t *)(AHB1_DMA1_ADDR + 0x10 + (0x18 * 5)))
#define DMA1_S5NDTR *((volatile uint32_t *)(AHB1_DMA1_ADDR + 0x14 + (0x18 * 5)))
#define DMA1_S5PAR *((volatile uint32_t *)(AHB1_DMA1_ADDR + 0x18 + (0x18 * 5)))
#define DMA1_S5M0AR *((volatile uint32_t *)(AHB1_DMA1_ADDR + 0x1C + (0x18 * 5)))

#define USART2_DR_ADDR (USART2_PERIPH_ADDR + 0x04)
#define USART2_CR1 *((volatile uint32_t *)(USART2_PERIPH_ADDR + 0x0C))

#define USART2_BRR *((volatile uint32_t *)(USART2_PERIPH_ADDR + 0x08))

#define USART2_CR3 *((volatile uint32_t *)(USART2_PERIPH_ADDR + 0x14))

static uint8_t rx_buffer[UART_BUFFER_SIZE];

dma_info_t uart_dma = {
    .buffer = rx_buffer,
    .size = UART_BUFFER_SIZE,
    .head = 0,
    .tail = 0};

void uart_init(void)
{
  RCC_AHB1ENR |= (0b1 << 21); // DMA1 Enable
  RCC_AHB1ENR |= (0b1 << 0);  // GPIOA Enable
  RCC_APB1ENR |= (0b1 << 17); // USART2 Enable

  GPIOA_MODER_ADDR |= (0b10 << 6); // GPIOA PA3 Alternate Function Setting
  GPIOA_AFRL |= (0b111 << 12);     // GPIOA PA3 to UART Function Setting

  /**
   * Settings:
   * [Name][Ref[Bits]]:[Selection],[Selection Explanation]
   * Channel Select(CHSEL[3]): 4), Channel 4
   * Memory Data Size(MSIZE[2]): 1, Byte
   * Memory Increment Mode(MINC[1]): 1, Mem address pointer incremeneted according to MSIZE
   * Circular Mode(CIRC[1]): 1, ON
   * Stream Enable (EN[1]): 1, ON
   */

  DMA1_S5CR = (uint32_t)(0x0);
  DMA1_S5NDTR = (uint32_t)(UART_BUFFER_SIZE);
  DMA1_S5PAR = (uint32_t)(USART2_DR_ADDR);
  DMA1_S5M0AR = (uint32_t)(rx_buffer);
  DMA1_S5CR = (0b100 << 25) | (0b1 << 10) | (0b1 << 8) | (0b1 << 0);

  /**
   * Set BRR to 115,200 baud rate, f_clk/target baud rate.
   *  16 MHz/115,200 = 138.888
   *  Mantissa = 138 = 0x8A
   *  Fractional = 0.888 = 16*0.888 = ~14 = 0x8
   */
  USART2_BRR = (0x8A << 4) | (0xE << 0);
  USART2_CR3 = (1 << 6);

  // Clear and enable UART after configuring, otherwise it will lead to it initially having the wrong settings
  USART2_CR1 = (uint32_t)(0);
  USART2_CR1 = (1 << 13) | (1 << 2) | (1 << 3);
}