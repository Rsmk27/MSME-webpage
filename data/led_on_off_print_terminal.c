#include "stm32f4xx.h"

void delayMS(int n);
void USART2_init(void);
void USART2_write(char ch);
void USART2_print(char *str);

int main(void)
{
    /* Enable clocks */
    RCC->AHB1ENR |= 1;        // GPIOA clock
    RCC->APB1ENR |= 0x20000;  // USART2 clock

    /* PA5 as output (LED) */
    GPIOA->MODER &= ~0x00000C00;
    GPIOA->MODER |=  0x00000400;

    /* USART2 init */
    USART2_init();

    while(1)
    {
        GPIOA->ODR |= 0x20;   // LED ON
        USART2_print("LED is ON\r\n");
        delayMS(500);

        GPIOA->ODR &= ~0x20;  // LED OFF
        USART2_print("LED is OFF\r\n");
        delayMS(500);
    }
}

/* USART2 initialization (PA2 = TX) */
void USART2_init(void)
{
    GPIOA->MODER |= 0x20;     // PA2 alternate function
    GPIOA->AFR[0] |= 0x0700;  // AF7 for USART2

    USART2->BRR = 0x0683;     // 9600 baud @16MHz
    USART2->CR1 = 0x0008;     // Enable TX
    USART2->CR1 |= 0x2000;    // Enable USART
}

/* Send one character */
void USART2_write(char ch)
{
    while(!(USART2->SR & 0x80));
    USART2->DR = ch;
}

/* Send string */
void USART2_print(char *str)
{
    while(*str)
    {
        USART2_write(*str++);
    }
}

/* Delay function */
void delayMS(int n)
{
    for(; n > 0; n--)
        for(int i = 0; i < 3195; i++);
}
