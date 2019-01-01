#include <stdio.h>
#include <stdlib.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include "usart_comm.h"
#include "relays.h"
#include "clock.h"


int main() {
	rcc_clock_setup_in_hse_8mhz_out_72mhz();

	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

	usart_comm_init();
	clock_init();
	//relays_init();

	//clock_set_time_ui();


	int cnt = 0;
	while(1){
		if(cnt > 0xfffff){
			printf("Time: %lu\r\n", clock_get_raw_time());
			cnt = 0;
		}
		else cnt++;
		//relays_update();
	}
}
