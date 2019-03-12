#include "Socket.h"


/*The function init_Socket implement initialize socket and connect to server
 *parameter char* host -- ip address hostname
 *parameter int port   -- port server
 *return int 0 or 1 ( failed or success )
 * */
int initSOCKET(char* host, int port){
	//Verify Create socket successfull
	if((client = socket(AF_INET, SOCK_STREAM, 0)) < 0){
#ifdef DEBUG
		printf("\nSocket creation error\n");
#endif
		return 0;
	}
#ifdef DEBUG
	printf("Socket create!\n");
#endif
	memset(&serv_addr, '0', sizeof(serv_addr));
	//setup host ip address
	serv_addr.sin_addr.s_addr	= inet_addr(host);
	serv_addr.sin_family		= AF_INET;
	//Setup port server
	serv_addr.sin_port		= htons(port);

	//Verify connect to hostname and port
	if(connect(client, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
#ifdef DEBUG
		printf("\nConnection failed\n");
#endif
		return 0;
	}
#ifdef DEBUG
	printf("Connected\n");
#endif
	return 1;
}

/*The function sendSocket implement send data to server
 *parameter char* data -- data will be send to server
 *return void
 * */
void sendSOCKET(char* data){
	send(client, data, strlen(data), 0);
}
/*The function receive socket implement receive data from server
 *parameter void
 *return void
 * */
char* receiveSOCKET(void){
	char* buffRead = (char*)malloc( DATA_BUFFER_LEN * sizeof(char));
	read(client, buffRead, DATA_BUFFER_LEN);
	return buffRead;	
}

/*The function disconnectSOCKET implement disconnect socket between client and server
 *parameter void
 *return void
 * */
void disconnectSOCKET(void){
	shutdown(client, SHUT_RDWR);
}
