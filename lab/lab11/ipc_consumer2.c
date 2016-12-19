#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <fcntl.h>

int main(){
	int shmid;
	key_t keyval;
	void *shared_memory = (void *)0;
	pid_t my_pid = getpid();
	char buf[1024];
	struct shmid_ds stats;

	keyval = 1000;
	shmid = shmget(keyval, 1024, IPC_CREAT | 0666);
	if(shmid == -1){
		perror("shmget failed\n");
		exit(0);
	}
	shared_memory = shmat(shmid, (void *)0, 0);
	if(shared_memory == (void *)-1){
		perror("shared memory attacthing failed\n");
		exit(0);
	}
	while(1){
		shmctl(shmid, IPC_STAT, &stats);
		if(stats.shm_lpid == my_pid){
			sleep(2);
		}
		else{
			printf("%s\n", (char *)shared_memory);
			sprintf(buf, "%s, consumer's pid : %d, std_name : Woo yonggeun",(char *)shared_memory, my_pid);
			strcpy((char *) shared_memory, buf);
			if(shmdt(shared_memory) == -1){
				perror("shared memory dettaching failed\n");
				exit(0);
			}
			break;
		}
	}

	return 0;
}
