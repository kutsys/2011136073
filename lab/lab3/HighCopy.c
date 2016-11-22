#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]){
	char buf[8192];
	FILE* rfp;
	FILE* wfp;
	char ch;
	clock_t start, current;

	if(argc == 3){
		if((rfp = fopen(argv[1], "r")) == NULL)
			printf("fopen error");
		if((wfp = fopen(argv[2], "w")) == NULL)
			printf("fopen error2");
	}else if(argc == 2){
		if((rfp = fopen(argv[1], "r")) == NULL)
			printf("fopen error");
		if((wfp = fopen("HighCopy.out", "w")) == NULL)
			printf("fopen error2");
	}else{
		if((rfp = fopen("HighCopyTest.in", "r")) == NULL)
			printf("fopen error");
		if((wfp = fopen("HighCopyTest.out", "w")) == NULL)
			printf("fopen error2");
	}
	printf("HighCopy start\n");
	start = clock();
	if((rfp != NULL) && (wfp != NULL)){
		while(1){
			ch = fgetc(rfp);
			if(feof(rfp) == 0){
				fputc(ch, wfp);
				current = clock();
				if((current - start) > 1000){
					start = clock();
					printf("*");
				}
			}
			else break;
		}
	}
	printf("\nComplite !\n");
	fclose(rfp);
	fclose(wfp);
	return 0;
}
