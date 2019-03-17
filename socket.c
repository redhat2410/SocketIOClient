#include "socket.h"

int mockSockSetup(int sock){
	if(fcntl(sock, F_SETFL, O_NONBLOCK) == -1){
		perror("socket fcntl(O_NONBLOCK)");
		//closeERR(sock);
		close(sock);
		return -1;
	}
#ifndef MSG_NOSIGNAL
	int i = 1;
	if(setsockport(sock, SOL_SOCKET, SO_NOSIGPIPE, &i, sizeof(i)) == -1){
		perror("sockopt(SO_NOSIGPIPE)(macOS)");
		close(sock);
		return -1;
	}
#endif
	return sock;
}

int mockConnect(uint32_t ipv4, int* sock, int port){
	struct sockaddr_in server;
	if((*sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror(MOCK "ClientContext: connect: ::socket()");
		return 0;
	}
	server.sin_family	= AF_INET;
	server.sin_port		= htons(port);
	memcpy(&server.sin_addr, &ipv4, 4);
	if(connect(*sock, (struct sockaddr*)&server, sizeof(server)) == -1){
		perror(MOCK "ClientContext::connect: ::connect()");
		return 0;
	}

	return mockSockSetup(*sock) == -1 ? 0 : 1;
}

ssize_t mockFillInBuf(int sock, char* ccinbuf, size_t* ccinbufsize){
	size_t maxread = CCBUFSIZE - *ccinbufsize;
	ssize_t ret = read(sock, ccinbuf + *ccinbufsize, maxread);

	if(ret == 0) return -1;
	if(ret == -1){
		if( errno != EAGAIN){
			fprintf(stderr, MOCK "ClientContext::(read/peek fd=%i): filling buffer for %zd bytes: %s\n", sock, maxread, strerror(errno));
			return -1;
		}
		ret = 0;
	}
	*ccinbufsize += ret;
	return ret;
}

ssize_t mockPeekBytes(int sock, char* dst, size_t usersize, int timeout_ms, char* ccinbuf, size_t* bufsize){
	if(usersize > CCBUFSIZE){
		mockverbose("CCBUFSIZE(%d) should be increased by %zd bytes (-> %zd)\n", CCBUFSIZE, usersize - CCBUFSIZE, usersize);
	}	
	struct pollfd p;
	size_t retsize = 0;
	do{
		if(usersize <= bufsize){
			// data already buffered
			retsize = usersize;
			break;
		}

		//check incoming data
		if(mockFillInBuf(sock, ccinbuf, bufsize) < 0)
			return -1;
		if(usersize <= bufsize){
			//data just received
			retsize = usersize;
			break;
		}
		//Wait for more data until timeout
		p.fd = sock;
		p.events = POLLIN;
	}while(poll(&p, 1, timeout_ms) == 1);

	memcpy(dst, ccinbuf, retsize);
	return retsize;
}

ssize_t mockRead(int sock, char* dst, size_t size, int timeout_ms, char* ccinbuf, size_t* ccinbufsize){
	ssize_t copied = mockPeekBytes(sock, dst, size, timeout_ms, ccinbuf, ccinbufsize);
	if(copied < 0) return -1;
	memmove(ccinbuf, ccinbuf + copied, *ccinbufsize - copied);
	*ccinbufsize -= copied;
	return copied;
}

ssize_t mockWrite(int sock, const char* data, size_t size, int timeout_ms){
	struct pollfd p;
	p.fd = sock;
	p.events = POLLOUT;
	int ret = poll(&p, 1, timeout_ms);
	if(ret == -1){
		fprintf(stderr, MOCK "ClientContext::write: poll(%d): %s\n", sock, strerror(errno));
		return 0;
	}
	if(ret){
#ifndef MSG_NOSIGNAL
		ret = write(sock, data, size);
#else
		ret = send(sock, data, size, MSG_NOSIGNAL);
#endif
		if(ret == -1)
		{
			fprintf(stderr, MOCK "ClientContext::write(%d): %s\n", sock, strerror(errno));
			return -1;
		}
		if(ret != (int)size){
			fprintf(stderr, MOCK "ClientContext::write: short write (%d < %zd) (FIXME poll loop TODO)\n", ret, size);
			exit(EXIT_FAILURE);
		}
	}
	return ret;
}




