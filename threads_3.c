#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
int count = 0;
pthread_mutex_t mutex;
void* routine(){
    printf("Hello from the thread!\n");
}
void* routine_1(){
    int i=0;
    pthread_mutex_lock(&mutex);
    for(i=0; i<10000000; i++){
        count++;
    }
    pthread_mutex_unlock(&mutex);
}
int main(){
    pthread_t t1,t2,t3;//defining two threads
    pthread_mutex_init(&mutex,NULL);
    if(pthread_create(&t1, NULL, &routine_1, NULL) != 0){
        printf("Error with using the creation of the first thread!");
        exit(0);  
    }
    if(pthread_create(&t2,NULL,&routine_1,NULL) != 0){
        printf("Error using the creation of the second thread!");
        exit(0);
    }
    if(pthread_create(&t3,NULL,&routine_1,NULL) != 0){
        printf("Error using the creation of the second thread!");
        exit(0);
    }
    if(pthread_join(t1,NULL) != 0){
        return 1;
    }
    if(pthread_join(t2,NULL) != 0){
        return 2;
    }
    if(pthread_join(t3,NULL) != 0){
        return 2;
    }
    printf("The count is : %d.\n", count);// not what we expected
    //to be more specific beacuse the threads operate in shared data 
    //maybe the execution of them is perplexed and the result is not the desired
    //for solving this in the next code we will be using a mutex
    pthread_mutex_destroy(&mutex);//correct answer
    //Practically mutexes are mutual exclusive locks
    //when the the lock is on only one threads is in the critical section
    //and when it unlocks the waiting room another thread can go there
    //also it can work for multiple threads
}