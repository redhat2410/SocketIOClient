#include "socket.h"
#include "err.h"

#define DATA_BUFFER_LEN	2048
#define ESTABLISHED	1
#define CLOSED		0


static int _sock;
static int _timeout_ms;
static char _inbuf[DATA_BUFFER_LEN];

signed int abortSOCK(){
	if(_sock >= 0){
		close(_sock);
#ifdef DEBUG_SOCK
		printf("\tsocket closed\n");
#endif
	}
	_sock = -1;
	return ERR_ABRT;
}

signed int closeSOCK(){
	abortSOCK();
	return ERR_OK;
}

int connectSOCK(char* ipv4, int port){
	return mockConnect(ipv4, &_sock, port);
}

void setTimeoutSOCK(int timeout_ms){
	_timeout_ms = timeout_ms;
}

int getTimeoutSOCK(){
	return _timeout_ms;
}

size_t getSizeSOCK(){
	if(_sock < 0) return 0;
	ssize_t ret = mockFillInBuf(_sock, _inbuf, DATA_BUFFER_LEN);
	if(ret < 0){
		abortSOCK();
		return 0;
	}
	return ret;
}

size_t readSOCK(char* dst, size_t size){
	ssize_t ret = mockRead(_sock, dst, size, _timeout_ms);
	if(ret < 0){
		abortSOCK();
		return 0;
	}
	return ret;
}

size_t peekBytesSOCK(char* dst, size_t size){
	ssize_t ret = mockPeekBytes(_sock, dst, size, _timeout_ms);
	if(ret < 0){
		abortSOCK();
		return 0;
	}

	return ret;
}

uint8_t stateSOCK(){
	(void)getSizeSOCK();
	return _sock >= 0 ? ESTABLISHED : CLOSED;
}

size_t writeSOCK(char* data, size_t size){
	ssize_t ret = mockWrite(_sock, data, size, _timeout_ms);
	if(ret < 0){
		abortSOCK();
		return 0;
	}

	return ret;
}

