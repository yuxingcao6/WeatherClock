#include <stdint.h>
#include <string.h>
#include "stm32f4xx.h"
#include "tim_delay.h"

static volatile uint64_t tim_tick_count;
static tim_periodic_callback_t periodic_callback;

void tim_delay_init(void)
{
    RCC_ClocksTypeDef RCC_ClocksStruct;
    RCC_GetClocksFreq(&RCC_ClocksStruct);
    uint32_t apb1_tim_freq_mhz = RCC_ClocksStruct.PCLK1_Frequency / 1000 / 1000 * 2;
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = apb1_tim_freq_mhz - 1;
    TIM_TimeBaseStructure.TIM_Period = 999;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM6, ENABLE);
    
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

uint64_t tim_now(void)
{
    uint64_t now, last_count;
    do {
        last_count = tim_tick_count;
        now = tim_tick_count + TIM_GetCounter(TIM6);
    } while (last_count != tim_tick_count);
    return now;
}

uint64_t tim_get_us(void)
{
    return tim_now();
}

uint64_t cpu_get_ms(void)
{
    return tim_now() / 1000;
}

void tim_delay_us(uint32_t us)
{
    uint64_t now = tim_now();
    while (tim_now() - now < (uint64_t)us);
}

void tim_delay_ms(uint32_t ms)
{
    uint64_t now = tim_now();
    while (tim_now() - now < (uint64_t)ms * 1000);
}

void tim_register_periodic_callback(tim_periodic_callback_t callback)
{
    periodic_callback = callback;
}

void TIM6_DAC_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
        tim_tick_count += 1000;
        if (periodic_callback)
            periodic_callback();
    }
}
