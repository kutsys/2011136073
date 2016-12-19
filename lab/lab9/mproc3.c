#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

int flags = 0;
int ncount = 0;
int to_count = 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void subproc(int *args){
	int count = 0;
	int r;
	int thread_num = *args + 1;
	srand(time(NULL) + thread_num);
	while(1){
		r = rand()%10 + 1;
		pthread_mutex_lock(&mutex);
		if((ncount == 0) && (to_count == (count + 1))){
			count++;
			ncount++;
			printf("thread num : %3d, count : %2d, sleeptime : %2d\n", thread_num, count, r);
			pthread_mutex_unlock(&mutex);
		}
		else if((ncount == 9) && (to_count == (count + 1))){
			count++;
			ncount = 0;
			to_count++;
			printf("thread num : %3d, count : %2d, sleeptime : %2d\n", thread_num, count, r);
			pthread_mutex_unlock(&mutex);
		}
		else if(to_count == (count + 1)){
			count++;
			ncount++;
			printf("thread num : %3d, count : %2d, sleeptime : %2d\n", thread_num, count, r);
			pthread_mutex_unlock(&mutex);
		}
		else{
			pthread_mutex_unlock(&mutex);
			sleep(r);
			continue;
		}
		if(count == 20){
			printf("%d said : I'am finished\n", thread_num);
			flags++;
			pthread_exit("well done\n");
		}
		sleep(r);
	}
}

int main(){
	int i;
	int res[10];
	pthread_t proc_thread[10];
	int *args;
	void *thread_result[10];

	printf("2011136073 Woo Yonggeun\n");
	for(i = 0; i < 10; i++){
		*args = i;
		res[i] = pthread_create(&(proc_thread[i]), NULL, subproc, args);
		if(res[i] != 0){
			perror("thread creation failed");
			exit(1);
		}
		usleep(200);
	}
	for(i = 0; i < 10; i++){
		pthread_detach(proc_thread[i]);
	}
	sleep(20);
	while(1){
		if(flags == 10){
			printf("All Task are finished!\n");
			return 0;
		}
		sleep(1);
	}
	pthread_mutex_destory(&mutex);
	return 0;
}
