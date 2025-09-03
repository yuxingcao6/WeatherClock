#ifndef __WEAHTER_H__
#define __WEAHTER_H__

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	char city[32];
	char loaction[128];
	char weather[16];
	int weather_code;
	float temperature;
} weather_info_t;

bool parse_seniverse_response(const char *response, weather_info_t *info);

#endif /* __WEAHTER_H__ */
