#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
void* routine(){
    printf("Hello from the thread!\n");
}
int main(){
    pthread_t t1; //defining the first thread
    if(pthread_create(&t1, NULL, &routine, NULL) != 0){
        return 1;
    };//the arguments are the address of the thread, the characteristics
    // the address of the pointer routine and the arguments we pass to the thread
    /*The pthread_create() function shall create a new thread, with attributes specified by attr, within a process.
     If attr is NULL, the default attributes shall be used. 
     If the attributes specified by attr are modified later, the thread's attributes shall not be affected.
      Upon successful completion, pthread_create() shall store the ID of the created thread in the location referenced by thread.

The thread is created executing start_routine with arg as its sole argument. If the start_routine returns, the effect shall be as if there was an implicit call to pthread_exit() using the return value of start_routine as the exit status. Note that the thread in which main() was originally invoked differs from this. When it returns from main(), the effect shall be as if there was an implicit call to exit() using the return value of main() as the exit status*/
    if(pthread_join(t1,NULL) != 0){
        return 2;
    }// the pthread_join waits for the thread to finish the job it does
    /*The pthread_join() function shall suspend execution of the calling thread until the target thread terminates, unless the target thread has already terminated. 
    On return from a successful pthread_join() call with a non-NULL value_ptr argument, the value passed to pthread_exit() by the terminating thread shall be made available in the location referenced by value_ptr. When a pthread_join() returns successfully, the target thread has been terminated. 
    The results of multiple simultaneous calls to pthread_join() specifying the same target thread are undefined. 
    If the thread calling pthread_join() is canceled, then the target thread shall not be detached.
    */
}