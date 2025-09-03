#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "st7789.h"
#include "ui.h"
#include "font.h"
#include "image.h"

typedef enum
{
    UI_ACTION_FILL_COLOR,
    UI_ACTION_WRITE_STRING,
    UI_ACTION_DRAW_IMAGE,
} ui_action_t;

typedef struct
{
    ui_action_t action;
    union
    {
        struct
        {
            uint16_t x;
            uint16_t y;
            uint16_t width;
            uint16_t height;
            uint16_t color;
        } fill_color;
        struct
        {
            uint16_t x;
            uint16_t y;
            const char *str;
            uint16_t color;
            uint16_t bg_color;
            const font_t *font;
        } write_string;
        struct
        {
            uint16_t x;
            uint16_t y;
            const image_t *image;
        } draw_image;
    };
} ui_message_t;

static QueueHandle_t ui_queue;

static void ui_func(void *param)
{
    ui_message_t msg;
    
    st7789_init();
    
    while (1)
    {
        xQueueReceive(ui_queue, &msg, portMAX_DELAY);
        
        switch (msg.action)
        {
        case UI_ACTION_FILL_COLOR:
            st7789_fill_color(msg.fill_color.x, msg.fill_color.y,
                              msg.fill_color.width, msg.fill_color.height,
                              msg.fill_color.color);
            break;
        case UI_ACTION_WRITE_STRING:
            st7789_write_string(msg.write_string.x, msg.write_string.y,
                                msg.write_string.str,
                                msg.write_string.color, msg.write_string.bg_color,
                                msg.write_string.font);
            vPortFree((void*)msg.write_string.str);
            break;
        case UI_ACTION_DRAW_IMAGE:
            st7789_draw_image(msg.draw_image.x, msg.draw_image.y,
                              msg.draw_image.image);
            break;
        default:
            printf("Unknown UI action: %d\n", msg.action);
            break;
        }
    }
}

void ui_init(void)
{
    ui_queue = xQueueCreate(16, sizeof(ui_message_t));
    configASSERT(ui_queue);
    xTaskCreate(ui_func, "ui", 1024, NULL, 8, NULL);
}

void ui_fill_color(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
    ui_message_t msg;
    msg.action = UI_ACTION_FILL_COLOR;
    msg.fill_color.x = x;
    msg.fill_color.y = y;
    msg.fill_color.width = width;
    msg.fill_color.height = height;
    msg.fill_color.color = color;
    
    xQueueSend(ui_queue, &msg, portMAX_DELAY);
}

void ui_write_string(uint16_t x, uint16_t y, const char *str, uint16_t color, uint16_t bg_color, const font_t *font)
{
    char *pstr = pvPortMalloc(strlen(str) + 1);
    if (pstr == NULL)
    {
        printf("ui write string malloc failed: %s", str);
        return;
    }
    strcpy(pstr, str);
    
    ui_message_t msg;
    msg.action = UI_ACTION_WRITE_STRING;
    msg.write_string.x = x;
    msg.write_string.y = y;
    msg.write_string.str = pstr;
    msg.write_string.color = color;
    msg.write_string.bg_color = bg_color;
    msg.write_string.font = font;
    
    xQueueSend(ui_queue, &msg, portMAX_DELAY);
}

void ui_draw_image(uint16_t x, uint16_t y, const image_t *image)
{
    ui_message_t msg;
    msg.action = UI_ACTION_DRAW_IMAGE;
    msg.draw_image.x = x;
    msg.draw_image.y = y;
    msg.draw_image.image = image;
    
    xQueueSend(ui_queue, &msg, portMAX_DELAY);
}
