#ifndef __FONT_H
#define __FONT_H

// !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~

#include <stdint.h>

typedef struct
{
    const char *name;
    const uint8_t *model;
} font_chinese_t;

typedef struct
{
    const uint8_t *ascii_model;
    const char *ascii_map;
    const font_chinese_t *chinese;
    uint16_t size;
} font_t;

extern const font_t font16_maple;
extern const font_t font20_maple_bold;
extern const font_t font24_maple_semibold;
extern const font_t font24_maple_bold;
extern const font_t font32_maple_bold;
extern const font_t font54_maple_bold;
extern const font_t font54_maple_semibold;
extern const font_t font64_maple_extrabold;
extern const font_t font76_maple_extrabold;

#endif /* __FONT_H */
