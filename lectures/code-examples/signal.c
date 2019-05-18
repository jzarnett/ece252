#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

volatile int quit = 0;

void handle_it( int signal_num ) {
    quit = 1;
}

int main( int argc, char** argv ) {
  signal( SIGINT, handle_it );
  while( quit == 0 ) {
  }
  
  printf("Time to die.\n");

  return 0;
}
