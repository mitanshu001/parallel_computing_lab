#include <bits/stdc++.h> 
#include <pthread.h>
#include <unistd.h>
using namespace std; 
using namespace std::chrono;
int BSIZE;
int consume;
int no_of_buffers;

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


struct Queue{
    vector <buffer_t*> buff;
    Queue(int n){
        buff.resize(n);
        for(int i=0;i<n;++i){
            buff[i] = new buffer_t();
        }
    }
};

Queue *q;

void* producer(void* arg)
{
    // buffer_t* b =  (buffer_t*)arg;
    // buffer_t* b = p->b;
    // int ig=0;
    while(1){
        sleep(rand()%3);
        int buffer_no=0;
        while(1){
            buffer_t * b = q->buff[buffer_no++];
            buffer_no%=no_of_buffers;
            if (pthread_mutex_trylock(&b->mutex) == 0)
			{
                // cout<<"mutex lock in producer"<<b->occupied<<endl;
                // cout<<"mutex3 lock in producer"<<b->occupied<<endl;
                while (b->occupied >= BSIZE){
                    // cout<<"in loop"<<endl;
                    pthread_cond_wait(&b->less, &b->mutex);
                }
                // cout<<"after"<<endl;
                assert(b->occupied < BSIZE);
                // cout<<"space in producer"<<endl;
                b->buf[b->nextin++] = rand()%3;

                b->nextin %= BSIZE;
                b->occupied++;
                // cout<<"producer is here"<<endl;
                pthread_cond_signal(&b->more);

                pthread_mutex_unlock(&b->mutex);
                break;
            }
        }
    }
    pthread_exit(NULL);
}


void* consumer(void *arg)
{
    int pre =rand()%3;
    while(1){
        sleep(pre);
        int buffer_no=0;
        while(1)
        {
            buffer_t * b = q->buff[buffer_no++];
            buffer_no%=no_of_buffers;
            int item;
            if (pthread_mutex_trylock(&b->mutex) == 0)
			{
                // cout<<"mutex lock in consumer"<<endl;
                // cout<<"mutex3 lock in consumer"<<endl;
                while(b->occupied <= 0)
                    pthread_cond_wait(&b->more, &b->mutex);

                assert(b->occupied > 0);
                // cout<<"space for consumer"<<endl;
                item = b->buf[b->nextout++];
                b->nextout %= BSIZE;
                b->occupied--;
                pre =item;
                // p->item = item;
                // cout<<"consumer was here"<<endl;
                pthread_cond_signal(&b->less);
                pthread_mutex_unlock(&b->mutex);
                consume+=item;
                break;
            }
        }
    }
    pthread_exit(NULL);
}

#define SIZE 100
int main(){
    // Queue is taken as array of buffers.

    int no_of_consumers = 1000;
    int no_of_producers = 1000;
    BSIZE = 10;
    no_of_buffers = 100;
    
    auto start = high_resolution_clock::now(); 
    consume=0;
    int sleep_time = 10; 
    
    q = new Queue(no_of_buffers);

    buffer_t buffer;
    pthread_t prod[no_of_producers], cons[no_of_consumers];
    
    for(int i=0;i<no_of_producers;++i){
        pthread_create(&prod[i], NULL, producer, NULL);
    }
    for(int i=0;i<no_of_consumers;++i){
        pthread_create(&cons[i], NULL, consumer, NULL);
    }
    
    sleep(sleep_time);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout<<consume/(duration.count())<<endl;
    
    return 0;
}