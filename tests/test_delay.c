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
extern volatile uint32_t msTicks;

// Counter to simulate hardware waiting
int systick_wait_counter = 0;
int systick_check_calls = 0;
int total_systick_flags = 0;

// This function replaces the condition: ((msTicks - startTicks) < (uint32_t)n)
// We use this to artificially increment msTicks to simulate interrupt
int mock_systick_check(int n, uint32_t startTicks) {
    systick_check_calls++;

    // Simulate some waiting before the interrupt fires
    if (systick_wait_counter++ > 3) {
        systick_wait_counter = 0;
        msTicks++; // Simulate interrupt firing
        total_systick_flags++;
    }

    // Original condition
    return ((msTicks - startTicks) < (uint32_t)n);
}

int main() {
    printf("Starting delayMS test...\n");

    // Reset mocks
    SysTick->LOAD = 0;
    SysTick->VAL = 0xFFFFFFFF;
    SysTick->CTRL = 0;
    msTicks = 0;

    systick_wait_counter = 0;
    systick_check_calls = 0;
    total_systick_flags = 0;

    // Test a 2ms delay
    delayMS(2);

    // Verify registers were configured correctly?
    // Actually the new code doesn't modify SysTick->LOAD inside delayMS anymore,
    // so we don't test for it here if the user's intent is to move init to main.
    // Wait, the prompt says: "Can be optimized by using WFI in a timer interrupt rather than busy-waiting for the timer flag. However, it requires modifying how delay is handled globally."
    // And in my changed led_on_off_print_terminal.c, SysTick_Init configures SysTick with interrupt.
    // Let's just check the simulated time passed correctly.
    assert(msTicks == 2);
    // 5 checks per ms tick
    assert(systick_check_calls == 10);
    assert(total_systick_flags == 2);

    // Test a 5ms delay
    systick_wait_counter = 0;
    systick_check_calls = 0;
    total_systick_flags = 0;

    delayMS(5);

    assert(msTicks == 7);
    assert(systick_check_calls == 25);
    assert(total_systick_flags == 5);

    printf("delayMS test passed!\n");
    return 0;
}
