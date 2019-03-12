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
/*The function sendHandshake implement send request to server with contents
 *GET /socket.io/1/?EIO=3&transport=polling&b64=true HTTP/1.1\r\n
 *HOST: hostname
 *Origin: DucVu
 *Connection: keep-alive
 *
 * ---Parameter char* host -- ip address or hostname domain
 * ---Return value void
 * */
void sendHandshake(char* host){
	char t_request[DATA_BUFFER_LEN] = "GET /socket.io/1/?EIO=3&transport=polling&b64=true HTTP/1.1\r\n";
	char* request = strcat(t_request, "HOST: ");
	request = strcat(request, host);
	request = strcat(request, "\r\n");
	request = strcat(request, "Origin: DucVu\r\n");
	request = strcat(request, "Connection: keep-alive\r\n");
	//Send request to server
	sendSOCKET(request);
#ifdef DEBUG
	printf("%s", request);
#endif
}




