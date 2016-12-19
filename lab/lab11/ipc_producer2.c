#include <time.h>
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
	char tmp[20];
	char buf[1024];
	struct shmid_ds stats;

	keyval = 1000;
	shmid = shmget(keyval, 1024, IPC_CREAT | 0666);
	if(shmid == -1){	//	shared memory error check
		perror("shmget failed\n");
		exit(0);
	}
	shared_memory = shmat(shmid, (void *)0, 0);
	if(shared_memory == (void *)-1){
		perror("shared memory attaching failed\n");
		exit(0);
	}
	while(1){
		printf("input the \"start\" : ");
		gets(tmp);
		if(strcmp(tmp, "start") == 0){
			sprintf(buf, "producer's pid : %d, stu_num : 2011136073", my_pid);
			strcpy((char *)shared_memory, buf);
			if(shmdt(shared_memory) == -1){
				perror("shared memory dettching failed\n");
				exit(0);
			}
			break;
		}
		else{
			buf[0] = '\0';
		}
	}
	while(1){
		shmctl(shmid, IPC_STAT, &stats);
		if(stats.shm_nattch == 1){
			sleep(2);
		}
		else{
			shared_memory = shmat(shmid, (void *)0, 0);
			if(shared_memory == (void *)-1){
				perror("shared memory attaching failed\n");
				exit(0);
			}
			strcpy(buf, (char *)shared_memory);
			printf("%s\n", buf);
			break;
		}
	}
	if(shmdt(shared_memory) == -1){
		perror("shared memory dettaching failed\n");
		exit(0);
	}

	/* exit program process */
	/* shared memory delete from kernel */
	if(shmctl(shmid, IPC_RMID, 0) == -1){
		perror("shared memory control failed\n");
		exit(0);
	}
	return 0;
}
