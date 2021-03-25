#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

static unsigned int seed = 0;

double rnd() {
    return (double) rand_r(&seed) / (RAND_MAX);
}

void myPrint(int nPoints, int within, double pi, double time)
{
   printf("Total Number of points: %d\n", nPoints);
   printf("Points within circle: %d\n", within);
   printf("Pi estimation: %f\n", pi);
   printf("Real time: %f\n", time);
}

void* monteCarloPi(void *arg)
{
   int v = *(int*)arg;
   int within = 0;
   for(int i = 0; i < v; i++){
      double x = rnd();
      double y = rnd();
      if((x*x) + (y*y) <= 1)
         within++;
   }
   int* result = malloc(sizeof(int));
   *result = within;
	return (void*) result;
}

int main(int argc, char **argv)
{
   struct timeval stop, start;
   gettimeofday(&start, NULL);

   int nRuns = atoi(argv[1]);
   int nThreads = atoi(argv[2]);
   int r = nRuns/nThreads;
   int* res;

   pthread_t threads[nThreads];
   for(int i = 0; i < nThreads; i++){
      pthread_create(&threads[i], NULL, monteCarloPi, &r);
   }

   int within = 0;
   for(int i = 0; i < nThreads; i++){
      pthread_join(threads[i], (void**) &res);
      within += *res;
      free(res);
   }

   double pi = 4.0*((double)within/(double)nRuns);

   gettimeofday(&stop, NULL);
   double time = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
   myPrint(nRuns, within, pi, time);
	
   return 0;
}