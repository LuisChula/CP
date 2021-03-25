#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

struct ThreadParams {
    int nPoints;
    unsigned int state;
};

double rnd(void* p_mystate) {
   unsigned int *mystate = p_mystate;
   return (double) rand_r(mystate) / (RAND_MAX);
}

void myPrint(int nPoints, int within, double pi, double time)
{
   printf("Total Number of points: %d\n", nPoints);
   printf("Points within circle: %d\n", within);
   printf("Pi estimation: %f\n", pi);
   printf("Real time: %f\n", time);
}

void* monteCarloPi(void *args)
{
   struct ThreadParams *readParams = args;
   int v = readParams->nPoints;
   int within = 0;
   for(int i = 0; i < v; i++){
      double x = rnd(&readParams->state);
      double y = rnd(&readParams->state);
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

   unsigned int states[nThreads];
   pthread_t threads[nThreads];
   for(int i = 0; i < nThreads; i++){
      struct ThreadParams tp;
      tp.nPoints = r;
      tp.state = states[i];
      pthread_create(&threads[i], NULL, monteCarloPi, &tp);
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