#include <stdint.h>
#include <string.h>
#include "ui.h"

void error_page_display(const char *msg)
{
    const uint16_t color_bg = mkcolor(0, 0, 0);
    ui_fill_color(0, 0, UI_WIDTH - 1, UI_HEIGHT - 1, color_bg);
    ui_draw_image(40, 37, &img_error);
    
    uint16_t startx = 0;
    int len = strlen(msg) * font20_maple_bold.size / 2;
    if (len < UI_WIDTH)
        startx = (UI_WIDTH - len + 1) / 2;
    ui_write_string(startx, 245, msg, mkcolor(255, 255, 0), color_bg, &font20_maple_bold);
}
