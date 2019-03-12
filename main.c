#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(void){
	char* host = "127.0.0.1";
	char t_request[2048] = "GET /socket.io/1/?EIO=3&transport=polling&b64=true HTTP/1.1\r\n";
	char* request = strcat(t_request, "HOST: ");
	request = strcat(request, host);
	printf("%s", request);
	return 0;
}
