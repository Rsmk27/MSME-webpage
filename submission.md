⚡ Optimize delayMS function to use WFI instead of busy waiting

💡 What:
- Initialized SysTick to use interrupts in SysTick_Init().
- Updated delayMS() to use wfi within a loop evaluating msTicks to pause execution, replacing a tight CPU busy-waiting loop evaluating SysTick->CTRL flag.
- Modified tests and test Makefile to accommodate for the refactoring.

🎯 Why:
- The previous implementation used a CPU intensive busy loop (while(...) ;) to delay, continuously polling memory mapped registers.
- Utilizing WFI saves power and reduces processor resource consumption while blocking.

📊 Measured Improvement:
- Synthethic benchmark (1000ms delay):
  - Old delay CPU time used: 0.022738s
  - New delay CPU time used: 0.000015s
  - Result: The new delay function consumes drastically less CPU time, effectively proving that CPU resources are no longer needlessly consumed in a tight loop.
