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
extern void delayMS(int n);

// Counter to simulate hardware waiting
int systick_wait_counter = 0;
int systick_check_calls = 0;
int total_systick_flags = 0;

// This function will replace ((SysTick->CTRL & 0x10000) == 0)
// It returns 1 to simulate "COUNTFLAG is not set" (stay in loop)
// It returns 0 to simulate "COUNTFLAG is set" (exit loop)
int mock_systick_check(void) {
    systick_check_calls++;
    if (systick_wait_counter++ > 3) {
        // After 4 checks, simulate the flag being set
        systick_wait_counter = 0;
        total_systick_flags++;
        return 0; // Break the while loop
    }
    return 1; // Stay in the while loop
}

int main() {
    printf("Starting delayMS test...\n");

    // Reset mocks
    SysTick->LOAD = 0;
    SysTick->VAL = 0xFFFFFFFF;
    SysTick->CTRL = 0;

    systick_wait_counter = 0;
    systick_check_calls = 0;
    total_systick_flags = 0;

    // Test a 2ms delay
    delayMS(2);

    // Verify registers were configured correctly
    assert(SysTick->LOAD == 16000 - 1);
    assert(SysTick->VAL == 0);
    // After delayMS is done, it should disable SysTick
    assert(SysTick->CTRL == 0);

    // Verify our simulation fired twice for 2ms
    assert(total_systick_flags == 2);
    // Should be 5 calls per ms (4 waits + 1 flag), total 10 calls
    assert(systick_check_calls == 10);

    // Test a 5ms delay
    systick_wait_counter = 0;
    systick_check_calls = 0;
    total_systick_flags = 0;

    delayMS(5);

    assert(total_systick_flags == 5);
    assert(systick_check_calls == 25);

    printf("delayMS test passed!\n");
    return 0;
}
