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
    //the goal is to create multiple threads at once
    //our desire is to create threads that process data parallely and not in a serial way
    pthread_t threads[10];//defining two threads
    pthread_mutex_init(&mutex,NULL);
    int j=0;
    for(j=0; j<10; j++){ 
        if(pthread_create(&threads[j], NULL, &routine_1, NULL) != 0){
            printf("Error with using the creation of the (%d) thread!\n", j);
            exit(0);  
        }
        else{
            printf("The (%d) thread has started\n", j);
        }
    }
    j=0;
    for(j=0; j<10; j++){ 
        if(pthread_join(threads[j], NULL) != 0){
            printf("Error with using the termination of the (%d) thread!\n", j);
            exit(0);  
        }
        else{
            printf("The (%d) thread is terminated!\n", j);
        }

    }
    printf("The count is : %d.\n", count);
    pthread_mutex_destroy(&mutex);
    //the moral of the story is that when we want to create a lot of threads we should have two for loops
    //one for creating them and one for terminating them
 
}