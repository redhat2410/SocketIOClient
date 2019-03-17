#include "delay.h"

void delay(int number_of_second){
	int milli_seconds = 1000 * number_of_second;
	clock_t start_time = clock();
	while(clock() < start_time + milli_seconds);
}
