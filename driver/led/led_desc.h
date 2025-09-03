#ifndef __LED_DESC_H__
#define __LED_DESC_H__

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx.h"

struct led_desc
{
    GPIO_TypeDef* Port;
    uint32_t Pin;
    BitAction OnBit;
    BitAction OffBit;
};

#endif /* __LED_DESC_H__ */
