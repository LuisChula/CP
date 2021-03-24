#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#include <sys/time.h>

bool isInTheCircle(double x, double y)
{
   return ((x*x) + (y*y) < 1) ? true : false;
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
      double x = ((double) rand() / (RAND_MAX));
      double y = ((double) rand() / (RAND_MAX));
      if(isInTheCircle(x, y))
         within++;
   }
	return (void*)within;
}

int main(int argc, char **argv)
{
   struct timeval stop, start;
   gettimeofday(&start, NULL);

   int nRuns = atoi(argv[1]);
   int nThreads = atoi(argv[2]);
   int r = nRuns/nThreads;
   void *res;

   pthread_t threads[nThreads];
   for(int i = 0; i < nThreads; i++){
      pthread_create(&threads[i], NULL, monteCarloPi, &r);
   }

   int within = 0;
   for(int i = 0; i < nThreads; i++){
      pthread_join(threads[i], &res);
      within += (int)res;
   }

   double pi = 4.0*((double)within/(double)nRuns);

   gettimeofday(&stop, NULL);
   double time = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
   myPrint(nRuns, within, pi, time);
	
   return 0;
}