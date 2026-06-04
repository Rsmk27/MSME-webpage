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

/* GPIO MODER Macros */
#define GPIO_MODER_MODER5_Pos            (10U)
#define GPIO_MODER_MODER5_Msk            (0x3UL << GPIO_MODER_MODER5_Pos)
#define GPIO_MODER_MODER5                GPIO_MODER_MODER5_Msk
#define GPIO_MODER_MODER5_0              (0x1UL << GPIO_MODER_MODER5_Pos)
#define GPIO_MODER_MODER5_1              (0x2UL << GPIO_MODER_MODER5_Pos)

#define GPIO_MODER_MODER2_Pos            (4U)
#define GPIO_MODER_MODER2_Msk            (0x3UL << GPIO_MODER_MODER2_Pos)
#define GPIO_MODER_MODER2                GPIO_MODER_MODER2_Msk
#define GPIO_MODER_MODER2_0              (0x1UL << GPIO_MODER_MODER2_Pos)
#define GPIO_MODER_MODER2_1              (0x2UL << GPIO_MODER_MODER2_Pos)

/* GPIO ODR Macros */
#define GPIO_ODR_OD5_Pos                 (5U)
#define GPIO_ODR_OD5_Msk                 (0x1UL << GPIO_ODR_OD5_Pos)
#define GPIO_ODR_OD5                     GPIO_ODR_OD5_Msk

/* GPIO MODER Macros */


/* GPIO ODR Macros */

/* GPIO AFR Macros */
#define GPIO_AFRL_AFSEL2_Pos             (8U)
#define GPIO_AFRL_AFSEL2_Msk             (0xFUL << GPIO_AFRL_AFSEL2_Pos)
#define GPIO_AFRL_AFSEL2                 GPIO_AFRL_AFSEL2_Msk

/* USART CR1 Macros */
#define USART_CR1_TE_Pos                 (3U)
#define USART_CR1_TE_Msk                 (0x1UL << USART_CR1_TE_Pos)
#define USART_CR1_TE                     USART_CR1_TE_Msk

#define USART_CR1_UE_Pos                 (13U)
#define USART_CR1_UE_Msk                 (0x1UL << USART_CR1_UE_Pos)
#define USART_CR1_UE                     USART_CR1_UE_Msk

/* USART SR Macros */
#define USART_SR_TXE_Pos                 (7U)
#define USART_SR_TXE_Msk                 (0x1UL << USART_SR_TXE_Pos)
#define USART_SR_TXE                     USART_SR_TXE_Msk

/* SysTick CTRL Macros */
#define SysTick_CTRL_ENABLE_Pos          (0U)
#define SysTick_CTRL_ENABLE_Msk          (1UL /*<< SysTick_CTRL_ENABLE_Pos*/)
#define SysTick_CTRL_CLKSOURCE_Pos       (2U)
#define SysTick_CTRL_CLKSOURCE_Msk       (1UL << SysTick_CTRL_CLKSOURCE_Pos)
#define SysTick_CTRL_COUNTFLAG_Pos       (16U)
#define SysTick_CTRL_COUNTFLAG_Msk       (1UL << SysTick_CTRL_COUNTFLAG_Pos)

/* RCC AHB1ENR Macros */
#define RCC_AHB1ENR_GPIOAEN_Pos          (0U)
#define RCC_AHB1ENR_GPIOAEN_Msk          (0x1UL << RCC_AHB1ENR_GPIOAEN_Pos)
#define RCC_AHB1ENR_GPIOAEN              RCC_AHB1ENR_GPIOAEN_Msk

/* RCC APB1ENR Macros */
#define RCC_APB1ENR_USART2EN_Pos         (17U)
#define RCC_APB1ENR_USART2EN_Msk         (0x1UL << RCC_APB1ENR_USART2EN_Pos)
#define RCC_APB1ENR_USART2EN             RCC_APB1ENR_USART2EN_Msk


/* GPIO MODER Macros */


/* GPIO ODR Macros */

/* GPIO AFR Macros */

/* USART CR1 Macros */


/* USART SR Macros */

/* SysTick CTRL Macros */

/* RCC AHB1ENR Macros */

/* RCC APB1ENR Macros */


/* Add the 0, 1, 2 macros for GPIO_AFRL_AFSEL2 */
#define GPIO_AFRL_AFSEL2_0               (0x1UL << GPIO_AFRL_AFSEL2_Pos)
#define GPIO_AFRL_AFSEL2_1               (0x2UL << GPIO_AFRL_AFSEL2_Pos)
#define GPIO_AFRL_AFSEL2_2               (0x4UL << GPIO_AFRL_AFSEL2_Pos)
