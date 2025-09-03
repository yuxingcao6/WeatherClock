#ifndef __RTC_H__
#define __RTC_H__

#include <stdint.h>

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t weekday;
} rtc_date_time_t;

void rtc_init(void);
void rtc_set_time(const rtc_date_time_t *date_time);
void rtc_get_time(rtc_date_time_t *date_time);

#endif /* __RTC_H__ */
