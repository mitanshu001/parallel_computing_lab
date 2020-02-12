#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1

int main(int argc, char** argv) {
    freopen("matrix_mul_col.csv","a+",stdout);
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
        n*=1LL*8;
        long long ar[n][n];
        long long B[n];
        long long no_element_per_process = n/world_size;
        long long arr[no_element_per_process][n];
        long long b[no_element_per_process]; 
        long long bn[n];
        
        if(world_rank == 0 ){
            for(int i=0;i<n;++i){
                for(int j=0;j<n;++j){
                    ar[i][j] = i*n+j;
                }
                B[i] = 1;
            }
        }

        MPI_Scatter(B,no_element_per_process,MPI_LONG_LONG,b,no_element_per_process,MPI_LONG_LONG,0,MPI_COMM_WORLD);
        // MPI_Scatter(ar,no_element_per_process*n,MPI_LONG_LONG,arr,no_element_per_process*n,MPI_LONG_LONG,0,MPI_COMM_WORLD);
        // MPI_Allgather(b,no_element_per_process,MPI_LONG_LONG,bn,no_element_per_process,MPI_LONG_LONG,MPI_COMM_WORLD);

        for(int i=0;i<n;++i){
            bn[i] = 0;
            for(int j=0;j<no_element_per_process;++j){
                bn[i] += arr[i][j]*b[j];
            }
        }

        

        for(int j=0;j<no_element_per_process;++j){
            printf("%d %lld\n",world_rank,b[j]);
        }
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}