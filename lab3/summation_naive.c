#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 7
int main(int argc, char** argv) {
    freopen("summation_naive2.csv","+a",stdout);
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
        n*=8;
        MPI_Barrier(MPI_COMM_WORLD);
        long long * arr;
        long long no_element_per_process;
        long long sum=0;
        double exec_time = 0.0;
        if(world_rank == 0){
            arr = (long long*)malloc(n*sizeof(long long));
            for(long long i=0;i<n;++i){
                arr[i]=i;
            }
            no_element_per_process = n/world_size;
            // printf("process 0 starts %d",no_element_per_process);
            for(long long i=1;i<world_size;++i){
                MPI_Send(&no_element_per_process,1,MPI_LONG_LONG, i, 0,MPI_COMM_WORLD );
                MPI_Send(arr+no_element_per_process*i,no_element_per_process,MPI_LONG_LONG,i,0,MPI_COMM_WORLD);
            }
            // printf("process 0 send complete");
        }
        else{
            MPI_Recv(&no_element_per_process,1,MPI_LONG_LONG,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            arr = (long long*)malloc(sizeof(long long)*no_element_per_process);
            MPI_Recv(arr,no_element_per_process,MPI_LONG_LONG,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // printf("receive %d \n",world_rank);
            // printf("haf");
        }

        MPI_Barrier(MPI_COMM_WORLD);
        exec_time -= MPI_Wtime();
        for(long long i=0;i<no_element_per_process;++i){
            sum+=arr[i];
        }

        if(world_rank!=0){
            MPI_Send(&sum,1,MPI_LONG_LONG,0,0,MPI_COMM_WORLD);
        }

        if(world_rank ==0 ){
            long long temp;
            for(long long i=1;i<world_size;++i){
                MPI_Recv(&temp,1,MPI_LONG_LONG,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                sum+=temp;
            }
            // printf("ending");

        }
        MPI_Barrier(MPI_COMM_WORLD);
        exec_time += MPI_Wtime();
        printf("%lld,%f\n",n,exec_time);
    }



    // Finalize the MPI environment.
    MPI_Finalize();
}