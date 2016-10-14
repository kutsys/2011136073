#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	char block[8192];
	int in, out;
	int nread;
	if(argc == 3){
		in = open(argv[1], O_RDONLY);
		out = open(argv[2], O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	}else if(argc == 2){
		in = open(argv[1], O_RDONLY);
		out = open("a.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	}else{
		in = open("file.in", O_RDONLY);
		out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	}
	while(1){
		nread = read(in, block, sizeof(block));
		printf(".");
		if(nread<=0) {
			printf("\nComplite !\n");
			break;
		}
		write(out, block, nread);
	}
}

