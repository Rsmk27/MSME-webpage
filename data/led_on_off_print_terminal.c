#include "stm32f4xx.h"

void delayMS(int n);
void USART2_init(void);
void USART2_write(char ch);
void USART2_print(char *str);

int main(void) {
  /* Enable clocks */
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // GPIOA clock
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // USART2 clock

  /* PA5 as output (LED) */
  GPIOA->MODER &= ~GPIO_MODER_MODER5_Msk;
  GPIOA->MODER |= GPIO_MODER_MODER5_0;

  /* USART2 init */
  USART2_init();

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
  GPIOA->MODER |= GPIO_MODER_MODER2_1; // PA2 alternate function
  GPIOA->AFR[0] |= (GPIO_AFRL_AFSEL2_0 | GPIO_AFRL_AFSEL2_1 |
                    GPIO_AFRL_AFSEL2_2); // AF7 for USART2

  USART2->BRR = 0x0683;        // 9600 baud @16MHz
  USART2->CR1 = USART_CR1_TE;  // Enable TX
  USART2->CR1 |= USART_CR1_UE; // Enable USART
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

/* Delay function using SysTick timer */
void delayMS(int n) {
  /* Configure SysTick to generate 1ms delay
   * Default clock is 16MHz HSI */
  SysTick->LOAD = 16000 - 1;
  SysTick->VAL = 0;
  SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_ENABLE_Msk); /* Enable SysTick, internal clock,
                                                no interrupt */

  for (int i = 0; i < n; i++) {
    /* Wait until COUNTFLAG is set */
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
      ;
  }

  /* Disable SysTick */
  SysTick->CTRL = 0;
}
