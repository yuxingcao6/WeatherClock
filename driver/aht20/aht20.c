#include <stdbool.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx.h"
#include "tim_delay.h"

static bool aht20_write(uint8_t data[], uint32_t length);
static bool aht20_read(uint8_t data[], uint32_t length);
static bool aht20_is_ready(void);

bool aht20_init(void)
{
    I2C_InitTypeDef I2C_InitStruct;
    I2C_StructInit(&I2C_InitStruct);
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStruct.I2C_ClockSpeed = 100ul * 1000ul;
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct.I2C_OwnAddress1 = 0x00;
    I2C_Init(I2C2, &I2C_InitStruct);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C2);
    
    vTaskDelay(pdMS_TO_TICKS(40));
    if (aht20_is_ready())
        return true;
    
    if (!aht20_write((uint8_t[]){0xBE, 0x08, 0x00}, 3))
        return false;
    
    for (uint32_t t = 0; t < 20; t ++)
    {
        vTaskDelay(pdMS_TO_TICKS(5));
        if (aht20_is_ready())
            return true;
    }
    
    return false;
}

#define I2C_CHECK_EVENT(EVENT, TIMEOUT) \
    do { \
        uint32_t timeout = TIMEOUT; \
        while (!I2C_CheckEvent(I2C2, EVENT) && timeout > 0) { \
            tim_delay_us(10); \
            timeout -= 10; \
        } \
        if (timeout <= 0) \
            return false; \
    } while (0)

static bool aht20_write(uint8_t data[], uint32_t length)
{
    I2C_AcknowledgeConfig(I2C2, ENABLE);
    I2C_GenerateSTART(I2C2, ENABLE);
    I2C_CHECK_EVENT(I2C_EVENT_MASTER_MODE_SELECT, 1000);
    I2C_Send7bitAddress(I2C2, 0x70, I2C_Direction_Transmitter);
    I2C_CHECK_EVENT(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED, 1000);
    for (uint32_t i = 0; i < length; i++)
    {
        I2C_SendData(I2C2, data[i]);
        I2C_CHECK_EVENT(I2C_EVENT_MASTER_BYTE_TRANSMITTING, 1000);
    }
    I2C_GenerateSTOP(I2C2, ENABLE);
    
    return true;
}

static bool aht20_read(uint8_t data[], uint32_t length)
{
    I2C_AcknowledgeConfig(I2C2, ENABLE);
    I2C_GenerateSTART(I2C2, ENABLE);
    I2C_CHECK_EVENT(I2C_EVENT_MASTER_MODE_SELECT, 1000);
    I2C_Send7bitAddress(I2C2, 0x70, I2C_Direction_Receiver);
    I2C_CHECK_EVENT(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED, 1000);
    for (uint32_t i = 0; i < length; i++)
    {
        if (i == length - 1)
            I2C_AcknowledgeConfig(I2C2, DISABLE);
        I2C_CHECK_EVENT(I2C_EVENT_MASTER_BYTE_RECEIVED, 1000);
        data[i] = I2C_ReceiveData(I2C2);
    }
    I2C_GenerateSTOP(I2C2, ENABLE);
    
    return true;
}

static bool aht20_read_status(uint8_t *status)
{
    uint8_t cmd = 0x71;
    if (!aht20_write(&cmd, 1))
        return false;
    if (!aht20_read(status, 1))
        return false;
    
    return true;
}

static bool aht20_is_busy(void)
{
    uint8_t status;
    if (!aht20_read_status(&status))
        return false;
    return (status & 0x80) != 0;
}

static bool aht20_is_ready(void)
{
    uint8_t status;
    if (!aht20_read_status(&status))
        return false;
    return (status & 0x08) != 0;
}

bool aht20_start_measurement(void)
{
    return aht20_write((uint8_t[]){0xAC, 0x33, 0x00}, 3);
}

bool aht20_wait_for_measurement(void)
{
    for (uint32_t t = 0; t < 20; t++)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
        if (!aht20_is_busy())
        {
            return true;
        }
    }
    return false;
}

bool aht20_read_measurement(float *temperature, float *humidity)
{
    uint8_t data[6];
    if (!aht20_read(data, 6))
        return false;
    
    uint32_t raw_humidity = ((uint32_t)data[1] << 12) | 
                            ((uint32_t)data[2] << 4) | 
                            ((uint32_t)(data[3] &0xF0) >> 4);
    uint32_t raw_temperature = ((uint32_t)(data[3] & 0x0F) << 16) | 
                               ((uint32_t)data[4] << 8) | 
                               ((uint32_t)data[5]);
    
    *humidity = (float)raw_humidity * 100.0f / (float)0x100000;
    *temperature = (float)raw_temperature * 200.0f / (float)0x100000 - 50.0f;
    
    return true;
}
