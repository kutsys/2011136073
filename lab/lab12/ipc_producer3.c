#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>

typedef struct {
	long mtype;
	char buf[1024];
} ms;


int main(){
	int msqid;
	ms msg;
	char tmp[20];
	char buf[1024];
	int msg_size;
	pid_t my_pid = getpid();
	key_t my_key = 3000;
	key_t my_key2 = 3001;

	if((msqid = msgget( my_key, IPC_CREAT | 0666)) == -1){
		perror("megget failed\n");
		exit(0);
	}
	while(1){
		printf("plz input \'start\' : ");
		gets(tmp);
		if(strcmp(tmp, "start") == 0){
			sprintf(msg.buf, "producer's pid : %d, std_num : 2011136073\n", my_pid);
			msg.mtype = 1000;
			msg_size = sizeof(msg) - sizeof(msg.mtype);

			msgsnd(msqid, &msg, msg_size, 0);
			break;
		}
		else{
			buf[0] = '\0';
			sleep(1);
		}
	}
	if((msqid = msgget(my_key2, IPC_CREAT | 0666)) == -1){
		perror("msgget failed\n");
		exit(0);
	}
	while(1){
		if(msgrcv(msqid, &msg, msg_size, 1000, 0) == -1){
			perror("msgrcv failed\n");
			exit(0);
		}
		else{
			printf("%s\n", msg.buf);
			break;
		}
		sleep(1);
	}

	msgctl(msqid, IPC_RMID, 0);
	return 0;
}
