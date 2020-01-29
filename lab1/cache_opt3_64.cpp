#include <stdio.h>
#include <iostream>
#include <iostream>
#include <stdlib.h> 
#include <chrono> 
#include <typeinfo>
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono; 
#define low 64
void recur(int *a,int *b,int *c,int n1,int nc,int ia,int ja,int ib,int jb,int ic,int jc){
    if(nc <= low){
        for(int i=0;i<nc;++i){
            for(int k=0;k<nc;++k){
                for(int j=0;j<nc;++j){
                    c[(ic+ i)*n1 + j+jc]+=a[(ia+ i)*n1 + k+ja]*b[(ib+k)*n1 + j + jb];
                }
            }
        }  
    }
    else{
        nc/=2;
        recur(a,b,c,n1,nc,ia,ja,ib,jb,ic,jc);
        recur(a,b,c,n1,nc,ia,ja+nc,ib+nc,jb,ic,jc);
        recur(a,b,c,n1,nc,ia,ja,ib,jb+nc,ic,jc+nc);
        recur(a,b,c,n1,nc,ia,ja+nc,ib+nc,jb+nc,ic,jc+nc);
        recur(a,b,c,n1,nc,ia+nc,ja,ib,jb,ic+nc,jc);
        recur(a,b,c,n1,nc,ia+nc,ja+nc,ib+nc,jb,ic+nc,jc);
        recur(a,b,c,n1,nc,ia+nc,ja,ib,jb+nc,ic+nc,jc+nc);
        recur(a,b,c,n1,nc,ia+nc,ja+nc,ib+nc,jb+nc,ic+nc,jc+nc);
    }
}

void initialise(int *c,int n1){
    for(int i=0;i<n1*n1;++i){
        c[i] =0;
    }
}

int main(){
    freopen("myfile3_64.csv","w",stdout);
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

        recur(a,b,c,n1,n1,0,0,0,0,0,0);
        auto stop1 = high_resolution_clock::now(); 
        double duration1 = duration_cast<seconds>(stop1 - start1).count(); 
        cout<<duration1<<setprecision(9)<<"\t";


        // dur1[l] = duration1;
        // int *c2 = new int[n1*n1];
        // initialise(c2,n1);
        // for(int i=0;i<n1;++i){
        //     for(int k=0;k<n1;++k){
        //         for(int j=0;j<n1;++j){
        //             c2[i*n1 + j]+=a[i*n1 + k]*b[k*n1 + j];
        //         }
        //     }
        // }

        // for(int i=0;i<n1;++i){
        //     for(int j=0;j<n1;++j){
        //         // cout<<"ji";
        //         if(c2[i*n1+j] - c[i*n1+j]!=0){
        //             cout<<c2[i*n1+j] - c[i*n1+j]<<"\t";
        //         }
        //     }
        // }  

        cout<<endl;
    }
  
    return 0;
}