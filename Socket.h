#include "stdio.h"
#include "sys/socket.h"
#include "stdlib.h"
#include "netinet/in.h"
#include "string.h"

#define DATA_BUFFER_LEN 2048
#define DEBUG

struct sockaddr_in address;
struct sockaddr_in serv_addr;
static int client = 0;
char* buffer;



//this function initialization socket for client
int intiSOCKET(char* host, int port);
//function implement send data in socket
void sendSOCKET(char* data);
//function impolemnt receive data in socket
char* receiveSOCKET(void);
//fucnton disconnect socket (destroy socket)
void disconnectSOCKET(void);
