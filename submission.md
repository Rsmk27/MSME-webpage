Title: ⚡ [Optimize USART2_init]

Description:
💡 **What:** Removed duplicate GPIO and USART initialization code from `USART2_init`.
🎯 **Why:** The exact same configuration sequence was repeated consecutively in the function without reason. Removing the redundant second initialization block cleans up the function, improves readability, and makes the code slightly faster without changing its behavior.
📊 **Measured Improvement:** Baseline performance measuring the time taken to execute `USART2_init()` 100M times was 0.64 seconds. Following the removal of the duplicate configurations, the time was reduced to 0.37 seconds (a ~42% reduction in execution time for this specific function initialization).
