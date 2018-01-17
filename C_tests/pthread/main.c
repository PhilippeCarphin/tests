#define _REENTRANT
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
void afficher(int n, char lettre)
{
	int i,j;
	for (j=1; j<n; j++)
	{
		for (i=1; i < 10000000; i++);
		printf("%c",lettre);
		fflush(stdout);
	}
}

void *threadA(void *inutilise)
{
	afficher(100,'A');
	printf("\n Fin du thread A\n");
	fflush(stdout);
	pthread_exit(NULL);
}

void *threadC(void *inutilise)
{
	afficher(150,'C');
	printf("\n Fin du thread C\n");
	fflush(stdout);
	pthread_exit(NULL);
}

void *threadB(void *inutilise)
{
	pthread_t thC;
	pthread_create(&thC, NULL, threadC, NULL);
	afficher(100,'B');
	printf("\n %s() : Le thread B attend la fin du thread C\n",__FUNCTION__);
	pthread_join(thC,NULL);
	printf("\n Fin du thread B\n");
	fflush(stdout);
	pthread_exit(NULL);
}
int main()
{
	int i;
	pthread_t thA, thB;
	printf("\n%s() :Creation du thread A", __FUNCTION__);
	pthread_create(&thA, NULL, threadA, NULL);
	pthread_create(&thB, NULL, threadB, NULL);
	printf("\n%s() : Sleep 1 \n ", __FUNCTION__);
	sleep(1);
	printf("\n%s() : fin sleep 1 \n ", __FUNCTION__);
	//attendre la fin des threads
	printf("\n%s() : Le thread principal attend que les autres se terminent\n", __FUNCTION__);
	pthread_join(thA,NULL);
	pthread_join(thB,NULL);
	exit(0);
}
