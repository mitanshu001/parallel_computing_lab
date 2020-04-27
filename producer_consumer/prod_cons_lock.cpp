#include <bits/stdc++.h> 
#include <pthread.h>
#include <unistd.h>
using namespace std; 
using namespace std::chrono;
int BSIZE;
int consume;
// struct packet{
//     struct buffer_t* b;
//     int item;
// };

struct buffer_t{
    vector <int> buf;
    int occupied;
    int nextin;
    int nextout;
    pthread_mutex_t mutex;
    pthread_cond_t more;
    pthread_cond_t less;
    buffer_t(){
        buf.resize(BSIZE);
        occupied = 0;
        nextin = 0;
        nextout = 0;
        mutex = PTHREAD_MUTEX_INITIALIZER;
        more = PTHREAD_COND_INITIALIZER;
        less = PTHREAD_COND_INITIALIZER;
    }
}; 


void* producer(void* arg)
{
    buffer_t* b =  (buffer_t*)arg;
    // buffer_t* b = p->b;
    int ig=0;
    while(1){
        sleep(rand()%3);
        pthread_mutex_lock(&b->mutex);
    
        while (b->occupied >= BSIZE)
            pthread_cond_wait(&b->less, &b->mutex);

        assert(b->occupied < BSIZE);

        b->buf[b->nextin++] = rand()%3;

        b->nextin %= BSIZE;
        b->occupied++;
        cout<<"producer is here"<<endl;
        pthread_cond_signal(&b->more);

        pthread_mutex_unlock(&b->mutex);
    }

    pthread_exit(NULL);
}


void* consumer(void *arg)
{
    buffer_t *b =  (buffer_t*)arg;
    int pre =rand()%3;
    while(1){
        sleep(pre);
        char item;
        pthread_mutex_lock(&b->mutex);
        while(b->occupied <= 0)
            pthread_cond_wait(&b->more, &b->mutex);

        assert(b->occupied > 0);
        
        item = b->buf[b->nextout++];
        b->nextout %= BSIZE;
        b->occupied--;
        pre =item;
        // p->item = item;
        cout<<"consumer was here"<<endl;
        pthread_cond_signal(&b->less);
        pthread_mutex_unlock(&b->mutex);
        consume++;        

    }
    pthread_exit(NULL);
}

#define SIZE 100
int main(){
    consume=0;
    BSIZE =16; 
    int sleep_time = 20; 
    int iteration = SIZE;
    buffer_t buffer;
    pthread_t prod[SIZE], cons[SIZE];
    int i=0;
    while(iteration--){
        pthread_create(&prod[i], NULL, producer, (void*)&buffer);
        pthread_create(&cons[i], NULL, consumer, (void*)&buffer);
        ++i;
    }

    sleep(sleep_time);
    cout<<(2*consume)/sleep_time<<endl;
    return 0;
}