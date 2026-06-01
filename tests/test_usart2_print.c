#include <stdio.h>
#include <string.h>
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

// Captured buffer
char captured_str[1024];
int capture_idx = 0;

void USART2_write(char ch) {
    if (capture_idx < sizeof(captured_str) - 1) {
        captured_str[capture_idx++] = ch;
        captured_str[capture_idx] = '\0';
    }
}

void clear_buffer(void) {
    capture_idx = 0;
    captured_str[0] = '\0';
}

// Declare the function we want to test
extern void USART2_print(char *str);

int main() {
    printf("Starting USART2_print test...\n");

    // Clear buffer
    clear_buffer();

    USART2_print("Hello, world!");

    assert(strcmp(captured_str, "Hello, world!") == 0);

    // Clear buffer again and test empty string
    clear_buffer();

    USART2_print("");
    assert(strcmp(captured_str, "") == 0);

    // Test a long string
    clear_buffer();

    USART2_print("1234567890\r\n");
    assert(strcmp(captured_str, "1234567890\r\n") == 0);

    printf("USART2_print test passed!\n");
    return 0;
}
