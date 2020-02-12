#include <mpi.h>
#include <stdio.h>
#include <math.h>
int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    // printf("world size %d",world_size);
    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

// for(int size = 8;size<= 2<<21;size*=8){
    int size = (int)pow(8,5);
    int number[size];
    int number2[size];
    // number = world_rank;
    MPI_Send(number, size, MPI_INT, (world_rank+1)%world_size, 0, MPI_COMM_WORLD);
    printf("send complete\n");
    MPI_Recv(number2, size , MPI_INT, ((world_rank -1 )%world_size + world_size )%world_size, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    printf("rec complete\n");
    // Print off a hello world message
    // printf("Hello world from processor %s, rank %d out of %d processors %d received\n",
        //    processor_name, world_rank, world_size, number2);
// }
    // Finalize the MPI environment.
    MPI_Finalize();
}
