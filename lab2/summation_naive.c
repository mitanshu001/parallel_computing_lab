#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
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

    int * arr;
    int n = 100;
    int no_element_per_process;
    int sum=0;
    double exec_time = 0.0;
    if(world_rank == 0){
        // scanf("%d",&n);
        arr = (int*)malloc(n*sizeof(int));
        for(int i=0;i<n;++i){
            arr[i]=i;
        }
        no_element_per_process = n/world_size;
        // printf("process 0 starts %d",no_element_per_process);
        for(int i=1;i<world_size;++i){
            MPI_Send(&no_element_per_process,1,MPI_INT, i, 0,MPI_COMM_WORLD );
            MPI_Send(arr+no_element_per_process*i,no_element_per_process,MPI_INT,i,0,MPI_COMM_WORLD);
        }
        // printf("process 0 send complete");
    }
    else{
        MPI_Recv(&no_element_per_process,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        arr = (int*)malloc(sizeof(int)*no_element_per_process);
        MPI_Recv(arr,no_element_per_process,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // printf("receive %d ",world_rank);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    exec_time -= MPI_Wtime();
    for(int i=0;i<no_element_per_process;++i){
        sum+=arr[i];
    }

    if(world_rank!=0){
        MPI_Send(&sum,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }

    if(world_rank ==0 ){
        int temp;
        for(int i=1;i<world_size;++i){
            MPI_Recv(&temp,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            sum+=temp;
        }
        // printf("ending");
        exec_time += MPI_Wtime();
        printf("\nSummation: %d Time %f seconds",sum,exec_time);
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}