#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>

struct msg {
  long mtype;
  int data;
};

int main( int argc, char** argv ) {
    int msgqid = msgget( IPC_PRIVATE, 0666 | IPC_CREAT );

    int pid = fork();
    if ( pid > 0 ) { /* Parent */
        struct msg m;
        m.mtype = 42;
        m.data = 252;
        msgsnd( msgqid, &m, sizeof( struct msg ), 0 );
    } else if ( pid == 0 ) { /* Child */
       struct msg m2;
       msgrcv( msgqid, &m2, sizeof( struct msg ), 42, 0 );
       printf("Received %d!\n", m2.data );
       msgctl( msgqid, IPC_RMID, NULL );
    }
    return 0;
}

