#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define SIZE 7

int cmpfunc (const void * a, const void * b) {
   return ( *(long long*)a - *(long long*)b );
}


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
        n*=1LL*8;
        long long * arr;
        long long * rec_arr;
        long long no_element_per_process;
        long long sum=0;
        double exec_time = 0.0;

        no_element_per_process = n/world_size;
        // printf("%lld %lld",n,height);
        if(world_rank == 0){
            arr = (long long*)malloc(n*sizeof(long long));
            
            for(long long i=1;i<=n;++i){
                arr[i-1]=i;
            }

        } 
        long long sz  = n;
        rec_arr = (long long*)malloc(no_element_per_process*sizeof(long long));
        MPI_Scatter(arr, no_element_per_process,MPI_LONG_LONG, rec_arr, no_element_per_process, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
        qsort(rec_arr,no_element_per_process,sizeof(long long),cmpfunc);
        
        
        if(world_rank ==0 ){
            printf("n: %lld sum: %lld \n",n, sum);
        }
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}