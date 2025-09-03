#ifndef __APP_UI_H__
#define __APP_UI_H__

#include <stdint.h>
#include "font.h"
#include "image.h"

#define UI_WIDTH    240
#define UI_HEIGHT   320

#define mkcolor(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))

void ui_init(void);
void ui_fill_color(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void ui_write_string(uint16_t x, uint16_t y, const char *str, uint16_t color, uint16_t bg_color, const font_t *font);
void ui_draw_image(uint16_t x, uint16_t y, const image_t *image);

#endif /* __APP_UI_H__ */
