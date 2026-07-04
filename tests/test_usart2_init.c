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
extern void USART2_init(void);

int main() {
    printf("Starting USART2_init test...\n");

    // Initialize mock registers to 0
    GPIOA->MODER = 0;
    GPIOA->AFR[0] = 0;
    USART2->BRR = 0;
    USART2->CR1 = 0;

    USART2_init();

    // Verify GPIOA MODER (PA2 alternate function)
    // GPIO_MODER_MODER2_1 is 0x20
    assert((GPIOA->MODER & 0x00000020) == 0x00000020);

    // Verify GPIOA AFR[0] (AF7 for USART2)
    // GPIO_AFRL_AFSEL2_AF7 is 0x700
    assert((GPIOA->AFR[0] & 0x00000700) == 0x00000700);

    // Verify USART2 BRR (9600 baud @16MHz)
    assert(USART2->BRR == 0x00000683);

    // Verify USART2 CR1 (TX and USART enabled)
    // TE = 0x8, UE = 0x2000
    assert((USART2->CR1 & 0x00002008) == 0x00002008);

    printf("USART2_init test passed!\n");

    return 0;
}
