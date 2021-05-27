/* check shmget's ability to allocate large shm segs */
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void)
{
        long int shmid;
        long int *shmptr;
        unsigned long int maxsize = 0;
        printf ("Please enter the shared mem segment size to allocate: ");
        scanf ("%ld", &maxsize);
        shmid = shmget (IPC_PRIVATE, maxsize, (IPC_CREAT | 0666));
        if ( shmid == -1 ) {
                printf ("Looks like we cannot allocate %ld bytes, sorry.\n", maxsize);
                exit (1);
        }
        shmptr = shmat(shmid, 0, 0);
        if ( shmptr == NULL ) {
                printf ("Looks like we cannot attach to shared mem seg %d, sorry.\n", shmptr);
                exit (2);
        }
        printf ("Allocated %ld bytes on segment id %d\n\n", maxsize, shmid);
        printf ("Waiting for you to enter a number and press enter to exit... ");
        scanf ("%ld", &maxsize);
        shmdt(shmptr);
        shmctl(shmid, IPC_RMID, 0);
        printf ("Done.\n");
        return(0);
}
/* end */
