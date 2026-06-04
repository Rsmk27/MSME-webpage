#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <assert.h>
#include "main.h"

int disable_irq_called = 0;
int loop_entered = 0;
jmp_buf test_env;

// Mock __disable_irq
void __disable_irq(void) {
    disable_irq_called = 1;
}

// Mocks for HAL functions to allow compilation
void HAL_Init(void) {}
int HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct) { return HAL_OK; }
int HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, int FLatency) { return HAL_OK; }
int HAL_USART_Init(USART_HandleTypeDef *husart) { return HAL_OK; }
void HAL_GPIO_Init(int GPIOx, GPIO_InitTypeDef *GPIO_Init) {}
void HAL_GPIO_WritePin(int GPIOx, int GPIO_Pin, int PinState) {}
int HAL_GPIO_ReadPin(int GPIOx, int GPIO_Pin) { return 0; }

// Test the Error_Handler function
int main(void) {
    printf("Starting Error_Handler test...\n");

    if (setjmp(test_env) == 0) {
        Error_Handler();
    }

    // Assertions
    assert(disable_irq_called == 1);
    assert(loop_entered == 1);

    printf("All tests passed!\n");
    return 0;
}
void __WFI(void) {}
void HAL_NVIC_SetPriority(int IRQn, int PreemptPriority, int SubPriority) {}
void HAL_NVIC_EnableIRQ(int IRQn) {}
void HAL_GPIO_EXTI_IRQHandler(int GPIO_Pin) {}
