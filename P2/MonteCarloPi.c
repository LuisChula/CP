#include <stdio.h>
#include <pthread.h>

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
void* monteCarloPi(void *arg)
{
   int v = *(int*)arg;
   for(int i = 0; i < 100; i++){
      printf("Thread %d => %d\n", v, i);
   }
	return NULL;
}

int main()
{
   int nThreads = 4;
   int nRuns = 100;
   int r = nRuns/nThreads;

   pthread_t t[nThreads];
   printf("Before Thread\n");
   for(int i = 0; i < nThreads; i++){
      pthread_create(&t[i], NULL, monteCarloPi, &i);
   }

   for(int i = 0; i < nThreads; i++){
      pthread_join(t[i], NULL);
   }
	printf("After Thread\n");
	
   return 0;
}
