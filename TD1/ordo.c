#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <sched.h>

#define NB_THREADS 5

pthread_t tid[NB_THREADS];
pthread_attr_t tattr[NB_THREADS];

void thread_fils(int id) {
	printf("je suis le thread fils. \n\tMon id est %d.\n\tMon pid est %d. \n\tMon tid est %u\n",
		id, getpid(),(int)pthread_self());
}

int main() {
	int i;
	int ret;
	void *status;
	for(i = 0; i < NB_THREADS ; i++) {
		struct sched_param param;

		/* initialize an attribute to the default value */
		ret = pthread_attr_init(&tattr[i]);
		if (ret){
			printf("%s\n", "Error: Attribute initialize.\n");
			exit(EXIT_FAILURE);
		}

		/* set the scheduling policy to SCHED_OTHER */
		ret = pthread_attr_setschedpolicy(&tattr[i], SCHED_FIFO);
		if (ret){
			printf("%s\n", "Error: Set scheduling policy.\n");
			exit(EXIT_FAILURE);
		}
		param.sched_priority = i+1;

		ret = pthread_create(&tid[i], &tattr[i], (void*) thread_fils, i);
		if (ret){
			printf("%s\n", "Error: Creating thread.\n");
			exit(EXIT_FAILURE);
		}
	}

	for (i = 0; i < NB_THREADS; ++i){
		ret = pthread_join(tid[i], &status);
		if (ret) {
			printf("Error: Cannont join thread.\n");
			exit (EXIT_FAILURE);
		}
	}

}