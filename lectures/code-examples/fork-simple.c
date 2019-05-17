#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( int argc, char** argv ) {
    printf( "Hello there!\n" );

    int f = fork();
    printf( "The value of f is %d.\n", f );
    return 0;
}
