#include <stdio.h>
#include <stdlib.h>

int main(){
	printf("$HOME : %s\n$PS1 : %s\n$PATH : %s\n$LD_LIBRARY_PATH : %s\n", getenv("HOME"), getenv("PS1"), getenv("PATH"), getenv("LD_LIBRARY_PATH"));
	setenv("TEST_ENV", "1234", 1);	// 1 : overwrite, 0 : non-overwrite
	printf("$TEST_ENV : %s\n", getenv("TEST_ENV"));
	return 0;
}
