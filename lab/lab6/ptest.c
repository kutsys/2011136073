#include <stdio.h>
#include <time.h>

int main(){
	struct tm* lo_time;
	time_t cu_time;
	while(1){
		time(&cu_time);
		lo_time = localtime(&cu_time);
		printf("%d hour %d min %d sec\n", lo_time->tm_hour, lo_time->tm_min, lo_time->tm_sec);
		sleep(2);
	}
	return 0;
}
