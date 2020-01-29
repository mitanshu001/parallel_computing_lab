#include <stdio.h>
#include <iostream>
#include <iostream>
#include <stdlib.h> 
#include <chrono> 
#include <typeinfo>
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono; 


void initialise(int *c,int n1){
    for(int i=0;i<n1*n1;++i){
        c[i] =0;
    }
}

int main(){
    // freopen("myfile1.csv","w",stdout);
    auto start = high_resolution_clock::now();
    int SIZE = 1;
    int S = 512;
    int SZ = 32;
    int n[SIZE];
    n[0] = 4096;
    for(int i=2;i<=SIZE;++i){
       n[i-1] =  n[i-2]<<1;
    }
    double dur1[SIZE];
    double dur2[SIZE];
    double dur3[SIZE];
    double dur4[SIZE];

    for(int l=0;l<SIZE;++l){
        int n1 = n[l];
        cout<<n1<<"\t";
        int *a = new int[n1*n1];
        int *b = new int[n1*n1];
        int *c = new int[n1*n1];
        initialise(c,n1);
        for(int i=0;i<n1;++i){
            for(int j=0;j<n1;++j){
                a[i*n1 + j] = rand();
            }
        }

        for(int i=0;i<n1;++i){
            for(int j=0;j<n1;++j){
                b[i*n1 + j] = rand();
            }
        }
        auto start1 = high_resolution_clock::now();
        for(int i=0;i<n1;++i){
            for(int k=0;k<n1;++k){
                for(int j=0;j<n1;++j){
                    c[i*n1 + j]+=a[i*n1 + k]*b[k*n1 + j];
                }
            }
        }  
        auto stop1 = high_resolution_clock::now(); 
        double duration1 = duration_cast<seconds>(stop1 - start1).count(); 
        cout<<duration1<<setprecision(9)<<"\t";
        dur1[l] = duration1;


        cout<<endl;
    }
  
    return 0;
}