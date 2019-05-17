#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main( int argc, char** argv ) {
  
  int pid;
  int child_status;

  pid = fork();
  
  if (pid < 0) {
    printf("Error occurred: %d.\n", pid);
    return -1;
  } else if (pid == 0) {
     /* Child Process */
    execlp("/bin/ls", "ls", NULL);
  } else {
    /* Parent Process */
    wait(&child_status );
    printf("This is the parent process. Child returned %d.\n", child_status);
  }
  return 0;
}

