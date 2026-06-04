#include <stdio.h>
#include <assert.h>
#include "stm32f4xx.h"

// Define the mock structures
RCC_TypeDef mock_RCC;
GPIO_TypeDef mock_GPIOA;
USART_TypeDef mock_USART2;
SysTick_TypeDef mock_SysTick;

RCC_TypeDef *RCC = &mock_RCC;
GPIO_TypeDef *GPIOA = &mock_GPIOA;
USART_TypeDef *USART2 = &mock_USART2;
SysTick_TypeDef *SysTick = &mock_SysTick;

// Declare the function we want to test
extern void USART2_write(char ch);

int main() {
    printf("Starting USART2_write test...\n");

    // Ensure the bit 0x80 is set in SR so it doesn't block
    USART2->SR |= 0x80;

    USART2->DR = 0;
    USART2_write('A');
    assert(USART2->DR == 'A');

    USART2->DR = 0;
    USART2_write('\n');
    assert(USART2->DR == '\n');

    printf("USART2_write test passed!\n");

    return 0;
}
