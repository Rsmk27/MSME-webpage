#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <assert.h>
#include "main.h"

int exti_irq_handler_called = 0;
int exti_irq_handler_pin = 0;

int disable_irq_called = 0;
int loop_entered = 0;
jmp_buf test_env;

// Mocks
void __disable_irq(void) {}
void HAL_Init(void) {}
int HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct) { return HAL_OK; }
int HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, int FLatency) { return HAL_OK; }
int HAL_USART_Init(USART_HandleTypeDef *husart) { return HAL_OK; }
void HAL_GPIO_Init(int GPIOx, GPIO_InitTypeDef *GPIO_Init) {}
void HAL_GPIO_WritePin(int GPIOx, int GPIO_Pin, int PinState) {}
int HAL_GPIO_ReadPin(int GPIOx, int GPIO_Pin) { return 0; }
void __WFI(void) {}
void HAL_NVIC_SetPriority(int IRQn, int PreemptPriority, int SubPriority) {}
void HAL_NVIC_EnableIRQ(int IRQn) {}

void HAL_GPIO_EXTI_IRQHandler(int GPIO_Pin) {
    exti_irq_handler_called = 1;
    exti_irq_handler_pin = GPIO_Pin;
}

void EXTI15_10_IRQHandler(void);

int main(void) {
    printf("Starting EXTI15_10_IRQHandler test...\n");

    EXTI15_10_IRQHandler();

    assert(exti_irq_handler_called == 1);
    assert(exti_irq_handler_pin == GPIO_PIN_13);

    printf("EXTI15_10_IRQHandler test passed!\n");
    return 0;
}
