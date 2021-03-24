#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

bool isInTheCircle(double x, double y)
{
   return ((x*x) + (y*y) < 1) ? true : false;
}

void myPrint(int nPoints, int within, double pi)
{
   printf("Total Number of points: %d\n", nPoints);
   printf("Points within circle: %d\n", within);
   printf("Pi estimation: %f\n", pi);
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
   int nRuns = atoi(argv[1]);
   int nThreads = atoi(argv[2]);
   int r = nRuns/nThreads;
   void *res;

   pthread_t t[nThreads];
   for(int i = 0; i < nThreads; i++){
      pthread_create(&t[i], NULL, monteCarloPi, &r);
   }

   int within = 0;
   for(int i = 0; i < nThreads; i++){
      pthread_join(t[i], &res);
      within += (int)res;
   }

   double pi = 4.0*((double)within/(double)nRuns);
   myPrint(nRuns, within, pi);
	
   return 0;
}