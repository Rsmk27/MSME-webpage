#include <stdio.h>
#include <assert.h>
#include <stdint.h>
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

extern volatile uint32_t msTicks;
extern void SysTick_Handler(void);

int main() {
    printf("Starting SysTick_Handler test...\n");

    msTicks = 0;
    SysTick_Handler();
    assert(msTicks == 1);

    msTicks = 42;
    SysTick_Handler();
    assert(msTicks == 43);

    // Test overflow
    msTicks = 0xFFFFFFFF;
    SysTick_Handler();
    assert(msTicks == 0);

    printf("SysTick_Handler test passed!\n");
    return 0;
}
