#include <bits/stdc++.h> 
using namespace std; 
using namespace std::chrono;
#define LOW 50
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

    for(int i=poly1_l;i<poly1_r;++i){
        int j = target - i;
        if(j>=poly2_l && j<poly2_r){
            ans[target]+=poly1[i]*poly2[j];
        }
    }
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
    // cout<<poly1_l<<"*"<<poly1_r<<" "<<poly2_l<<" "<<poly2_r<<endl;
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



void* karatsuba(void* p_params){
    struct params *param = (struct params*)p_params;
    int poly1_l = param->poly1_l;  
    int poly1_r = param->poly1_r;
    int poly2_l = param->poly2_l;
    int poly2_r = param->poly2_r;
    int* poly1=  param->poly1;
    int* poly2 = param->poly2;
    int** poly3 = param->poly3;

    int poly1_mid = poly1_l + (poly1_r - poly1_l)/2;
    int poly2_mid = poly2_l + (poly2_r - poly2_l)/2;
    int n1 = poly1_r - poly1_l;
    int n2 = poly2_r - poly2_l;
    
    if(n1<=LOW || n2<= LOW){
        // cout<<poly1_l<<" "<<poly1_r<<" "<<poly2_l<<" "<<poly2_r<<endl;
        params p(0,n1,0,n2,poly1+poly1_l,poly2+poly2_l,poly3);
        pthread_t th;
        pthread_create(&th,NULL,&naive_prod,&p);
        pthread_join(th,NULL);
        // cout<<" "<<poly1_l<<" "<<poly1_r<<" "<<poly2_l<<" "<<poly2_r<<endl;
        pthread_exit(NULL);
    }
    else{
        // cout<<"sr"<<endl;
        int *ans2;
        pthread_t th1;
        params p1(poly1_mid,poly1_r,poly2_mid,poly2_r,poly1,poly2,&ans2);
        int tn1 = pthread_create(&th1,NULL,&karatsuba,&p1);

        int *ans1;
        pthread_t th2;
        params p2(poly1_l,poly1_mid,poly2_l,poly2_mid,poly1,poly2,&ans1);
        int tn2 = pthread_create(&th2,NULL,&karatsuba,&p2);

        pthread_join(th1,NULL);
        pthread_join(th2,NULL);
        // cout<<"hu"<<endl;
        int* left = new int[poly1_mid - poly1_l];
        int* right = new int[poly2_mid - poly2_l];

        for(int i=0;i<poly1_mid - poly1_l;++i){
            left[i] = poly1[poly1_l + i] + poly1[poly1_mid + i];
        }

        for(int i=0;i<poly2_mid - poly2_l;++i){
            right[i] = poly2[poly2_l + i] + poly2[poly2_mid + i];
        }

        int *ans3;
        pthread_t th3;
        params p3(0,poly1_mid-poly1_l,0,poly2_mid - poly2_l , left,right,&ans3);
        int tn3 = pthread_create(&th3,NULL,&karatsuba,&p3);

    
        pthread_join(th3,NULL);
        // cout<<"yu[t"<<endl;
        delete [] left,right;

        for(int i=0;i<2*(poly1_mid-poly1_l);++i){
            ans3[i] -= (ans1[i] + ans2[i]);
        }

        int * ans  = new int[n1 + n2];
        memset(ans,0,sizeof(int)*(n1+n2));

        for(int i=0;i < poly1_mid-poly1_l + poly2_mid-poly2_l; ++i){
            ans[i] +=  ans1[i];
        }

        int bs = poly1_mid-poly1_l + poly2_mid-poly2_l;
        for(int i=0;i < poly1_r - poly1_mid + poly2_r - poly2_mid ;++i )
        {
            ans[bs + i] += ans2[i];
        }   

        bs = poly1_mid - poly1_l;
        for(int i=0;i<poly1_mid - poly1_l + poly2_mid - poly2_l;++i){
            ans[i+bs] +=ans3[i];
        }

        *poly3 = ans;
        delete[] ans1,ans2,ans3;
        // cout<<"yup"<<endl;
        pthread_exit(NULL);
    }
}


int *multiply(int A[], int B[], int m, int n) 
{ 
    int * res;
    params p(0,m,0,n,A,B,&res);
    pthread_t th;
    pthread_create(&th,NULL,&karatsuba,&p);
    pthread_join(th,NULL);
    return res;
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


int main() 
{ 
    
    freopen("karatsuba_output.csv","a",stdout);
    for(int N=(1<<6);N<=(1<<12);N*=4){
        int A[N];
        int B[N];
        for(int i=0;i<N;++i)A[i] = rand()%100;
        for(int i=0;i<N;++i)B[i] = rand()%100;
        int m = sizeof(A)/sizeof(A[0]); 
        int n = sizeof(B)/sizeof(B[0]); 
    
        auto start = high_resolution_clock::now(); 
        int *prod = multiply(A, B, m, n); 
        auto stop = high_resolution_clock::now();
	    auto duration = duration_cast<milliseconds>(stop - start);
        cout<<N<<"\t"<<duration.count()<<endl;
    }

  
    return 0; 
} 