#ifndef __AHT20_H__
#define __AHT20_H__

#include <stdbool.h>
#include <stdint.h>

bool aht20_init(void);
bool aht20_start_measurement(void);
bool aht20_wait_for_measurement(void);
bool aht20_read_measurement(float *temperature, float *humidity);

#endif /* __AHT20_H__ */
