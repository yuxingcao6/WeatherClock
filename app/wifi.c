#include <stdint.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "esp_at.h"
#include "page.h"
#include "wifi.h"

void wifi_init(void)
{
    if (!esp_at_init())
    {
        printf("[AT] init failed\n");
        goto err;
    }
    printf("[AT] inited\n");
    
    if (!esp_at_wifi_init())
    {
        printf("[WIFI] init failed\n");
        goto err;
    }
    printf("[WIFI] inited\n");
    
    if (!esp_at_sntp_init())
    {
        printf("[SNTP] init failed\n");
        goto err;
    }
    printf("[SNTP] inited\n");
    
    return;
    
err:
    error_page_display("wireless init failed");
    while (1)
    {
        ;
    }
}

void wifi_wait_connect(void)
{
    printf("[WIFI] connecting\n");
    
    esp_at_connect_wifi(WIFI_SSID, WIFI_PASSWD, NULL);
    
    for (uint32_t t = 0; t < 10 * 1000; t += 100)
    {
        vTaskDelay(pdMS_TO_TICKS(100));
        esp_wifi_info_t wifi = { 0 };
        if (esp_at_get_wifi_info(&wifi) && wifi.connected)
        {
            printf("[WIFI] Connected\n");
            printf("[WIFI] SSID: %s, BSSID: %s, Channel: %d, RSSI: %d\n",
                wifi.ssid, wifi.bssid, wifi.channel, wifi.rssi);
            return;
        }
    }
    
    printf("[WIFI] Connection Timeout\n");
    error_page_display("wireless connect failed");
    while (1)
    {
        ;
    }
}
