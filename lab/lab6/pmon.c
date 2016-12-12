#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void monitor(int sig){
	FILE* p;
	char buf[10] = {'\0'};
	if((p = popen("ps -ef | grep ptest | grep -v 'grep' | awk '{print $2}'", "r")) == NULL){
		printf("popen error");
	}
	if(fgets(buf, 10, p) == NULL){
		printf("not existed\n>> ");
	}
	else{
		printf("running\n>> ");
	}
	pclose(p);
	fflush(stdout);
	alarm(5);
}

int main(){
	char menu;
	char buff[10];
	FILE* tmp;
	int i = 0;

	(void) signal(SIGALRM, monitor);
	alarm(5);

	printf("Manual\nQ : quit pmon\nK : kill ptest\nS : start ptest\nR : quit ptest and restart ptest\n");
	while(1){
		printf(">> ");
		//scanf("%c", &menu);
		menu = getc(stdin);
		__fpurge(stdin);	//	buffer cleaning
		if(menu == 'Q' || menu == 'q'){
			printf("pmon said : Good Bye\n");
			break;
		}
		else if(menu == 'K' || menu == 'k'){
			if((tmp = popen("ps -ef | grep ptest | grep -v 'grep' | awk '{print $2}'", "r")) == NULL){
				printf("popen error2");
			}
			if(fgets(buff, 10, tmp) != NULL){
				system("kill -9 `ps -ef | grep ptest | grep -v 'grep' | awk '{print $2}'`");
				printf("pmon said : killed ptest\n");
			}
			else{
				printf("pmon said : no exist ptest\n");
			}
			pclose(tmp);
		}
		else if(menu == 'S' || menu == 's'){
			if((tmp = popen("ps -ef | grep ptest | grep -v 'grep' | awk '{print $2}'", "r")) == NULL){
				printf("popen error3");
			}
			if(fgets(buff, 10, tmp) == NULL){
				printf("start\n");
				alarm(0);
				execl("./ptest", "./ptest", NULL);
			}
			else{
				printf("already running\n");
			}
			pclose(tmp);
		}
		else if(menu == 'R' || menu == 'r'){
			if((tmp = popen("ps -ef | grep ptest | grep -v 'grep' | awk '{print $2}'", "r")) == NULL){
				printf("popen error4");
			}
			if(fgets(buff, 10, tmp) == NULL){
				printf("newly started\n");
				alarm(0);
				execl("./ptest", "./ptest", NULL);
			}
			else{
				system("kill -19 `ps -ef | grep ptest | grep -v 'grep' | awk '{print $2}'`");
				alarm(0);
				execl("./ptest", "./ptest", NULL);
			}
			pclose(tmp);
		}
		else{
			printf("incorrect commnad. please retry\n");
			continue;
		}
		for(i=0; i<10; i++){
			buff[i] = '\0';
		}
	}


	return 0;
}
