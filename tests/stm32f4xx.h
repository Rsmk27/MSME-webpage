#ifndef STM32F4XX_H
#define STM32F4XX_H

#include <stdint.h>

typedef struct {
    uint32_t AHB1ENR;
    uint32_t APB1ENR;
} RCC_TypeDef;

typedef struct {
    uint32_t MODER;
    uint32_t ODR;
    uint32_t AFR[2];
} GPIO_TypeDef;

typedef struct {
    uint32_t BRR;
    uint32_t CR1;
    uint32_t SR;
    uint32_t DR;
} USART_TypeDef;

typedef struct {
    uint32_t LOAD;
    uint32_t VAL;
    uint32_t CTRL;
} SysTick_TypeDef;

extern RCC_TypeDef *RCC;
extern GPIO_TypeDef *GPIOA;
extern USART_TypeDef *USART2;
extern SysTick_TypeDef *SysTick;

#endif
