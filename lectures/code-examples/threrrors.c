#include <pthread.h>

int global;
void* threadA( void* ignore );
void* threadB( void* ignore );
pthread_mutex_t mutexA;
pthread_mutex_t mutexB;

/** Demonstrates various helgrind error reports.
 * compile: gcc -g -std=c99 -o threrrors threrrors.c -pthread
 * run: valgrind --tool=helgrind ./threrrors
 */
int main( int argc, char** argv ) {

	pthread_mutex_init(&mutexA, NULL);
	pthread_mutex_init(&mutexB, NULL);

    pthread_t ta;
    pthread_t tb;

    pthread_create( &ta, NULL, threadA, NULL );
    pthread_create( &tb, NULL, threadB, NULL );

    pthread_join( ta, NULL );
    pthread_join( tb, NULL );

    pthread_mutex_destroy( &mutexA );
    pthread_mutex_destroy( &mutexA );

    pthread_exit( 0 );
}

void* threadA( void* ignore ) {
	global = 1;
    pthread_mutex_lock( &mutexA );
    pthread_mutex_lock( &mutexB );
    pthread_mutex_unlock( &mutexA );
    pthread_mutex_unlock( &mutexB );
    pthread_exit( 0 );
}

void* threadB( void* ignore ) {
	global = 2;
    pthread_mutex_lock( &mutexB );
    pthread_mutex_lock( &mutexA );
    pthread_exit( 0 );
}
