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

#define SysTick_CTRL_ENABLE_Pos    0U
#define SysTick_CTRL_ENABLE_Msk    (1UL << SysTick_CTRL_ENABLE_Pos)
#define SysTick_CTRL_TICKINT_Pos   1U
#define SysTick_CTRL_TICKINT_Msk   (1UL << SysTick_CTRL_TICKINT_Pos)
#define SysTick_CTRL_CLKSOURCE_Pos 2U
#define SysTick_CTRL_CLKSOURCE_Msk (1UL << SysTick_CTRL_CLKSOURCE_Pos)
#define SysTick_CTRL_COUNTFLAG_Pos 16U
#define SysTick_CTRL_COUNTFLAG_Msk (1UL << SysTick_CTRL_COUNTFLAG_Pos)

#endif
