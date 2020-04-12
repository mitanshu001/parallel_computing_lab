#include <stdio.h>
struct params{
    int poly1_l;
    int poly1_r;
    int poly2_l;
    int poly2_r;
    int *poly1;
    int *poly2;
    int **poly3;
    params(int l1,int l2,int r1,int r2,int * pol,int *pol2){
        poly1_l = l1;
        poly1_r = l2;
        poly2_l  = r1;
        poly2_r = r2;
        poly1 = pol;
        poly2 = pol2; 
    }
};



void* karatsuba(void * p_params){
    struct params *param = (struct params*)p_params;
    
    int poly1_l = param->poly1_l;  
    int poly1_r = param->poly1_l;
    int poly2_l = param->poly2_l;
    int poly2_r = param->poly2_r;
    int* poly1=  param->poly1;
    int * poly2 = param->poly2;
    int **poly3 = param->poly3;

    int poly1_mid = poly1_l + (poly1_r - poly1_l)/2;
    int poly2_mid = poly2_l + (poly2_r - poly2_l)/2;
    int n1 = poly1_r - poly1_l;
    int n2 = poly2_r - poly2_l;
    
    int *a;
    pthread_t th1;
    params p1(poly1_mid,poly1_r,poly2_mid,poly2_r,poly1,poly2);
    int tn1 = pthread_create(th1,NULL,&karatsuba,(void*)p1);

    pthread_create()

    int *d;
    int *intermediate = new int

}


int *multiply(int A[], int B[], int m, int n) 
{ 
   int *prod = new int[m+n-1]; 

   for (int i = 0; i<m+n-1; i++) 
     prod[i] = 0; 

    recur(0,m-1,A,B);

  
   return prod; 
} 

void printPoly(int *poly, int n) 
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
    int B[] = {1, 2, 4,5}; 
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