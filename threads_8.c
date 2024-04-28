#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
int count = 0;
pthread_mutex_t mutex;
void *routine(){
    int j; 
    pthread_mutex_lock(&mutex);
    for(j=0; j<1000000; j++){
        count++;
    }
    pthread_mutex_unlock(&mutex);
}
void *lucky_routine(){
    pthread_mutex_lock(&mutex);
    int value = (rand()%6)+1;//returns a randoma value integer from 1-6
    int* result = malloc(sizeof(int));
    *result = value ; 
    pthread_mutex_unlock(&mutex);
    return (void*) result;
}
int main(){
    int *res ; 
    pthread_t threads[10];//declaring ten threads
    int i;//iterating variable
    for(i=0; i<10; i++){
        if(pthread_create(&threads[i],NULL,&lucky_routine,NULL) != 0){
            printf("Error in creating the threads!");
            exit(0);
        }
        else{
            printf("Everything okey with the creation of the threads\n!");
        }
    }
    for(i=0; i<10; i++){
        if(pthread_join(threads[i],(void **) &res)!=0){
            printf("Error in joining the threads!");
            exit(1);
        }
        else{
            printf("Everything okey with joining the threads!\n");
            printf("The result of your dice is: %d\n", *res);
        }
    }      
    printf("The value of count after its processing from threads is: %d\n", count);
    pthread_mutex_destroy(&mutex);
    free(res); 
}