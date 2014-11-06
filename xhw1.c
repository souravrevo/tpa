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
#include <sys/types.h>
#include <pthread.h>

#define __NR_xconcat	349	/* our private syscall number */

pthread_t t1,t2;
unsigned long global;

void *thread1(void *t){

	unsigned long res = 0;
	res = syscall(__NR_xconcat, NULL, 4096);

	//printf("Thread1 pid: %d\n", gettid());
	
	if (res >= 0) {
			printf("%lu\n", res);
			//global = res;

	} else {	/* Printing the proper error description. */
		perror("ERROR");
	}

	//strcpy((void *)global ,"Hello");
	return 0;
}

void *thread2(void *t){

	unsigned long res = 0;
	res = syscall(__NR_xconcat, NULL, 4096);

	//printf("Thread2 pid: %d\n", gettid());
	
	if (res >= 0) {
			printf("%lu\n", res);

	} else {	/* Printing the proper error description. */
		perror("ERROR");
	}

	//*((char *)global) = 14;
	
	return 0;
}

int main(int argc, char *argv[]){
	unsigned long res = 0;
	res = syscall(__NR_xconcat, NULL, 4096);

	printf("Main pid: %d\n", getpid());
	
	pthread_create(&t1, NULL, thread1, NULL);
	pthread_create(&t2, NULL, thread2, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	if (res >= 0) {
			printf("%lu\n", res);
			//strcpy((void *)res ,"Hello");
	} else {
		perror("ERROR");
		exit(1);
	}

	return 0;
}

