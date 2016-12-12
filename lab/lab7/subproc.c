#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

pid_t my_pid = 0;
pid_t my_ppid = 0;
struct tm* lo_time;
time_t cu_time;
int count = 0;
int fds[2];

int test_funct(){
	int buf[1] = {++count};
	time(&cu_time);
	lo_time = localtime(&cu_time);
	printf("pid num : %5d, %2d hour %2d min %2d sec, count : %2d ", my_pid, lo_time->tm_hour, lo_time->tm_min, lo_time->tm_sec, count);
	write(fds[1], buf, sizeof(buf));
	return 0;
}

int main(int argc, char* argv[]){
	int r = 0;
	my_pid = getpid();
	fds[0] = atoi(argv[1]);
	fds[1] = atoi(argv[2]);
	write(fds[1], "0\0", 2);
	while(1){
		srand(time(NULL) + my_pid);
		//srand(time(NULL));
		test_funct();
		r = rand()%10 + 1;
		printf("sleep time : %d\n", r);
		sleep(r);
		my_ppid = getppid();	// Get My Parent is who
		if(my_ppid == 1) break;	// Check My Parent is dead
	}
	
	close(fds[0]);
	close(fds[1]);
	return 0;
}
