#include "SocketIOClient.h"


/*The function ConnectSocketIO implement verify create socket and connect
 *to server, start process hand shake between client and server, send and
 *receive request and response between client and server
 *---Parameter char* host -- ip address server ( hostname or domain )
 *---Parameter int   port -- port connect to server ( port open by server)
 *---Return value is 0 or 1 ( fail or success )
 * */
uint8_t ConnectSocketIO(char* host, int port){
	//Verify create socket and connect to server
	while(!initSOCKET(host, port)){
#ifdef DEBUG
		printf("Connect fail");
#endif
	}
#ifdef DEBUG
	prinf("connect success");
#endif;
	//start process handshake between client and server
	hostname = host;
	PORT = port;
	//send request of client to server
	sendHandshake(hostname);
	//receive response from server
	return readHandshake();	
}
