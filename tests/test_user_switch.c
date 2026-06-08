#include "main.h"
#include <assert.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

int disable_irq_called = 0;
int loop_entered = 0;
int read_pin_called = 0;
int write_pin_called = 0;

jmp_buf test_env;

// Mock __disable_irq
void __disable_irq(void) { disable_irq_called = 1; }

// Mocks for HAL functions to allow compilation
void HAL_Init(void) {}
int HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct) { return HAL_OK; }
int HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, int FLatency) {
  return HAL_OK;
}
int HAL_USART_Init(USART_HandleTypeDef *husart) { return HAL_OK; }
void HAL_GPIO_Init(int GPIOx, GPIO_InitTypeDef *GPIO_Init) {}

void HAL_GPIO_WritePin(int GPIOx, int GPIO_Pin, int PinState) {
  write_pin_called++;
}

int HAL_GPIO_ReadPin(int GPIOx, int GPIO_Pin) {
  read_pin_called++;
  return GPIO_PIN_RESET; // Simulate button pressed
}

// Test the Error_Handler function
void test_error_handler(void) {
  printf("Starting Error_Handler test...\n");
  disable_irq_called = 0;
  loop_entered = 0;

  if (setjmp(test_env) == 0) {
    Error_Handler();
  }

  // Assertions
  assert(disable_irq_called == 1);
  assert(loop_entered == 1);
  printf("Error_Handler test passed!\n");
}

void test_hal_gpio_exti_callback(void) {
  printf("Starting HAL_GPIO_EXTI_Callback test...\n");

  // Test with incorrect pin
  read_pin_called = 0;
  write_pin_called = 0;
  HAL_GPIO_EXTI_Callback(GPIO_PIN_5);
  assert(read_pin_called == 0);
  assert(write_pin_called == 0);

  // Test with correct pin
  read_pin_called = 0;
  write_pin_called = 0;
  HAL_GPIO_EXTI_Callback(GPIO_PIN_13);
  assert(read_pin_called == 1);
  assert(write_pin_called == 1);

  printf("HAL_GPIO_EXTI_Callback test passed!\n");
}

int main(void) {
  test_error_handler();
  test_hal_gpio_exti_callback();

  printf("All user_switch tests passed!\n");
  return 0;
}

void __WFI(void) {}
void HAL_NVIC_SetPriority(int IRQn, int PreemptPriority, int SubPriority) {}
void HAL_NVIC_EnableIRQ(int IRQn) {}
void HAL_GPIO_EXTI_IRQHandler(int GPIO_Pin) {}
