#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

void* threadA( void* ignore );
void* threadB( void* ignore );
sem_t sem;

int main( int argc, char** argv ) {

    pthread_t ta;
    pthread_t tb;
    
    sem_init( &sem, 0, 0 );

    pthread_create( &ta, NULL, threadA, NULL );
    pthread_create( &tb, NULL, threadB, NULL );

    pthread_join( ta, NULL );
    pthread_join( tb, NULL );

    sem_destroy( &sem );
    pthread_exit( 0 );
}

void* threadA( void* ignore ) {
    sleep( 5 );
    printf( "This is thread A.\n" );
    sem_post( &sem );
    pthread_exit( 0 );
}

void* threadB( void* ignore ) {
    sleep( 4 );
    sem_wait( &sem );
    printf( "This is thread B.\n" );
    
    pthread_exit( 0 );
}


