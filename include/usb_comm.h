#pragma once
#include <stdint.h>

void usb_comm_init();
int usb_comm_write(const char*, int);
int usb_comm_read(char*, int);
uint32_t usb_comm_read_int();
uint32_t usb_comm_read_available();
