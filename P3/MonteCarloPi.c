#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void myPrint(int nPoints, int within, double pi)
{
   printf("Total Number of points: %d\n", nPoints);
   printf("Points within circle: %d\n", within);
   printf("Pi estimation: %f\n", pi);
}

double rnd(void* p_mystate) {
   unsigned int *mystate = p_mystate;
   return (double) rand_r(mystate) / (RAND_MAX);
}

int main(int argc, char **argv) {
    
    if(argc < 3){
        printf("./MonteCarloPi <nPoints> <nThreads>\n");
        return 1;
    }
    
    int nPoints = atoi(argv[1]);
    int nThreads = atoi(argv[2]);
    
    int within = 0;
    unsigned int seed = time(NULL);

    omp_set_num_threads(nThreads);
    #pragma omp parallel for reduction (+:within,seed)
    for(int i = 0; i < nPoints; i++){
        double x = rnd(&seed);
        double y = rnd(&seed);
        if((x*x) + (y*y) < 1)
            within++;
    }   

    double pi = 4.0*((double)within/(double)nPoints);

    myPrint(nPoints, within, pi);

    return 0;
}
