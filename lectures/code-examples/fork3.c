#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main( int argc, char** argv ) {

    printf("Hello from the parent.\n");
    int child_status;
    int pid = fork();
    if ( pid < 0 ) {
        printf("Fork failed.\n");
        return -1;
    } else if ( pid == 0 ) { /* This is the child process */
        sleep( 5 );
        printf("Hello from the child!\n");
        exit( 0 );
    } else { /* This is the parent process */
        waitpid(pid, &child_status, 0 );
        printf("Hello from the parent!\n");
        printf("Child status was: %d.\n", child_status );
    }

    return 0;
}
