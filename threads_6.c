#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
int evens[10] = {2,4,6,8,10,12,14,16,18,20};//declaring the array of evens
void* routine(void* arg){
    int index = *(int*)arg;
    printf("%d",evens[index]);
    free(arg);   
}//this is a procedure that is a pointer to a void function which takes
//as argument a void pointer which can be really used as a wildcard
//inside the body of it we create a variable called index so as to
// save the value of arg and we simply print the even number of the array
//in position i. The we free the void pointer

int main(){
    pthread_t th[10];//declaring the ten threads
    int i;//declaring the iterative variable

    for(i=0; i<10; i++){
        int* ind = malloc(sizeof(int));//in order to not have issues with printing
        //and the way the threads work
        *ind = i;//we now pass the ind as an argument to the creation of the thread
        if(pthread_create(&th[i], NULL, &routine, ind) != 0){
            printf("Error trying to create the thread in (%d) iteration!", i);
            exit(0);   
        }

    }
    for(i=0; i<10; i++){
        if(pthread_join(th[i], NULL) != 0){
            printf("Error in terminating the thread in the (%d) iteration!", i);
            exit(0);
        }
    }

    return 0;
}