#include "relays.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <stdlib.h>
#include <stdio.h>

#include "clock.h"

//#define RELAY_GPIO_SET(V,G,P) 	(V) ? gpio_set(G, P) : gpio_clear(G, P)
#define RELAY_GPIO_SET(V,G,P) 	printf("Relay[%d] = %d\r\n", (P), (V))
#define RELAY_GET(S,N) (!!(S &(1 << (N))))
#define RELAY_TOGGLE(S,N) S ^= (1 << (N))

static uint8_t state = 0;
static uint32_t next_update_time;

static void logic_update() {
	clock_time_t tm;
	clock_get_time(&tm);

	if(tm.hours > 6 && tm.hours < 17){
		state = 0;
		next_update_time = tm.raw + 5;
		return;
	}


	for(int i = 0;i < 1000;i++){
		uint8_t new_state = state;
		RELAY_TOGGLE(new_state, rand() % 3);
		uint8_t total = 0;
		for(int r = 0;r < 3;r++)
			if(RELAY_GET(new_state, r)) total++;
		if(total > 0 && total < 3){
			state = new_state;
			break;
		}
	}
	next_update_time = tm.raw + 5;
}

static void state_update() {
	RELAY_GPIO_SET(RELAY_GET(state, 0),GPIOA,GPIO4);
	RELAY_GPIO_SET(RELAY_GET(state, 1),GPIOA,GPIO5);
	RELAY_GPIO_SET(RELAY_GET(state, 2),GPIOA,GPIO6);
}
void relays_init(){
	rcc_periph_clock_enable(RCC_GPIOA);
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ,GPIO_CNF_OUTPUT_PUSHPULL, GPIO4|GPIO5|GPIO6);
	gpio_clear(GPIOA, GPIO6 | GPIO5| GPIO4);

	next_update_time = clock_get_raw_time();
}
void relays_update(){
	if(clock_get_raw_time() < next_update_time) return;
	logic_update();
	state_update();
}
