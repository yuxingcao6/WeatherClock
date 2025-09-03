#ifndef __LED_H__
#define __LED_H__

#include <stdbool.h>
#include <stdint.h>

struct led_desc;
typedef struct led_desc *led_desc_t;

void led_init(led_desc_t led);
void led_set(led_desc_t led, bool onoff);
void led_on(led_desc_t led);
void led_off(led_desc_t led);


#endif /* __LED_H__ */
