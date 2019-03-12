#include "Socket.h"


/*The function init_Socket implement initialize socket and connect to server
 *
 * */
int init_Socket(char* host, int port){
	//Verify Create socket successfull
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("\nSocket creation error\n");
		return -1;
	}
	printf("Socket create!\n");
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_addr.s_addr	= inet_addr(host);
	serv_addr.sin_family		= AF_INET;
	serv_addr.sin_port		= htons(port);

	//Verify connect to hostname and port
	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		printf("\nConnection failed\n");
		return -1;
	}
	printf("Connected\n");
}

/*The function sendSocket implement send data to server
 *parameter char* data -- data will be send to server
 *return void
 * */
void sendSocket(char* data){
	send(sock, data, strlen(data), 0);
}
/*The function receive socket implement receive data from server
 *parameter void
 *return void
 * */
void receiveSocket(void){
	buffer = (char*)malloc( DATA_BUFFER_LEN * sizeof(char));
	read(sock, buffer, DATA_BUFFER_LEN);	
}


