#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	char menu;
	pid_t tmp_pid;
	pid_t ptest_pid;
	int ptest_stat;
	FILE* rfp;


	tmp_pid = fork();
	if(tmp_pid == -1){
		printf("failed fork");
	}
	else if(tmp_pid == 0){
		while(1){
			printf("this is fuck?");
			system("ps -ef | grep ptest | grep -v 'grep' | awk '{print $2}' > ptest_pid.txt");
			if((rfp = fopen("ptest_pid.txt", "r")) == NULL){
				printf("fopen error");
			}
			if(feof(rfp)){
				printf("not existed");
			}
			else{
				printf("running");
			}
			fclose(rfp);
			sleep(5);
		}
	}
	printf("Manual\nQ : quit pmon\nK : kill ptest forcely\nS : start ptest\nR : kill ptest and restart ptest\n");
	while(1){
		printf(">> ");
		scanf("%c", &menu);
		__fpurge(stdin);// buffer cleaning
		if(menu == 'Q' || menu == 'q'){
			printf("pmon said : Good Bye\n");
			break;
		}
		else if(menu == 'K' || menu == 'k'){
			system("kill -9 `ps -ef | grep ptest | grep -v 'grep' | awk '{print $2}'`");
			printf("pmon said : killed ptest\n");
		}
		else if(menu == 'S' || menu == 's'){
			system("ps -ef | grep ptest | grep -v 'grep' | awk '{print $2}' > ptest_pid.txt");
			if((rfp = fopen("ptest_pid.txt", "r")) == NULL){
					printf("file open error");
			}
			if(feof(rfp)){	// if EOF, return true
				//tmp_pid = fork();
				//if(tmp_pid == 0) {
					execl("./ptest", "./ptest");
				/*}
				else if(tmp_pid == -1){
					printf("failed fork");
					exit(1);
				}*/
			}
			else{
				printf("already running\n");
			}
			fclose(rfp);
		}
		else if(menu == 'R' || menu == 'r'){
			if((rfp = fopen("ptest_pid.txt", "r")) == NULL){
				printf("file open error");
			}
			if(feof(rfp)){	//if EOF, return true
				printf("newly started");
				//tmp_pid = fork();
				//if(tmp_pid == 0){
					execl("./ptest", "./ptest");
				/*}
				else if(tmp_pid == -1){
					printf("failed fork");
					exit(1);
				}*/
			}
			else{
				system("kill -19 `ps -ef | grep ptest | grep -v 'grep' | awk '{print $2}'`");	//	-19 is quit. not kill
				//tmp_pid = fork();
				//if(tmp_pid == 0){
					execl("./ptest", "./ptest");
				/*}
				else if(tmp_pid == -1){
					printf("failed fork");
					exit(1);
				}*/
			}
			fclose(rfp);
		}
		else{
			printf("incorrect command. please Retry\n");
			continue;
		}


	}
	return 0;
}
