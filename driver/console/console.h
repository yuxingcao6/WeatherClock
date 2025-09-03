#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdint.h>

typedef void (*console_received_func_t)(uint8_t data);

void console_init(void);
void console_write(const char str[]);
void console_received_register(console_received_func_t func);

#endif /* __CONSOLE_H__ */
