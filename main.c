#include "ClientContext.h"
int main(){
	char* hello = "Hello Server";
	if(connectSOCK("192.168.100.9", 80)){
		setTimeoutSOCK(50);
		writeSOCK(hello, strlen(hello));
		char* buf = (char*)malloc(2048 * sizeof(char));
		if(stateSOCK()){
			readSOCK(buf, 2048);
			printf("\t%s\n", buf);
		}
	}
	return 0;
}
