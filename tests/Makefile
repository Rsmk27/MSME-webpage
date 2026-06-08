CC=gcc
CFLAGS=-I.

test:
	sed 's/while (1)/if (1) { loop_entered = 1; longjmp(test_env, 1); } while (0)/g' ../data/user_switch.c | sed 's/int main/int original_main/g' > user_switch_tested.c
	$(CC) $(CFLAGS) -o test_user_switch test_user_switch.c user_switch_tested.c
	./test_user_switch
	sed 's/int main(void)/int original_main(void)/g' ../data/led_on_off_print_terminal.c | sed 's/void USART2_write(char ch)/void original_USART2_write(char ch)/g' > led_tested.c
	$(CC) $(CFLAGS) -o test_usart2 test_usart2_print.c led_tested.c
	./test_usart2
	sed 's/int main(void)/int original_main(void)/g' ../data/led_on_off_print_terminal.c > led_write_tested.c
	$(CC) $(CFLAGS) -o test_usart2_write test_usart2_write.c led_write_tested.c
	./test_usart2_write

clean:
	rm -f test_user_switch user_switch_tested.c test_usart2 led_tested.c test_usart2_write led_write_tested.c
	sed 's/int main(void)/int original_main(void)/g' ../data/led_on_off_print_terminal.c | sed 's/while ((SysTick->CTRL & 0x10000) == 0)/while (mock_systick_check())/g' | sed '1i int mock_systick_check(void);' > led_delay_tested.c
	$(CC) $(CFLAGS) -o test_delay test_delay.c led_delay_tested.c
	./test_delay

clean:
	rm -f test_user_switch user_switch_tested.c test_usart2 led_tested.c test_delay led_delay_tested.c
