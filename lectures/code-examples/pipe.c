#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 10
#define READ_END 0
#define WRITE_END 1

int main( int argc, char** argv ) {
  
  char write_msg[BUFFER_SIZE] = "Greetings";
  char read_msg[BUFFER_SIZE];
  int fd[2]; 
  pid_t pid;

  /*memset( &read_msg, 0, BUFFER_SIZE ); */
  if ( pipe(fd) == -1 ) {
    printf("Pipe failed.\n");
    return -1;
  }
  printf("The file descriptors are %d and %d.\n", fd[0], fd[1]);

  pid = fork();
  if (pid < 0) {
    printf("Fork failed.\n");
    return -1;
  } else if (pid > 0) {
    /* Parent Process */
    close( fd[READ_END] );
    
    write(fd[WRITE_END], write_msg, strlen( write_msg ) );

    close( fd[WRITE_END] );
  } else {
    close( fd[WRITE_END] );
    
    read( fd[READ_END], read_msg, BUFFER_SIZE );
    printf("Read %s.\n", read_msg);

    close( fd[READ_END] );
  }

  return 0;
}
