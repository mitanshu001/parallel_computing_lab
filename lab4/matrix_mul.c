#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1

int main(int argc, char** argv) {
    freopen("odd_even_sort.csv","a+",stdout);
    // printf("START\n");
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    long long n = 1;

    for(long long k=1;k<=SIZE;++k){
        n*=1LL*64;
        
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}