#ifndef __KEY_DESC_H__
#define __KEY_DESC_H__

#include <stdint.h>
#include "stm32f4xx.h"
#include "key.h"

struct key_desc
{
    GPIO_TypeDef *port;
    uint16_t pin;
    uint8_t exti_port_src;
    uint8_t exti_pin_src;
    uint32_t exti_line;
    uint8_t irqn;
    key_func_t func;
};

#endif /* __KEY_H__ */
