#include <stdbool.h>
#include <stddef.h>
#include "stm32f4xx.h"
#include "key.h"
#include "key_desc.h"

// KEY1: PA0
// KEY2: PC4
// KEY3: PC5

void key_init(key_desc_t key)
{
    // GPIO初始化结构体模板
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Medium_Speed;
    
    // EXTI中断初始化结构体模板
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_StructInit(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    
    // EXTI中断优先级配置结构体模板
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    
    // KEY1初始化
    GPIO_InitStructure.GPIO_Pin = key->pin;
    GPIO_Init(key->port, &GPIO_InitStructure);
    SYSCFG_EXTILineConfig(key->exti_port_src, key->exti_pin_src);
    EXTI_InitStructure.EXTI_Line = key->exti_line;
    EXTI_Init(&EXTI_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = key->irqn;
    NVIC_Init(&NVIC_InitStructure);
}

bool key_read(key_desc_t key)
{
    return GPIO_ReadInputDataBit(key->port, key->pin) == Bit_SET;
}

void key_press_callback_register(key_desc_t key, key_func_t func)
{
    key->func = func;
}
