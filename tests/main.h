#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <setjmp.h>

extern int loop_entered;
extern jmp_buf test_env;

// Mock types
typedef struct {
    int OscillatorType;
    int HSIState;
    int HSICalibrationValue;
    struct {
        int PLLState;
        int PLLSource;
        int PLLM;
        int PLLN;
        int PLLP;
        int PLLQ;
        int PLLR;
    } PLL;
} RCC_OscInitTypeDef;

typedef struct {
    int ClockType;
    int SYSCLKSource;
    int AHBCLKDivider;
    int APB1CLKDivider;
    int APB2CLKDivider;
} RCC_ClkInitTypeDef;

typedef struct {
    int Instance;
    struct {
        int BaudRate;
        int WordLength;
        int StopBits;
        int Parity;
        int Mode;
        int CLKPolarity;
        int CLKPhase;
        int CLKLastBit;
    } Init;
} USART_HandleTypeDef;

typedef struct {
    int Pin;
    int Mode;
    int Pull;
    int Speed;
} GPIO_InitTypeDef;

#define HAL_OK 0
#define HAL_ERROR 1

// Mock functions
void HAL_Init(void);
int HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
int HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, int FLatency);
int HAL_USART_Init(USART_HandleTypeDef *husart);
void HAL_GPIO_Init(int GPIOx, GPIO_InitTypeDef *GPIO_Init);
void HAL_GPIO_WritePin(int GPIOx, int GPIO_Pin, int PinState);
int HAL_GPIO_ReadPin(int GPIOx, int GPIO_Pin);

// Mock macros
#define __HAL_RCC_PWR_CLK_ENABLE()
#define __HAL_PWR_VOLTAGESCALING_CONFIG(x)
#define __HAL_RCC_GPIOC_CLK_ENABLE()
#define __HAL_RCC_GPIOH_CLK_ENABLE()
#define __HAL_RCC_GPIOA_CLK_ENABLE()
#define __HAL_RCC_GPIOB_CLK_ENABLE()

void __disable_irq(void);

// Constants
#define USART2 2
#define USART_WORDLENGTH_8B 8
#define USART_STOPBITS_1 1
#define USART_PARITY_NONE 0
#define USART_MODE_TX_RX 3
#define USART_POLARITY_LOW 0
#define USART_PHASE_1EDGE 0
#define USART_LASTBIT_DISABLE 0

#define PWR_REGULATOR_VOLTAGE_SCALE3 3
#define RCC_OSCILLATORTYPE_HSI 1
#define RCC_HSI_ON 1
#define RCC_HSICALIBRATION_DEFAULT 16
#define RCC_PLL_ON 1
#define RCC_PLLSOURCE_HSI 1
#define RCC_PLLP_DIV4 4

#define RCC_CLOCKTYPE_HCLK 1
#define RCC_CLOCKTYPE_SYSCLK 2
#define RCC_CLOCKTYPE_PCLK1 4
#define RCC_CLOCKTYPE_PCLK2 8
#define RCC_SYSCLKSOURCE_PLLCLK 1
#define RCC_SYSCLK_DIV1 1
#define RCC_HCLK_DIV2 2
#define RCC_HCLK_DIV1 1
#define FLASH_LATENCY_2 2

#define GPIOC 1
#define GPIOA 2
#define GPIOH 3
#define GPIOB 4
#define LD2_GPIO_Port GPIOA

#define GPIO_PIN_13 13
#define GPIO_PIN_5 5
#define LD2_Pin GPIO_PIN_5
#define GPIO_PIN_RESET 0
#define GPIO_PIN_SET 1

#define GPIO_MODE_INPUT 1
#define GPIO_MODE_OUTPUT_PP 2
#define GPIO_NOPULL 0
#define GPIO_SPEED_FREQ_LOW 1

void Error_Handler(void);

void __WFI(void);
#define EXTI15_10_IRQn 40
#define GPIO_MODE_IT_RISING_FALLING 0x10210000
void HAL_NVIC_SetPriority(int IRQn, int PreemptPriority, int SubPriority);
void HAL_NVIC_EnableIRQ(int IRQn);
void HAL_GPIO_EXTI_IRQHandler(int GPIO_Pin);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif
