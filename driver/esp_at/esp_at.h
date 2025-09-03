#ifndef __ESP_AT_H__
#define __ESP_AT_H__

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	char ssid[64];
	char bssid[18];
	int channel;
	int rssi;
	bool connected;
} esp_wifi_info_t;

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t weekday;
} esp_date_time_t;

bool esp_at_init(void);
bool esp_at_wifi_init(void);
bool esp_at_connect_wifi(const char *ssid, const char *pwd, const char *mac);
bool esp_at_get_wifi_info(esp_wifi_info_t *info);
bool wifi_is_connected(void);
bool esp_at_sntp_init(void);
bool esp_at_sntp_get_time(esp_date_time_t *date);
const char *esp_at_http_get(const char *url);

#endif /* __ESP_AT_H__ */
