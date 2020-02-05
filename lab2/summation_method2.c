#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define SIZE 1

int main(int argc, char** argv) {
    freopen("summation_method2.csv","w",stdout);
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
        n*=1LL*16;
        long long * arr;
        long long no_element_per_process;
        long long sum=0;
        double exec_time = 0.0;
        long long start;
        long long height = (long long)log2((double)world_size);
        // printf("%lld %lld",n,height);
        if(world_rank == 0){
            arr = (long long*)malloc(n*sizeof(long long));
            for(long long i=0;i<n;++i){
                arr[i]=i;
            }
            no_element_per_process = n/world_size;
            start = 0;
            printf("worldd_rank: %d\n",world_rank);
        }
        
        long long sz  = n;
        // printf("world_rank : %d\n",world_rank);
        // MPI_Barrier(MPI_COMM_WORLD);
        printf("world_rank : %d\n",world_rank);
        while(height>0){
            printf("height : %lld  %d\n",height,world_rank );
            sz = sz>>1;
            if( world_rank%(1<<height) == 0 ){
                MPI_Send(arr + sz, sz, MPI_LONG_LONG, 1<<(height-1) + world_rank , 0, MPI_COMM_WORLD);
            }
            else if( world_rank%(1<<(height-1)) == 0 ){
                arr = (long long*)malloc(sz*sizeof(long long));
                MPI_Recv(arr, sz, MPI_LONG_LONG, world_rank - 1<<(height-1), 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            height--;
        }
        printf("%d %lld \n",world_rank,sz);

        for(int i=0;i<no_element_per_process;++i){
            sum+=arr[i];
        }
        MPI_Barrier(MPI_COMM_WORLD);
        long long depth = 1;
        height = (long long)log2((double)world_size);
        printf("after barrier");
        while(depth <= height){ 
            printf("depth: %lld %d\n",depth,world_rank);
            if(world_rank%(1<<depth) == 0 ){
                long long temp;
                MPI_Recv(&temp, 1, MPI_LONG_LONG, 1<<(depth-1) + world_rank , 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                sum+=temp;
            }
            else if( world_rank%(1<<(depth-1)) == 0 ){
                MPI_Send(&sum, 1, MPI_LONG_LONG, world_rank - 1<<(depth-1), 0    , MPI_COMM_WORLD);
            }
            depth++;
        }
        if(world_rank ==0 ){
            printf("sum: %lld ",sum);
        }
    }

        
    //     else{
    //         MPI_Recv(&no_element_per_process,1,MPI_LONG_LONG,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    //         arr = (long long*)malloc(sizeof(long long)*no_element_per_process);
    //         MPI_Recv(arr,no_element_per_process,MPI_LONG_LONG,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //         // printf("receive %d ",world_rank);
    //     }

    //     MPI_Barrier(MPI_COMM_WORLD);
    //     exec_time -= MPI_Wtime();
    //     for(long long i=0;i<no_element_per_process;++i){
    //         sum+=arr[i];
    //     }

    //     if(world_rank!=0){
    //         MPI_Send(&sum,1,MPI_LONG_LONG,0,0,MPI_COMM_WORLD);
    //     }

    //     if(world_rank ==0 ){
    //         long long temp;
    //         for(long long i=1;i<world_size;++i){
    //             MPI_Recv(&temp,1,MPI_LONG_LONG,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    //             sum+=temp;
    //         }
    //         // printf("ending");
    //         exec_time += MPI_Wtime();
    //         printf("%lld,%f\n",n,exec_time);
    //     }
    // }



    // Finalize the MPI environment.
    MPI_Finalize();
}