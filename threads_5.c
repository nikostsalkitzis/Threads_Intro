#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
// the goal of this code it to see how we can have a returning value from the thread
// this is going to be done via the second parameter of the pthread_join
pthread_mutex_t mutex;
void* roll_dice() {
    pthread_mutex_lock(&mutex);
    int value = (rand() % 6) + 1;//producing the value of the dice
    int* result = malloc(sizeof(int));
    *result = value;
    pthread_mutex_unlock(&mutex);
    // printf("%d\n", value);
    printf("Thread result: %p\n", result);

    return (void*) result;
    

}

int main(int argc, char* argv[]) {
    int* res;
    pthread_mutex_init(&mutex,NULL);
    srand(time(NULL));
    pthread_t th[3];
    int i ;  
    for(i=0; i<3; i++){
        if (pthread_create(&th[i], NULL, &roll_dice, NULL) != 0) {
            return 1;
        }

    }
    int j;
    for(j=0; j<3; j++){
        if (pthread_join(th[j], (void**) &res) != 0) {// the second parameter is a double pointer
            return 2;
        }
        else{
            printf("The number of the dice is : %d\n", *res);
        }

    }
    pthread_mutex_destroy(&mutex);
    free(res);
    return 0;
}