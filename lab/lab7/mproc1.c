#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>




int main(){
	int ends = 0;
	int buf[1];
	char tmp[2][10];
	int tmpcallcount;
	int i;
	pid_t pid[10];
	int fds[10][2];
	int checklist[10];
	FILE *fp;


	printf("2011136073, Woo YongGeun\n");
	for(i = 0; i < 10; i++){
		pipe(fds[i]);
		checklist[i] = 1;
		pid[i] = fork();
		if(pid[i] == 0) {	//	case child process
			sprintf(tmp[0], "%d", fds[i][0]);
			sprintf(tmp[1], "%d", fds[i][1]);
			if(fcntl(fds[i][0], F_SETFL, O_NONBLOCK == -1)){
				exit(0);
			}
			if(fcntl(fds[i][1], F_SETFL, O_NONBLOCK == -1)){
				exit(0);
			}// file descriptor set on nonblocking mode
			execl("./subproc", "./subproc", tmp[0], tmp[1], NULL);
			break;
		}
	}

	while(1){
		for(i=0; i<10; i++){
			if(checklist[i]){
				if(read(fds[i][0], buf, sizeof(buf))){
					if(buf[0] == 20){
						if(kill(pid[i], SIGKILL) == 0){
							close(fds[i][0]);
							close(fds[i][1]);
							ends++;
							printf("%d kill!\n", pid[i]);
							checklist[i] = 0;
						}
					}
				}
			}
			if(ends == 10) {
				printf("finished\n");
				return 0;
			}
		}
		usleep(200);
	}

	return 0;
}
