#include <errno.h>
#include "usart_comm.h"

int _write(int, const char*, int);
int _read(int, char*, int);

int _write(int fd, const char* buffer, int nbyte) {
	(void) fd;
	return usart_comm_write(buffer, nbyte);
}
int _read(int fd,char* buffer, int nbyte) {
	(void) fd;
	return usart_comm_read(buffer, nbyte);
}
