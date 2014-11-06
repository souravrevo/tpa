#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <errno.h>
#include <locale.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>

#define __NR_xconcat	349	/* our private syscall number */

int main(int argc, char *argv[]){
	unsigned long res = 0;
	res = syscall(__NR_xconcat, (void *)"Hello", sizeof("Hello"));

	/*
		# Analysing the result from the Kernel System call. #
	*/

	if (res >= 0) {
			strcpy((char *)res, "Hello");
			printf("%s\n", (char *)res);
			mprotect((void *)res, 4096, PROT_NONE);
			printf("%s\n", (char *)res);

	} else {	/* Printing the proper error description. */
		perror("ERROR");
		exit(1);
	}

	return 0;
}

