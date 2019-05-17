#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main( void ) {
  int pid;
  int child_status;

  pid = fork();
  
  if (pid < 0) {
    printf("Error occurred: %d.\n", pid);
    return -1;
  } else if (pid == 0) {
     printf("Child Executing...\n");
     /* Child Process */
     printf("Hello from the child process.\n");
  } else {
     printf("Parent executing...\n");  
    /* Parent Process */
    waitpid(pid, &child_status, 0 );
    printf("This is the parent process. Child returned %d.\n", child_status);
  }
  return 0;
}

