#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(){
	int sock1, sock2;
	int addr_size, option;
	int len;
	struct sockaddr_un con_addr;
	struct sockaddr_un pro_addr;
	char buf1[1024+5];
	char buf2[1024+5];
	pid_t my_pid = getpid();

	if(access("/tmp/sockfile", F_OK) == 0){
		unlink("/tmp/sockfile");
	}
	sock1 = socket(PF_FILE, SOCK_STREAM, 0);
	if(sock1 == -1){
		perror("sock creation failed\n");
		exit(1);
	}
	memset(&con_addr, 0, sizeof(con_addr));
	con_addr.sun_family = AF_UNIX;
	strcpy(con_addr.sun_path, "/tmp/sockfile");
	if(bind(sock1, (struct sockaddr *)&con_addr, sizeof(con_addr)) == -1){
		perror("bind error\n");
		exit(1);
	}
	while(1){
		if(listen(sock1, 5) == -1){
			perror("set mode waitting failed\n");
			exit(1);
		}
		addr_size = sizeof(pro_addr);
		sock2 = accept(sock1, (struct sockaddr *)&pro_addr, &addr_size);

		if(sock2 == -1){
			perror("accepting failed\n");
			exit(1);
		}

		read(sock2, buf1, 1024);
		printf("%s\n", buf1);

		sprintf(buf2, "%s, consumer's pid : %d, std_name : Woo yonggeun\n", buf1, my_pid);
		write(sock2, buf2, strlen(buf2)+1);
		close(sock2);
	}


	return 0;
}
