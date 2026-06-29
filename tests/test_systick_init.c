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
extern void SysTick_Init(void);

int main() {
    printf("Starting SysTick_Init test...\n");

    // Reset mocks
    SysTick->LOAD = 0;
    SysTick->VAL = 0xFFFFFFFF;
    SysTick->CTRL = 0;

    // Call function
    SysTick_Init();

    // Verify registers were configured correctly
    assert(SysTick->LOAD == 16000 - 1);
    assert(SysTick->VAL == 0);
    assert(SysTick->CTRL == (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk));

    printf("SysTick_Init test passed!\n");
    return 0;
}
