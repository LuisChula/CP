#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>
#include <time.h>

long findPi(long numPoints) {
    long i, pointsInCircle = 0;
    double x, y;
    unsigned int seed;
    #pragma omp parallel private(seed,x,y) shared(numPoints) reduction(+:pointsInCircle)
    {
    	seed = (unsigned int) omp_get_thread_num() ^ (unsigned int) time(NULL);
    	srand(seed);
    	printf("%u\n", seed);
    	#pragma omp for
    	for(i = 0; i < numPoints; i++) {
            x = (double) rand_r(&seed) / (RAND_MAX);
            y = (double) rand_r(&seed) / (RAND_MAX);
            if(x*x + y*y < 1)
                pointsInCircle++;
        }
    }
    return pointsInCircle;
}

int main(int argc, char **argv){
    double runtime = omp_get_wtime();
    long numPoints = atol(argv[1]);
    int numThreads = 1;
    if(argc > 2)
        numThreads = atoi(argv[2]);
    omp_set_num_threads(numThreads);
    long pointsInCircle = findPi(numPoints);
    double pi = 4 * (double) pointsInCircle / (double) numPoints;
    runtime = omp_get_wtime() - runtime;
    
    printf("%li of %li points are within the circle.\n", pointsInCircle, numPoints);
    printf("Pi estimation: %lf\n", pi);
    printf("Time wasted in this trash: %lf\n", runtime);
    return 0;
}

