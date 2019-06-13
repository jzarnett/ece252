#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

void* threadA( void* ignore );
void* threadB( void* ignore );
void* threadC( void* ignore );
sem_t aArrived;
sem_t bArrived;
sem_t cArrived;

int main( int argc, char** argv ) {

    pthread_t ta;
    pthread_t tb;
    pthread_t tc;
    
    sem_init( &aArrived, 0, 0 );
    sem_init( &bArrived, 0, 0 );
    sem_init( &cArrived, 0, 0 );

    pthread_create( &ta, NULL, threadA, NULL );
    pthread_create( &tb, NULL, threadB, NULL );
    pthread_create( &tc, NULL, threadC, NULL );

    pthread_join( ta, NULL );
    pthread_join( tb, NULL );
    pthread_join( tc, NULL );

    sem_destroy( &aArrived );
    sem_destroy( &bArrived );
    sem_destroy( &cArrived );
    pthread_exit( 0 );
}

void* threadA( void* ignore ) {
    sleep( 5 );
    printf( "Thread A getting ready.\n" );
    sem_post( &aArrived );
    sem_post( &aArrived );
    sem_wait( &bArrived );
    sem_wait( &cArrived );
    sleep( 1 );
    printf( "This is thread A.\n" );
    pthread_exit( 0 );
}

void* threadB( void* ignore ) {
    sleep( 4 );
    printf("Thread B getting ready.\n");
    sem_post( &bArrived );
    sem_post( &bArrived );
    sem_wait( &aArrived );
    sem_wait( &cArrived );
    sleep( 1 );
    printf( "This is thread B.\n" );
    pthread_exit( 0 );
}

void* threadC( void* ignore ) {
    sleep( 3 );
    printf( "Thread C getting ready.\n" );
    sem_post( &cArrived );
    sem_post( &cArrived );
    sem_wait( &aArrived );
    sem_wait( &bArrived );
    sleep( 1 );
    printf( "This is thread C.\n" );

    pthread_exit( 0 );
}
