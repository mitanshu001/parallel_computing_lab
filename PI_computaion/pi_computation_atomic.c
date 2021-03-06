#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_THREADS 41

static long steps = 1000000000;
double step;

int main (int argc, const char *argv[]) {

    int i,j;
    double pi, sum = 0.0;
    double start, delta;

    step = 1.0/(double) steps;

    // Compute parallel compute times for 1-MAX_THREADS
    for (j=1; j<= MAX_THREADS; j+=5) {

        printf(" running on %d threads: ", j);

        // This is the beginning of a single PI computation 
        omp_set_num_threads(j);

        sum = 0.0;
        double start = omp_get_wtime();


        #pragma omp parallel for shared(step)
        for (i=0; i < steps; i++) {
            double x = (i+0.5)*step;
            #pragma omp atomic
            sum += 4.0 / (1.0+x*x); 
        }

        // Out of the parallel region, finialize computation
        pi = step * sum;
        delta = omp_get_wtime() - start;
        printf("PI = %.16g computed in %.4g seconds\n", pi, delta);

    }
    

}