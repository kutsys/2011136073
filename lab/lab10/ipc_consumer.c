#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
 
int main(){
	char buffer[PIPE_BUF + 1];
	char buffer2[PIPE_BUF + 1];
	int res, pipe_id;
	pid_t my_pid = getpid();

	while(1){
		if((res = open("./named_pipe", O_RDWR)) < 0){
			printf("fifo open failed");
			sleep(2);
			continue;
		}
		else{
			if(read(res, buffer, PIPE_BUF) < 0){
				printf("read pipe fail");
			}
			else{
				printf("%s\n", buffer);
				break;
			}

		}

	}
	sprintf(buffer2, "%s, Name : Woo Yonggeun, consumer's pid : %d", buffer, my_pid);
	if(access("./named_pipe2", F_OK) == -1){
		res = mkfifo("./named_pipe2", 0777);
		if(res != 0) exit(EXIT_FAILURE);

	}
	printf("Process %d opening FIFO\n", getpid());
	pipe_id = open("./named_pipe2", O_WRONLY | O_NONBLOCK);
	res = write(pipe_id, buffer2, PIPE_BUF);
	close(pipe_id);

	

	return 0;
}
