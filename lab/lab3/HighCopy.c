#include <stdio.h>

int main(int argc, char* argv[]){
	char buf[8192];
	FILE* rfp;
	FILE* wfp;
	char ch;
	int count = 0;
	if(argc == 3){
		rfp = fopen(argv[1], "r");
		wfp = fopen(argv[2], "w");
	}else if(argc == 2){
		rfp = fopen(argv[1], "r");
		wfp = fopen("HighCopy.out", "w");
	}else{
		rfp = fopen("HighCopyTest.in", "r");
		wfp = fopen("HighCopyTest.out", "w");
	}

	if((rfp != NULL) && (wfp != NULL)){
		while((ch = fgetc(rfp)) != EOF){
			fputc(ch, wfp);
			count++;
			if(count%64 == 0) printf("*");
		}
	}
	printf("\nComplite !\n");
	return 0;
}
