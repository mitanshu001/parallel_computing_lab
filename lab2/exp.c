// #include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define SIZE 7

int main(){
    int t =4;
    // printf("%lld",(long long)log2((double)t));
    int * arr;
    arr = (int*)malloc(sizeof(int));
    arr[0] = 3;
    arr = (int *)malloc(2*sizeof(int));
    arr[1]=4;
    printf("%d %d",arr[0],arr[1]);
}