#pragma once
#include <stdint.h>


typedef int32_t ring_size_t;

typedef struct {
	uint8_t *data;
	ring_size_t size;
	uint32_t begin;
	uint32_t end;
} ring;

#define RING_SIZE(RING)  ((RING)->size - 1)
#define RING_DATA(RING)  (RING)->data
#define RING_EMPTY(RING) ((RING)->begin == (RING)->end)

void ring_init(ring*, uint8_t*, ring_size_t);

int32_t ring_write_ch(ring*, uint8_t);

int32_t ring_write(ring* ,uint8_t*, ring_size_t);
int32_t ring_read_ch(ring* , uint8_t*);
int32_t ring_read(ring* , uint8_t* , ring_size_t);
