
#include <bits/stdc++.h> 
using namespace std; 
using namespace std::chrono;
// For storing complex values of nth roots 
// of unity we use complex<double> 
typedef complex<double> cd; 
  
struct data{
    cd* a;
    cd* ans;
    int n;
    bool inv;
    data(cd* pa,cd* pans,int pn){
        a = pa;
        ans=pans;
        n = pn;
        inv=0;
    }
    data(cd* pa,cd* pans,int pn,bool pb){
        a = pa;
        ans=pans;
        n = pn;
        inv=pb;
    }
};

// Recursive function of FFT 
void * fft(void* aa) 
{ 
    struct data* af = (struct data*)aa;
    cd* a = af->a;
    cd* ans = af->ans;
    int n = af->n;
    bool inv=af->inv;
    // ans =  new cd[n];
    // if input contains just one element 
    if (n == 1){
        ans[0] = a[0];
        pthread_exit(NULL);
    }
    // For storing n complex nth roots of unity 
    vector<cd> w(n); 
    for (int i = 0; i < n; i++) { 
        double alpha = 2 * M_PI * i / n; 
        if(inv)alpha=-alpha;
        w[i] = cd(cos(alpha), sin(alpha)); 
    } 
    
    cd* A0  = new cd[n/2];
    cd* A1  = new cd[n/2];
    cd* y0 = new cd[n/2];
    cd* y1 = new cd[n/2];
    for (int i = 0; i < n / 2; i++) { 
  
        // even indexed coefficients 
        A0[i] = a[i * 2]; 
  
        // odd indexed coefficients 
        A1[i] = a[i * 2 + 1]; 
    } 
    pthread_t th[2];

    
    struct data d0(A0,y0,n/2,inv);

    struct data d1(A1,y1,n/2,inv);
    // Recursive call for even indexed coefficients 
   
    pthread_create(&th[0],NULL,fft,(void*)&d0);
    pthread_create(&th[1],NULL,fft,(void*)&d1);

    // for storing values of y0, y1, y2, ..., yn-1. 
    for(int i=0;i<2;++i){
        pthread_join(th[i],NULL);
    }
    delete[] A0;
    delete[] A1;
    for (int k = 0; k < n / 2; k++) { 
        ans[k] = y0[k] + w[k] * y1[k]; 
        ans[k + n / 2] = y0[k] - w[k] * y1[k]; 
    } 
    delete[] y0;
    delete[] y1;
    pthread_exit(NULL);
} 


// vector<cd> inv_fft(vector<cd>& a) 
// { 
//     int n = a.size(); 
  
//     // if input contains just one element 
//     if (n == 1) 
//         return vector<cd>(1, a[0]); 
  
//     // For storing n complex nth roots of unity 
//     vector<cd> w(n); 
//     for (int i = 0; i < n; i++) { 
//         double alpha = 2 * M_PI * i / n; 
//         w[i] = cd(cos(-alpha), sin(-alpha)); 
//     } 
  
//     vector<cd> A0(n / 2), A1(n / 2); 
//     for (int i = 0; i < n / 2; i++) { 
  
//         // even indexed coefficients 
//         A0[i] = a[i * 2]; 
  
//         // odd indexed coefficients 
//         A1[i] = a[i * 2 + 1]; 
//     } 
  
//     // Recursive call for even indexed coefficients 
//     vector<cd> y0 = inv_fft(A0);  
  
//     // Recursive call for odd indexed coefficients 
//     vector<cd> y1 = inv_fft(A1); 
  
//     // for storing values of y0, y1, y2, ..., yn-1. 
//     vector<cd> y(n); 
  
//     for (int k = 0; k < n / 2; k++) { 
//         y[k] = y0[k] + w[k] * y1[k]; 
//         y[k + n / 2] = y0[k] - w[k] * y1[k]; 
//     } 
//     return y; 
// } 

void printPoly(cd* poly, int n) 
{ 
    for (int i=0; i<n; i++) 
    { 
       cout << poly[i].real(); 
       if (i != 0) 
        cout << "x^" << i ; 
       if (i != n-1) 
       cout << " + "; 
    } 
    cout<<"\n";
} 

  
// Driver code 
int main() 
{ 
    freopen("fft_output.csv","a",stdout);
    srand(time(0));
    for(int N=(1<<6);N<=(1<<12);N*=4)
    {
        cd *a = new cd[2*N];
        cd *b = new cd[2*N];
        cd *af = new cd[2*N];
        cd *bf = new cd[2*N];
        for(int i=0;i<N;++i)a[i] = (double)(rand()%10);
        for(int i=0;i<N;++i)b[i] = (double)(rand()%10);
        for(int i=N;i<2*N;++i){
            a[i] = b[i] = 0.0;
        }
        auto start = high_resolution_clock::now(); 
        // printPoly(a,2*N-1);
        // printPoly(b,2*N-1);
        pthread_t th[3];
        struct data da(a,af,2*N);
        pthread_create(&th[0],NULL,fft,(void*)&da);
        struct data db(b,bf,2*N);
        pthread_create(&th[1],NULL,fft,(void*)&db);
        for(int i=0;i<2;++i){
            pthread_join(th[i],NULL);
        }
        // printPoly`()
        delete[] a;
        delete[] b;
        for(int i=0;i<2*N;++i){
            af[i] = af[i]*bf[i];
        } 
        struct data dans(af,bf,2*N,1);
        pthread_create(&th[2],NULL,fft,(void*)&dans);
        pthread_join(th[2],NULL);
        for(int i=0;i<2*N-1;++i){
            bf[i]/=(2*N);
        } 
        delete[] af;
        // printPoly(bf,2*N-1);
        delete[] bf;
        auto stop = high_resolution_clock::now();
	    auto duration = duration_cast<milliseconds>(stop - start);
        cout<<N<<"\t"<<duration.count()<<endl;
    }
    return 0; 
} 