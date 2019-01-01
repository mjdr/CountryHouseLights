#include "usart_comm.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include "ring.h"

void usart_comm_init(){
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_AFIO);
	rcc_periph_clock_enable(RCC_USART2);
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
			      GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART2_TX);
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT,
			      GPIO_CNF_INPUT_FLOAT, GPIO_USART2_RX);

	usart_set_baudrate(USART2, 9600);
	usart_set_databits(USART2, 8);
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_parity(USART2, USART_PARITY_NONE);
	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
	usart_set_mode(USART2, USART_MODE_TX_RX);
	usart_enable(USART2);

}
int usart_comm_write(const char* buffer, int len){
	for(int i = 0;i < len;i++)
		usart_send_blocking(USART2, buffer[i]);
	return len;

}
int usart_comm_read(char* buffer, int len){
	if(len == 0) return 0;
	buffer[0] = usart_recv_blocking(USART2);
	return 1;
}
