#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int main(){
	int sock;
	struct sockaddr_un con_addr;
	char tmp[20];
	char buf[1024+5];
	char rcvbuf[1024+5];
	pid_t my_pid = getpid();
	
	if((sock = socket(PF_FILE, SOCK_STREAM, 0)) < 0){
		perror("sock error\n");
		exit(0);
	}
	memset(&con_addr, 0, sizeof(con_addr));
	con_addr.sun_family = AF_UNIX;
	strcpy(con_addr.sun_path, "/tmp/sockfile");
	while(1){
		printf("plz input \'start\' : ");
		gets(tmp);
		if(strcmp(tmp, "start") == 0){
			sprintf(buf, "producer's pid : %d, std_num : 2011136073", my_pid);
			if(connect(sock, (struct sockaddr *)&con_addr, sizeof(con_addr)) == -1){
				perror("connect error");
				exit(1);
			}
			write(sock, buf, strlen(buf) + 1);
			break;
		}
		else{
			buf[0] = '\0';
			sleep(1);
		}
	}
	read(sock, rcvbuf, 1024);
	printf("%s\n", rcvbuf);
	close(sock);

	return 0;
}
