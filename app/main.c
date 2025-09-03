#include "FreeRTOS.h"
#include "task.h"
#include "workqueue.h"
#include "app.h"
#include "ui.h"
#include "wifi.h"
#include "page.h"

extern void board_lowlevel_init(void);
extern void board_init(void);

static void main_init(void *param)
{
    board_init();
    ui_init();

    welcome_page_display();

    wifi_init();
    wifi_page_display();
    wifi_wait_connect();

    main_page_display();
    app_init();

    vTaskDelete(NULL);
}

int main(void)
{
    board_lowlevel_init();
    workqueue_init();

    xTaskCreate(main_init, "init", 1024, NULL, 9, NULL);

    vTaskStartScheduler();

    while (1)
    {
        ; // code should not run here
    }
}
