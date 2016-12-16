#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>



int main(){
	char buf[20];
	int res, pipe_id, pipe_id2;
	char buffer[PIPE_BUF + 1];
	pid_t my_pid = getpid();

	sprintf(buffer, "2011136073, producer's pid : %d\n", my_pid);
	
	printf("input the \"start\" : ");
	while(1){
		gets(buf);
		if(strcmp(buf, "start") == 0){
			if(access("./named_pipe", F_OK) == -1){
				res = mkfifo("./named_pipe", 0777);
				if(res != 0) exit(EXIT_FAILURE);
			}
			printf("Process %d opening FIFO\n", getpid());
			pipe_id = open("./named_pipe", O_WRONLY); // | O_NONBLOCK);
			res = write(pipe_id, buffer, PIPE_BUF);
			break;
		}
		else{
			buf[0] = '\0';
		}
		printf("plz reinput the \"start\" : ");
	}
	while(1){
		if((pipe_id2 = open("./named_pipe2", O_RDONLY)) < 0){
			printf("fifo open failed\n");
			sleep(1);
			continue;
		}
		else{
			if(read(pipe_id2, buffer, PIPE_BUF) < 0){
				printf("read pipe2 fail\n");
			}
			else{
				printf("%s\n", buffer, my_pid);
				break;
			}
		}
	}
	close(pipe_id);
	close(pipe_id2);


	return 0;
}
