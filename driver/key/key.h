#ifndef __KEY_H__
#define __KEY_H__

#include <stdbool.h>
#include <stdint.h>

struct key_desc;
typedef struct key_desc *key_desc_t;

typedef void (*key_func_t)(key_desc_t key);

void key_init(key_desc_t key);
bool key_read(key_desc_t key);
void key_press_callback_register(key_desc_t key, key_func_t func);

#endif /* __KEY_H__ */
