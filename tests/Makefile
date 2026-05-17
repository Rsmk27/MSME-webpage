CC=gcc
CFLAGS=-I.

test:
	sed 's/while (1)/if (1) { loop_entered = 1; longjmp(test_env, 1); } while (0)/g' ../data/user_switch.c | sed 's/int main/int original_main/g' > user_switch_tested.c
	$(CC) $(CFLAGS) -o test_error test_error_handler.c user_switch_tested.c
	./test_error

clean:
	rm -f test_error user_switch_tested.c
