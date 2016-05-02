#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>

pthread_t tid;
pthread_attr_t attr;

void thread_fils() {
	int err;
	int i;
	err = pthread_set_name_np(pthread_self(), "thread_TR");
	if (err) {
		printf("erreur thread set_name\n");
		exit(EXIT_FAILURE);
	}
	printf("Thread : entrez un caractere: ");
	scanf("%s", &i);
	pthread_exit(NULL);
}

int main() {
	int i;
	int err;
  	mlockall(MCL_CURRENT|MCL_FUTURE);

	err = pthread_set_name_np(pthread_self(), "thread_principal");
	if (err) {
		printf("erreur main set_name\n");
		exit(EXIT_FAILURE);
	}
	printf("Main : entrez un caractere: ");
	scanf("%s", &i);

	err = pthread_attr_init(&attr);	
	if (err) {
		printf("erreur main attr_init\n");
		exit(EXIT_FAILURE);
	}
 	err = pthread_create(&tid, &attr, (void *) thread_fils, NULL);
	if (err) {
		printf("erreur main create\n");
		exit(EXIT_FAILURE);
	}
	err = pthread_join(tid, (void *) NULL);
	if (err) {
		printf("erreur main join\n");
		exit(EXIT_FAILURE);
	}
}
