#pragma once

#include <stdint.h>

typedef struct {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t dayOfWeek;
	uint32_t raw;
} __attribute__((packed)) clock_time_t;


void clock_init();
void clock_set_time_ui();
void clock_get_time_ui();
void clock_get_time(clock_time_t*);
uint32_t clock_get_raw_time();
