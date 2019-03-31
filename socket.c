#include "socket.h"

int mockSockSetup(int sock){
	if(fcntl(sock, F_SETFL, O_NONBLOCK) == -1){
		close(sock);
		return -1;
	}

	return sock;
}

int mockConnect(char* ipv4, int* sock, int port){
	struct sockaddr_in server;
	if((*sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
#ifdef DEBUG_SOCK
		printf("\tSocket create error\n");
#endif
		return -1;
	}
#ifdef DEBUG_SOCK
	printf("\tCreate socket success\n");
#endif
	memset(&server, '0', sizeof(server));
	server.sin_addr.s_addr	= inet_addr(ipv4);
	server.sin_family		= AF_INET;
	server.sin_port		= htons(port);

	if(connect(*sock, (struct sockaddr *)&server, sizeof(server)) < 0){
#ifdef DEBUG_SOCK
		printf("\tConnection Failled");
#endif
		return -1;
	}
#ifdef DEBUG_SOCK
	printf("\tConnected\n");
#endif
	return mockSockSetup(*sock) == -1 ? 0 : 1;
}

ssize_t mockFillInBuf(int sock, char* ccinbuf, size_t ccinbufsize){
	ssize_t ret = read(sock, ccinbuf, ccinbufsize);
	if(ret == 0) return -1;
	if(ret == -1) ret = 0;
	return ret;
}

ssize_t mockPeekBytes(int sock, char* ccinbuf, size_t ccinbufsize, int timeout_ms){
	struct pollfd p;
	ssize_t ret;
	do{
		ret = mockFillInBuf(sock, ccinbuf, ccinbufsize);
		if(ret < 0)
			return -1;
		p.fd = sock;
		p.events = POLLIN;
	}while(poll(&p, 1, timeout_ms) == 1);
	return ret;
}

ssize_t mockRead(int sock, char* ccinbuf, size_t ccinbufsize, int timeout_ms){
	ssize_t copied = mockPeekBytes(sock, ccinbuf, ccinbufsize, timeout_ms);
	if(copied < 0) return -1;
	memmove(ccinbuf, ccinbuf + copied, ccinbufsize - copied);
	return copied;
}

ssize_t mockWrite(int sock, char* data, size_t size, int timeout_ms){
	struct pollfd p;
	p.fd = sock;
	p.events = POLLOUT;
	int ret = poll(&p, 1, timeout_ms);
	if(ret == -1) return 0;
	if(ret){
		ret = send(sock, data, size, 0);
		if(ret == -1) return -1;
		if(ret != (int)size) exit(EXIT_FAILURE);
	}
	return ret;
}
