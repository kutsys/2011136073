#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int flags;
struct tm* lo_time;
time_t cu_time;

void *subproc(int *args){
	int count = 0;
	int r;
	int thread_num = *args + 1;
	srand(time(NULL));
	while(1){
		count++;
		r = rand()%10 + 1;
		time(&cu_time);
		lo_time = localtime(&cu_time);
		printf("thread num : %3d, %2d hour %2d min %2d sec, count : %2d sleeptime : %2d\n", thread_num, lo_time->tm_hour, lo_time->tm_min, lo_time->tm_sec, count, r);
		if(count == 20){
			flags++;
			printf("%d said : I'am finished\n", thread_num);
			pthread_exit("well done\n");
		}
		sleep(r);
	}

}



int main(){
	int res[10];
	int i;
	pthread_t proc_thread[10];
	int *args;
	void *thread_result[10];

	printf("2011136073 Woo Yonggeun\n");
	for(i = 0; i < 10; i++){
		*args = i;
		res[i] = pthread_create(&(proc_thread[i]), NULL, subproc, args);
		if(res[i] != 0){
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
		usleep(200);
	}
	for(i = 0; i < 10; i++){
		pthread_detach(proc_thread[i]);
	}
	sleep(20);
	while(1){
		if(flags == 10){
			printf("All Tasks are finished!\n");
			return 0;
		}
		usleep(200);
	}



	return 0;
}
