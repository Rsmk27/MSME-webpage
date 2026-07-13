#include "main.h"
#include <assert.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

int disable_irq_called = 0;
int loop_entered = 0;
int read_pin_called = 0;
int write_pin_called = 0;
int mock_osc_config_return = HAL_OK;
int mock_clock_config_return = HAL_OK;

jmp_buf test_env;

int rcc_gpioc_clk_enable_called = 0;
int rcc_gpioh_clk_enable_called = 0;
int rcc_gpioa_clk_enable_called = 0;
int rcc_gpiob_clk_enable_called = 0;

int hal_gpio_init_called = 0;
int last_gpio_init_port = 0;
GPIO_InitTypeDef last_gpio_init_struct;

int nvic_set_priority_called = 0;
int last_nvic_set_priority_irqn = -1;
int last_nvic_set_priority_preempt = -1;
int last_nvic_set_priority_sub = -1;

int nvic_enable_irq_called = 0;
int last_nvic_enable_irq_irqn = -1;

int hal_usart_init_called = 0;
int mock_usart_init_return = HAL_OK;
USART_HandleTypeDef last_usart_init_struct;

// Mock __disable_irq
void __disable_irq(void) { disable_irq_called = 1; }

// Mocks for HAL functions to allow compilation
void HAL_Init(void) {}
int HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct) { return mock_osc_config_return; }
int HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, int FLatency) {
  return mock_clock_config_return;
}
int HAL_USART_Init(USART_HandleTypeDef *husart) {
  hal_usart_init_called++;
  last_usart_init_struct = *husart;
  return mock_usart_init_return;
}

void HAL_GPIO_Init(int GPIOx, GPIO_InitTypeDef *GPIO_Init) {
  hal_gpio_init_called++;
  last_gpio_init_port = GPIOx;
  last_gpio_init_struct = *GPIO_Init;
}


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


void test_systemclock_config(void) {
  printf("Starting SystemClock_Config test...\n");

  // Happy path
  mock_osc_config_return = HAL_OK;
  mock_clock_config_return = HAL_OK;
  disable_irq_called = 0;
  loop_entered = 0;
  SystemClock_Config();
  assert(disable_irq_called == 0);
  assert(loop_entered == 0);

  // Error path 1: OscConfig fails
  mock_osc_config_return = HAL_ERROR;
  mock_clock_config_return = HAL_OK;
  disable_irq_called = 0;
  loop_entered = 0;
  if (setjmp(test_env) == 0) {
    SystemClock_Config();
  }
  assert(disable_irq_called == 1);
  assert(loop_entered == 1);

  // Error path 2: ClockConfig fails
  mock_osc_config_return = HAL_OK;
  mock_clock_config_return = HAL_ERROR;
  disable_irq_called = 0;
  loop_entered = 0;
  if (setjmp(test_env) == 0) {
    SystemClock_Config();
  }
  assert(disable_irq_called == 1);
  assert(loop_entered == 1);

  printf("SystemClock_Config test passed!\n");
}


void test_mx_gpio_init(void) {
  printf("Starting MX_GPIO_Init test...\n");

  // Reset counters
  rcc_gpioc_clk_enable_called = 0;
  rcc_gpioh_clk_enable_called = 0;
  rcc_gpioa_clk_enable_called = 0;
  rcc_gpiob_clk_enable_called = 0;

  hal_gpio_init_called = 0;
  write_pin_called = 0;

  nvic_set_priority_called = 0;
  nvic_enable_irq_called = 0;

  extern void MX_GPIO_Init(void);

  MX_GPIO_Init();

  // Assert clock enables
  assert(rcc_gpioc_clk_enable_called == 1);
  assert(rcc_gpioh_clk_enable_called == 1);
  assert(rcc_gpioa_clk_enable_called == 1);
  assert(rcc_gpiob_clk_enable_called == 1);

  // Assert HAL_GPIO_WritePin called once for LD2_Pin (GPIO_PIN_RESET)
  assert(write_pin_called >= 1);

  // Assert HAL_GPIO_Init called twice (for PC13 and LD2_Pin)
  assert(hal_gpio_init_called == 2);

  // Assert NVIC calls
  assert(nvic_set_priority_called == 1);
  assert(last_nvic_set_priority_irqn == EXTI15_10_IRQn);
  assert(last_nvic_set_priority_preempt == 0);
  assert(last_nvic_set_priority_sub == 0);

  assert(nvic_enable_irq_called == 1);
  assert(last_nvic_enable_irq_irqn == EXTI15_10_IRQn);

  printf("MX_GPIO_Init test passed!\n");
}


void test_mx_usart2_init(void) {
  printf("Starting MX_USART2_Init test...\n");

  extern void MX_USART2_Init(void);

  // Happy path
  hal_usart_init_called = 0;
  mock_usart_init_return = HAL_OK;
  disable_irq_called = 0;
  loop_entered = 0;

  MX_USART2_Init();

  assert(hal_usart_init_called == 1);
  assert(last_usart_init_struct.Instance == USART2);
  assert(last_usart_init_struct.Init.BaudRate == 115200);
  assert(last_usart_init_struct.Init.WordLength == USART_WORDLENGTH_8B);
  assert(last_usart_init_struct.Init.StopBits == USART_STOPBITS_1);
  assert(last_usart_init_struct.Init.Parity == USART_PARITY_NONE);
  assert(last_usart_init_struct.Init.Mode == USART_MODE_TX_RX);
  assert(last_usart_init_struct.Init.CLKPolarity == USART_POLARITY_LOW);
  assert(last_usart_init_struct.Init.CLKPhase == USART_PHASE_1EDGE);
  assert(last_usart_init_struct.Init.CLKLastBit == USART_LASTBIT_DISABLE);

  assert(disable_irq_called == 0);
  assert(loop_entered == 0);

  // Error path
  hal_usart_init_called = 0;
  mock_usart_init_return = HAL_ERROR;
  disable_irq_called = 0;
  loop_entered = 0;

  if (setjmp(test_env) == 0) {
    MX_USART2_Init();
  }

  assert(hal_usart_init_called == 1);
  assert(disable_irq_called == 1);
  assert(loop_entered == 1);

  printf("MX_USART2_Init test passed!\n");
}

int main(void) {
  test_error_handler();
  test_mx_usart2_init();
  test_systemclock_config();
  test_mx_gpio_init();
  test_hal_gpio_exti_callback();

  printf("All user_switch tests passed!\n");
  return 0;
}

void __WFI(void) {}

void HAL_NVIC_SetPriority(int IRQn, int PreemptPriority, int SubPriority) {
  nvic_set_priority_called++;
  last_nvic_set_priority_irqn = IRQn;
  last_nvic_set_priority_preempt = PreemptPriority;
  last_nvic_set_priority_sub = SubPriority;
}


void HAL_NVIC_EnableIRQ(int IRQn) {
  nvic_enable_irq_called++;
  last_nvic_enable_irq_irqn = IRQn;
}

void HAL_GPIO_EXTI_IRQHandler(int GPIO_Pin) {}
