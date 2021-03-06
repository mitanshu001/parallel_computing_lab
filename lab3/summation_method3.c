#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define SIZE 7

int main(int argc, char** argv) {
    freopen("summation_method3.csv","a+",stdout);
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

    long long n = 8;

    for(long long k=1;k<=SIZE;++k){
        n*=1LL*8;
        long long * arr;
        long long * rec_arr;
        long long no_element_per_process;
        long long sum=0;
        double exec_time = 0.0;
        long long start;
        long long height = (long long)log2((double)world_size);
        no_element_per_process = n/world_size;
        // printf("%lld %lld",n,height);
        if(world_rank == 0){
            arr = (long long*)malloc(n*sizeof(long long));
            
            for(long long i=1;i<=n;++i){
                arr[i-1]=i;
            }
            start = 0;
        } 
        long long sz  = n;
        rec_arr = (long long*)malloc(no_element_per_process*sizeof(long long));
        MPI_Scatter(arr, no_element_per_process,MPI_LONG_LONG, rec_arr, no_element_per_process, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        exec_time -= MPI_Wtime();
        for(int i=0;i<no_element_per_process;++i){
            sum+=rec_arr[i];
        }

        long long global_sum;
        MPI_Reduce(&sum,&global_sum,1,MPI_LONG_LONG, MPI_SUM,0,MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        exec_time += MPI_Wtime();
        if(world_rank ==0 ){
            printf("%lld  %f \n",n, exec_time);
        }
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}