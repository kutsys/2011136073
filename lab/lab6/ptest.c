#include <stdio.h>
#include <time.h>

int main(){
	struct tm* lo_time;
	time_t cu_time;
	pid_t my_ppid;


	while(1){
		my_ppid = getppid();
		if(my_ppid == 1){
			printf("ptest : I'm dead...");
			return 0;
		}
		time(&cu_time);
		lo_time = localtime(&cu_time);
		printf("%d hour %d min %d sec\n", lo_time->tm_hour, lo_time->tm_min, lo_time->tm_sec);
		sleep(2);
	}
	return 0;
}
