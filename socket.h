#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "fcntl.h"
#include "poll.h"

#define CCBUFSIZE	65536
#define DEBUG_SOCK

int mockSockSetup(int sock);
int mockConnect(char* ipv4, int* sock, int port);
ssize_t mockFillInBuf(int sock, char* ccinbuf, size_t ccinbufsize);
ssize_t mockPeekBytes(int sock, char* ccinbuf, size_t ccinbufsize, int timeout_ms);
ssize_t mockRead(int sock, char* ccinbuf, size_t ccinbufsize, int timeout_ms);
ssize_t mockWrite(int sock, char* data, size_t size, int timeout_ms);
