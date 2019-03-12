#include "stdio.h"
#include "stdlib.h"
#include "netinet/in.h"
#include "string.h"

#define DATA_BUFFER_LEN 2048

struct sockaddr_in address;
struct sockaddr_in serv_addr;
int sock = 0, valread;
char* buffer;



//this function initialization socket for client
int inti_SOCKET(char* host, int port);
//function implement send data in socket
void Send(char* data);
//function impolemnt receive data in socket
void Receive(void);
