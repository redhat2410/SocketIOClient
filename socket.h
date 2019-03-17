#include "stdlib.h"
#include "unistd.h"
#include "netinet/tcp.h"
#include "arpa/inet.h"
#include "poll.h"
#include "fcntl.h"
#include "errno.h"
#include "stdint.h"

#define RANDOM_REG32	((uint32_t)random())
#define MOCK "mock: "

int ets_printf(const char* fmt, ...) __attribute__ ((format (printf, 1, 2)));
#define os_printf_plus prinft
int mockverbose(const char* fmt, ...) __attribute__ ((format (printf, 1, 2)));

extern const char* host_interface;
extern int mock_port_shifter;

#define NO_GLOBAL_BINDING	0xffffffff
#define _REENT	_impure_ptr
#define stderr	(_REENT->_stderr)

#ifndef CCBUFSIZE
#define CCBUFSIZE 65536
#endif


// for TCP
int	mockSockSetup	(int sock);
int	mockConnect	(uint32_t addr, int* sock, int port);
ssize_t	mockFillInBuf	(int sock, char* ccinbuf, size_t* ccinbufsize);
ssize_t	mockPeekBytes	(int sock, char* dst, size_t usersize, int timeout_ms, char* ccinbuf, size_t* bufsize);
ssize_t mockRead	(int sock, char* dst, size_t size, int timeout_ms, char* buff, size_t* bufsize);
ssize_t	mockWrite	(int sock, const char* data, size_t size, int timeout_ms);
int	serverAccept	(int sock);


// for error

