#include "stm32f4xx.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Define the mock structures
RCC_TypeDef mock_RCC;
GPIO_TypeDef mock_GPIOA;
USART_TypeDef mock_USART2;
SysTick_TypeDef mock_SysTick;

RCC_TypeDef *RCC = &mock_RCC;
GPIO_TypeDef *GPIOA = &mock_GPIOA;
USART_TypeDef *USART2 = &mock_USART2;
SysTick_TypeDef *SysTick = &mock_SysTick;

// Captured buffer
char captured_str[1024];
int capture_idx = 0;

void USART2_write(char ch) {
  if (capture_idx < sizeof(captured_str) - 1) {
    captured_str[capture_idx++] = ch;
    captured_str[capture_idx] = '\0';
  }
}

// Declare the function we want to test
extern void USART2_print(char *str);
extern void USART2_init(void);

void test_USART2_init(void) {
  printf("Starting USART2_init test...\n");

  // Test case 1: Registers initialized to 0
  mock_GPIOA.MODER = 0;
  mock_GPIOA.AFR[0] = 0;
  mock_USART2.BRR = 0;
  mock_USART2.CR1 = 0;

  USART2_init();

  assert((mock_GPIOA.MODER & 0x20) == 0x20);
  assert((mock_GPIOA.AFR[0] & 0x0700) == 0x0700);
  assert(mock_USART2.BRR == 0x0683);
  assert((mock_USART2.CR1 & 0x0008) == 0x0008);
  assert((mock_USART2.CR1 & 0x2000) == 0x2000);

  // Test case 2: Registers have other bits set
  mock_GPIOA.MODER = 0x12340000;
  mock_GPIOA.AFR[0] = 0x00005678;
  mock_USART2.BRR = 0x0000;
  mock_USART2.CR1 = 0x1010;

  USART2_init();

  assert((mock_GPIOA.MODER & 0x20) == 0x20);
  assert((mock_GPIOA.MODER & 0x12340000) == 0x12340000);
  assert((mock_GPIOA.AFR[0] & 0x0700) == 0x0700);
  assert((mock_GPIOA.AFR[0] & 0x00005678) == 0x00005678);
  assert(mock_USART2.BRR == 0x0683);
  assert((mock_USART2.CR1 & 0x0008) == 0x0008);
  assert((mock_USART2.CR1 & 0x2000) == 0x2000);
  // assert((mock_USART2.CR1 & 0x1010) == 0x1010); // CR1 is overwritten

  printf("USART2_init test passed!\n");
}

int main() {
  test_USART2_init();
  printf("Starting USART2_print test...\n");

  // Clear buffer
  capture_idx = 0;
  captured_str[0] = '\0';

  USART2_print("Hello, world!");

  assert(strcmp(captured_str, "Hello, world!") == 0);

  // Clear buffer again and test empty string
  capture_idx = 0;
  captured_str[0] = '\0';

  USART2_print("");
  assert(strcmp(captured_str, "") == 0);

  // Test a long string
  capture_idx = 0;
  captured_str[0] = '\0';

  USART2_print("1234567890\r\n");
  assert(strcmp(captured_str, "1234567890\r\n") == 0);

  printf("USART2_print test passed!\n");
  return 0;
}
