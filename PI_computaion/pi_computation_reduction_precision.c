#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_THREADS 16

long long steps;
double step;

int main (int argc, const char *argv[]) {

    int i;
    double pi, sum = 0.0;
    double start, delta;

    

    // Compute parallel compute times for 1-MAX_THREADS
    for (steps=100000; steps<= 1000000000; steps*=10) {
        step = 1.0/(double) steps;
        printf(" running on %lld steps: ", steps);

        // This is the beginning of a single PI computation 
        omp_set_num_threads((MAX_THREADS));

        sum = 0.0;
        double start = omp_get_wtime();


        #pragma omp parallel for shared(step), reduction(+:sum)
        for (i=0; i < steps; i++) {
            double x = (i+0.5)*step;
            sum += 4.0 / (1.0+x*x); 
        }

        // Out of the parallel region, finialize computation
        pi = step * sum;
        delta = omp_get_wtime() - start;
        printf("PI = %.16g computed in %.4g seconds\n", pi, delta);

    }
    

}