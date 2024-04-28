#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

pthread_mutex_t mutex;

void* routine(void* arg) {
    pthread_mutex_lock(&mutex);
    char* ch = (char*)arg;
    printf("Thread received: %s\n", ch);
    int i;
    for(i = 0; i < strlen(ch); i++) {
        ch[i] = toupper(ch[i]);
    }
    printf("Uppercase string: %s\n", ch); // Print the modified string
    pthread_mutex_unlock(&mutex);
    return arg;
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    int i, n;
    printf("Give the number of threads you want to create: ");
    scanf("%d", &n);
    pthread_t threads[n];
    for(i = 0; i < n; i++) {
        char* ch = (char*)malloc(100 * sizeof(char)); // Allocating memory for the string
        if(ch == NULL) {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        printf("Give a string you want to uppercase it: ");
        scanf("%s", ch);
        if(pthread_create(&threads[i], NULL, routine, (void*)ch) != 0) {
            printf("Error in creating the thread!\n");
            exit(EXIT_FAILURE);
        } else {
            printf("Success in creating the thread!\n");
        }
        // Wait for the thread to finish before proceeding
        void* result;
        if(pthread_join(threads[i], &result) != 0) {
            printf("Error in joining the threads!\n");
            exit(EXIT_FAILURE);
        }
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}


