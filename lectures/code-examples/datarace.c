#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int global;
pthread_mutex_t lock;

void* run( void* arg ) {
    for (int i = 0; i < 1000; ++i ) {
        pthread_mutex_lock( &lock );
        global++;
        pthread_mutex_unlock( &lock );
    }
}

int main( int argc, char** argv ) {
    global = 0;
    pthread_mutex_init( &lock, NULL );
    pthread_t t;
    pthread_create(&t, NULL, run, NULL );

    for (int i = 0; i < 10000; ++i) {
        printf("Global = %d\n", global);
    }

    pthread_join( t , NULL );
    printf("Global = %d\n", global);
    pthread_mutex_destroy( &lock );
    return 0;
}

