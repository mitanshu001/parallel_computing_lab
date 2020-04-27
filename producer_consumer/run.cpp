#include <bits/stdc++.h>
using namespace std;
//default 1000 1000 100 5
int main(){
    freopen("prod_cons_lock_free.csv","a",stdout);
    int no_of_consumers =1000;
    int no_of_producers = 1000;
    int BSIZE = 5;
    int no_of_buffers = 100;

    string s = "./lockfree.exe ";
    // varying no_pf_producers
    for(int no_of_producers=10;no_of_producers<=10000;no_of_producers*=5){
        string temp = s + to_string(no_of_producers)  + " " + to_string(no_of_consumers) + " " + to_string(no_of_buffers)+ " " + to_string(BSIZE);
        char char_array[temp.length() + 1]; 
        // copying the contents of the 
        // string to char array 
        // cout<<temp<<endl;
        strcpy(char_array, temp.c_str()); 
        std::system(char_array);
    }
    no_of_producers = 1000;
    cout<<endl;
    for(int no_of_consumers=10;no_of_consumers<=10000;no_of_consumers*=5){
        string temp = s + to_string(no_of_producers)  + " " + to_string(no_of_consumers) + " " + to_string(no_of_buffers)+ " " + to_string(BSIZE);
        char char_array[temp.length() + 1]; 
        // copying the contents of the 
        // string to char array 
        // cout<<temp<<e/ndl;
        strcpy(char_array, temp.c_str()); 
        std::system(char_array);
    }
    no_of_consumers=1000;
    cout<<endl;
    for(int BSIZE=2;BSIZE<=1000;BSIZE*=2){
        string temp = s + to_string(no_of_producers)  + " " + to_string(no_of_consumers) + " " + to_string(no_of_buffers)+ " " + to_string(BSIZE);
        char char_array[temp.length() + 1]; 
        // copying the contents of the 
        // string to char array 
        // cout<<temp<<endl;
        strcpy(char_array, temp.c_str()); 
        std::system(char_array);
    }
    cout<<endl;
    BSIZE = 5;
    for(int no_of_buffers=10;no_of_buffers<=50000;no_of_buffers*=5){
        string temp = s + to_string(no_of_producers)  + " " + to_string(no_of_consumers) + " " + to_string(no_of_buffers)+ " " + to_string(BSIZE);
        char char_array[temp.length() + 1]; 
        // copying the contents of the 
        // string to char array 
        // cout<<temp<<endl;
        strcpy(char_array, temp.c_str()); 
        std::system(char_array);
    }
    


    return 0;
}