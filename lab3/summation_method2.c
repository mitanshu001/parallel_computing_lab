#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define SIZE 7

int main(int argc, char** argv) {
    freopen("summation_method2.csv","a+",stdout);
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

        while(height>0){
            sz = sz>>1;
            if( world_rank%(1<<height) == 0 ){
                int h = height-1;
                h = 1<<h;
                // printf("send %lld %d %d \n",height,h + world_rank ,world_rank);
                MPI_Send(arr + sz, sz, MPI_LONG_LONG, h + world_rank , 0, MPI_COMM_WORLD);
            }
            else if( world_rank%(1<<(height-1)) == 0 ){
                int h = height-1;
                h = 1<<h;
                // printf("rec %lld %d %d \n",height, world_rank - h,world_rank);
                arr = (long long*)malloc(sz*sizeof(long long));
                MPI_Recv(arr, sz, MPI_LONG_LONG, world_rank - h, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            height--;
        }
        // printf("ARR: %d %lld \n",world_rank,no_element_per_process);
        MPI_Barrier(MPI_COMM_WORLD);
        exec_time -= MPI_Wtime();
        for(int i=0;i<no_element_per_process;++i){
            sum+=arr[i];
        }
        long long depth = 1;
        height = (long long)log2((double)world_size);
        while(depth <= height){ 
            if(world_rank%(1<<depth) == 0 ){
                long long temp;
                MPI_Recv(&temp, 1, MPI_LONG_LONG, (1<<(depth-1)) + world_rank , 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                sum+=temp;
            }
            else if( world_rank%(1<<(depth-1)) == 0 ){
                MPI_Send(&sum, 1, MPI_LONG_LONG, world_rank - (1<<(depth-1)), 0    , MPI_COMM_WORLD);
            }
            depth++;
        }
        MPI_Barrier(MPI_COMM_WORLD);
        exec_time += MPI_Wtime();
        if(world_rank ==0 ){
            printf("%lld,%f \n",n, exec_time);
        }
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}