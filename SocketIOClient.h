#define __SOCKET_IO_CLIENT_H

#include "Socket.h"

#define DEBUG

#define SID_LEN	24

int PORT;
char* dataptr;
char databuffer[];
char* hostname;
char* sid;
char* key;


uint8_t ConnectSocketIO(char* host, int port);
uint8_t ConnectedSocketIO(void);
void disconnectSocketIO(void);
uint8_t reconnectSocketIO(char* host, int port);
uint8_t monitor(void);
void sendMessage(char* message);
void sendSocketIO(char* RID, char* Rname, char* Rcontent);
void heartbeat(int select);
void clear(void);

int parser(int index);
void sendHandshake(char* host);
uint8_t readHandshake(void);
void readLine(void);
void findColon(char which);
void terminateCommand(void);
void eatHeader(void);

