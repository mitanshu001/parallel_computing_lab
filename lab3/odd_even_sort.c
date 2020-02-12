#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 7

int cmpfunc (const void * a, const void * b) {
   return ( *(long long*)a - *(long long*)b );
}

long long* merge(long long* arr,long long * rec_arr,long long no_element_per_process){
        long long *mod_arr;
        mod_arr = (long long*)malloc(sizeof(long long)*2*no_element_per_process);
        int h=0;
        int j=0;
        int i=0;
        while(h< no_element_per_process && j<no_element_per_process){
            if(arr[h] < rec_arr[j]){
                mod_arr[i++] = arr[h++];
            }else{
                mod_arr[i++] = rec_arr[j++];
            }
        }
        while(h<no_element_per_process){
            mod_arr[i++] = arr[h++];
        }
        while(j<no_element_per_process){
            mod_arr[i++] = rec_arr[j++];
        }
        return mod_arr;
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
        long long * ar;
        long long * arr;
        long long * rec_arr;
        long long no_element_per_process;

        double exec_time = 0.0;

        no_element_per_process = n/world_size;
        // printf("%lld %lld",n,height);
        if(world_rank == 0){
            ar = (long long*)malloc(n*sizeof(long long));
            
            for(long long i=1;i<=n;++i){
                ar[i-1]=n-i;
                // printf("q%lld ",ar[i-1] );
            }

        } 
        long long sz  = n;
        arr = (long long*)malloc(no_element_per_process*sizeof(long long));
        MPI_Scatter(ar, no_element_per_process,MPI_LONG_LONG, arr, no_element_per_process, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        exec_time -= MPI_Wtime();
        qsort(arr,no_element_per_process,sizeof(long long),cmpfunc);

        // long long *rec_arr;
        rec_arr = (long long*)malloc(sizeof(long long)*no_element_per_process);
        long long phase = 1;
        
        while(phase <= world_size ){
            // printf("%d %lld\n",world_rank,phase);    
            if(phase%2){
                if(world_rank!=0 && world_rank%2 && world_rank!=world_size-1){        
                    MPI_Recv(rec_arr,no_element_per_process,MPI_LONG_LONG,world_rank+1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                    long long * mod_arr = merge(arr,rec_arr,no_element_per_process);
                    for(int p=0;p<no_element_per_process;++p){
                        arr[p] = mod_arr[p];
                    }
                    // memcpy(arr,mod_arr,no_element_per_process);
                    MPI_Send(mod_arr+no_element_per_process,no_element_per_process,MPI_LONG_LONG,world_rank+1,0,MPI_COMM_WORLD);
                }else if(world_rank!=0 && world_rank%2==0){
                    MPI_Send(arr,no_element_per_process,MPI_LONG_LONG,world_rank-1,0,MPI_COMM_WORLD);
                    MPI_Recv(arr,no_element_per_process,MPI_LONG_LONG,world_rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);  
                }
            }else{
                if(world_rank%2==0 && world_rank!=world_size-1){
                    // rec_arr = (long long*)malloc(sizeof(long long)*no_element_per_process);
                    MPI_Recv(rec_arr,no_element_per_process,MPI_LONG_LONG,world_rank+1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                    long long * mod_arr = merge(arr,rec_arr,no_element_per_process);
                    for(int p=0;p<no_element_per_process;++p){
                        arr[p] = mod_arr[p];
                    }
                    MPI_Send(mod_arr+no_element_per_process,no_element_per_process,MPI_LONG_LONG,world_rank+1,0,MPI_COMM_WORLD);
                }else if(world_rank%2==1){
                    MPI_Send(arr,no_element_per_process,MPI_LONG_LONG,world_rank-1,0,MPI_COMM_WORLD);
                    MPI_Recv(arr,no_element_per_process,MPI_LONG_LONG,world_rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);  
                }
            }
            phase++;
        }
        // MPI_Barrier(MPI_Comm)
        exec_time += MPI_Wtime();
        // printf("%d complete\n",world_rank);
        MPI_Gather(arr,no_element_per_process,MPI_LONG_LONG,ar,no_element_per_process,MPI_LONG_LONG,0,MPI_COMM_WORLD);

    }

    // Finalize the MPI environment.
    MPI_Finalize();
}