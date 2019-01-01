#include "clock.h"
#include <stdio.h>
#include <libopencm3/stm32/rtc.h>
#include <libopencm3/stm32/flash.h>
#include "usb_comm.h"

#define CLOCK_MAGIC 0xdeadbeaf

static void clock_set_time(const clock_time_t*);

void clock_init() {

	rcc_periph_clock_enable(RCC_PWR);
	rcc_periph_clock_enable(RCC_BKP);
	rcc_periph_reset_pulse(RST_BKP);

	rcc_osc_on(RCC_LSE);
	rcc_wait_for_osc_ready(RCC_LSE);
	rcc_set_rtc_clock_source(RCC_LSE);
	rcc_enable_rtc_clock();

	//rtc_enter_config_mode();

	//rtc_set_prescale_val(0xFFFFFFFF);
	//rtc_set_counter_val(0);
	//rtc_exit_config_mode();

}

void clock_set_time_ui(){
	clock_time_t tm;
	printf("Enter day of the week [1-7]: ");
	scanf("%1hhd", &tm.dayOfWeek);
	printf("Enter number of hours [0-23]: ");
	scanf("%2hhd", &tm.hours);
	printf("Enter number of minutes [0-59]: ");
	scanf("%2hhd", &tm.minutes);
	printf("Enter number of seconds [0-59]: ");
	scanf("%2hhd", &tm.seconds);

	printf("%d  %02d:%02d:%02d\n",
				tm.dayOfWeek,
				tm.hours,
				tm.minutes,
				tm.seconds
		);

	clock_set_time(&tm);
}
static void clock_set_time(const clock_time_t* tm){
	uint32_t time = 0;
	time += (tm->dayOfWeek - 1) * (60*60*24);
	time += tm->hours * (60*60);
	time += tm->minutes * 60;
	time += tm->seconds;

	return;

	rtc_enter_config_mode();
	rcc_set_rtc_clock_source(RCC_LSE);
	rtc_set_prescale_val(0xFFFFFFFF);
	rtc_set_counter_val(time);
	rtc_exit_config_mode();


}
void clock_get_time_ui(){
	clock_time_t tm;
	clock_get_time(&tm);

	printf("%d  %02d:%02d:%02d\n",
			tm.dayOfWeek,
			tm.hours,
			tm.minutes,
			tm.seconds
	);
}
void clock_get_time(clock_time_t* tm){
	uint32_t time = rtc_get_counter_val();

	tm->daysFromStart = time / (60*60*24);
	tm->dayOfWeek = (tm->daysFromStart % 7) + 1;
	tm->hours = (time / (60*60)) % 24;
	tm->minutes = (time / 60) % 60;
	tm->seconds = time % 60;
}
uint32_t clock_get_raw_time() {
	return rtc_get_counter_val();
}

