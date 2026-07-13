#include "stm32f4xx.h"

volatile uint32_t msTicks = 0;

void SysTick_Handler(void) { msTicks++; }

void SysTick_Init(void) {
  /* Configure SysTick to generate 1ms interrupts
   * Default clock is 16MHz HSI */
  SysTick->LOAD = 16000 - 1;
  SysTick->VAL = 0;
  SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk); /* Enable SysTick, internal clock, enable interrupt */
}

void delayMS(int n);
void USART2_init(void);
void USART2_write(char ch);
void USART2_print(char *str);


#define GPIO_MODER_MODER2_1   0x00000020
#define GPIO_AFRL_AFSEL2_AF7  0x00000700
#define USART_BRR_9600_16MHZ  0x00000683
#define USART_CR1_TE          0x00000008
#define USART_CR1_UE          0x00002000

int main(void) {
  /* Enable clocks */
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // GPIOA clock
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // USART2 clock

  /* PA5 as output (LED) */
  GPIOA->MODER &= ~GPIO_MODER_MODER5_Msk;
  GPIOA->MODER |= GPIO_MODER_MODER5_0;

  /* USART2 init */
  USART2_init();

  /* SysTick init */
  SysTick_Init();

  while (1) {
    GPIOA->ODR |= GPIO_ODR_OD5; // LED ON
    USART2_print("LED is ON\r\n");
    delayMS(500);

    GPIOA->ODR &= ~GPIO_ODR_OD5; // LED OFF
    USART2_print("LED is OFF\r\n");
    delayMS(500);
  }
}

/* USART2 initialization (PA2 = TX) */
void USART2_init(void) {
  GPIOA->MODER |= GPIO_MODER_MODER2_1;    // PA2 alternate function
  GPIOA->AFR[0] |= GPIO_AFRL_AFSEL2_AF7;  // AF7 for USART2

  USART2->BRR = USART_BRR_9600_16MHZ; // 9600 baud @16MHz
  USART2->CR1 = USART_CR1_TE;         // Enable TX
  USART2->CR1 |= USART_CR1_UE;        // Enable USART
}

/* Send one character */
void USART2_write(char ch) {
  while (!(USART2->SR & USART_SR_TXE))
    ;
  USART2->DR = ch;
}

/* Send string */
void USART2_print(char *str) {
  while (*str) {
    USART2_write(*str++);
  }
}

/* Delay function using SysTick interrupt */
void delayMS(int n) {
  uint32_t startTicks = msTicks;
  while ((msTicks - startTicks) < (uint32_t)n) {
#ifdef __arm__
    __asm volatile("wfi");
#endif
  }
}
