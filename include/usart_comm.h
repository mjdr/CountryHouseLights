#pragma once


void usart_comm_init();
int usart_comm_write(const char*, int);
int usart_comm_read(char*, int);
