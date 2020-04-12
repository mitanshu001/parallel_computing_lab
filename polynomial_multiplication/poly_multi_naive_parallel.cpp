#include <bits/stdc++.h> 
using namespace std; 

struct params{
    int poly1_l;
    int poly1_r;
    int poly2_l;
    int poly2_r;
    int *poly1;
    int *poly2;
    int **poly3;
    params(){

    }
    params(int l1,int l2,int r1,int r2,int * pol,int *pol2,int **pol3){
        poly1_l = l1;
        poly1_r = l2;
        poly2_l  = r1;
        poly2_r = r2;
        poly1 = pol;
        poly2 = pol2; 
        poly3 = pol3;
    }
};

struct params2 : params{
    int target;
    int * ans;
    void par(int l1,int l2,int r1,int r2,int * pol,int *pol2,int *an,int t){
        target =t;
        poly1_l = l1;
        poly1_r = l2;
        poly2_l  = r1;
        poly2_r = r2;
        poly1 = pol;
        poly2 = pol2; 
        ans = an;
    }
};

void * fill(void * p_params){
    struct params2 *param = (struct params2*)p_params;
    int poly1_l = param->poly1_l;  
    int poly1_r = param->poly1_r;
    int poly2_l = param->poly2_l;
    int poly2_r = param->poly2_r;
    int* poly1=  param->poly1;
    int* poly2 = param->poly2;
    int* ans = param->ans;
    int n1 = poly1_r - poly1_l;
    int n2 = poly2_r - poly2_l;
    int target = param->target;
    // int g= 0;
    // int *r = &g;

    for(int i=poly1_l;i<poly1_r;++i){
        int j = target - i;
        if(j>=poly2_l && j<poly2_r){
            ans[target]+=poly1[i]*poly2[j];
        }
    }
    // *poly3 = r;
    pthread_exit(NULL);
}


void* naive_prod(void* p_params){

    struct params *param = (struct params*)p_params;
    int poly1_l = param->poly1_l;  
    int poly1_r = param->poly1_r;
    int poly2_l = param->poly2_l;
    int poly2_r = param->poly2_r;
    int* poly1=  param->poly1;
    int* poly2 = param->poly2;
    int** poly3 = param->poly3;
    int n1 = poly1_r - poly1_l;
    int n2 = poly2_r - poly2_l;
    
    int *ans = new int[n1+n2];
    memset(ans,0,sizeof(int));
    pthread_t th[n1+n2];
    params2 p[n1+n2];
    for(int i=0;i<n1+n2;++i){
        p[i].par(poly1_l,poly1_r,poly2_l,poly2_r,poly1,poly2,ans,i);
        int tn = pthread_create(th + i,NULL,&fill, (void*)(p+ i));
    }
    for(int i=0;i<n1+n2;++i){
        pthread_join(th[i],NULL);
    }
    *poly3 = ans;
    pthread_exit(NULL);
}



int *multiply(int A[], int B[], int m, int n) 
{ 
    int * res;
    params p(0,m,0,n,A,B,&res);
    pthread_t th;
    pthread_create(&th,NULL,&naive_prod,&p);
    pthread_join(th,NULL);
    return res;
} 

void printPoly(int poly[], int n) 
{ 
    for (int i=0; i<n; i++) 
    { 
       cout << poly[i]; 
       if (i != 0) 
        cout << "x^" << i ; 
       if (i != n-1) 
       cout << " + "; 
    } 
    cout<<"\n";
} 

int main() 
{ 
  // for(int )
    int A[] = {5, 0, 10, 6}; 
    int B[] = {1, 2, 4}; 
    int m = sizeof(A)/sizeof(A[0]); 
    int n = sizeof(B)/sizeof(B[0]); 
  
    cout << "First polynomial is : "; 
    printPoly(A, m); 

    cout << "Second polynomial is : "; 
    printPoly(B, n); 
  
    int *prod = multiply(A, B, m, n); 
  
    cout << "Product polynomial is : "; 
    printPoly(prod, m+n-1); 
  
    return 0; 
} 