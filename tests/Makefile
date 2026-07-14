CC=gcc
CFLAGS=-I.

test:
	sed 's/while (1)/if (1) { loop_entered = 1; longjmp(test_env, 1); } while (0)/g' ../data/user_switch.c | sed 's/int main/int original_main/g' | sed 's/static void MX_GPIO_Init/void MX_GPIO_Init/g' | sed 's/static void MX_USART2_Init/void MX_USART2_Init/g' > user_switch_tested.c
	$(CC) $(CFLAGS) -o test_user_switch test_user_switch.c user_switch_tested.c
	./test_user_switch
	sed 's/int main(void)/int original_main(void)/g' ../data/led_on_off_print_terminal.c | sed 's/void USART2_write(char ch)/void original_USART2_write(char ch)/g' > led_tested.c
	$(CC) $(CFLAGS) -o test_usart2 test_usart2_print.c led_tested.c
	./test_usart2
	sed 's/int main(void)/int original_main(void)/g' ../data/led_on_off_print_terminal.c > led_write_tested.c
	$(CC) $(CFLAGS) -o test_usart2_write test_usart2_write.c led_write_tested.c
	./test_usart2_write
	sed 's/int main(void)/int original_main(void)/g' ../data/led_on_off_print_terminal.c | sed 's/while ((msTicks - startTicks) < (uint32_t)n)/while (mock_systick_check(n, startTicks))/g' | sed '1i #include <stdint.h>\nint mock_systick_check(int n, uint32_t startTicks);' > led_delay_tested.c
	$(CC) $(CFLAGS) -o test_delay test_delay.c led_delay_tested.c
	./test_delay
	sed 's/int main(void)/int original_main(void)/g' ../data/led_on_off_print_terminal.c > led_systick_tested.c
	$(CC) $(CFLAGS) -o test_systick_handler test_systick_handler.c led_systick_tested.c
	./test_systick_handler

	sed 's/int main(void)/int original_main(void)/g' ../data/led_on_off_print_terminal.c > led_systick_tested.c
	$(CC) $(CFLAGS) -o test_systick_init test_systick_init.c led_systick_tested.c
	./test_systick_init

clean:
	rm -f test_user_switch user_switch_tested.c test_usart2 led_tested.c test_usart2_write led_write_tested.c test_delay led_delay_tested.c test_systick_handler led_systick_tested.c test_systick_init
