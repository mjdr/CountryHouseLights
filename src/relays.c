#include "relays.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <stdlib.h>
#include <stdio.h>

#include "clock.h"

//#define RELAY_GPIO_SET(V,G,P) 	(V) ? gpio_set(G, P) : gpio_clear(G, P)
#define RELAY_GPIO_SET(V,G,P) 	printf("Relay[%d] = %d\n", (P), (V))
#define RELAY_GET(S,N) (!!(S &(1 << (N))))
#define RELAY_TOGGLE(S,N) S ^= (1 << (N))

static uint8_t state = 0;
static uint32_t next_update_time;


void relays_init(){
	rcc_periph_clock_enable(RCC_GPIOA);
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ,GPIO_CNF_OUTPUT_PUSHPULL, GPIO0|GPIO1|GPIO2);
	gpio_clear(GPIOA, GPIO0 | GPIO1 | GPIO2);

	next_update_time = clock_get_raw_time();
}
void relays_update(){
	uint32_t time = clock_get_raw_time();

	if(time < next_update_time) return;


	RELAY_TOGGLE(state, rand() % 3);
	next_update_time = time + 5;

	RELAY_GPIO_SET(RELAY_GET(state, 0),GPIOA,GPIO0);
	RELAY_GPIO_SET(RELAY_GET(state, 1),GPIOA,GPIO1);
	RELAY_GPIO_SET(RELAY_GET(state, 2),GPIOA,GPIO2);
}
