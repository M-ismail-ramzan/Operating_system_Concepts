#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(char *argv[], int argc)
{

    printf("\nI am the Parent Process with PID: %d\n ", getpid());
    pid_t p1_child = fork();
    // Child of the P1 Process
    if (p1_child == 0)
    {
        printf("\nI am the Child of P1 with PID %d", getpid());
        printf("\nMy Parent PID is : %d\n", getppid());

        // Child of P1 will create another Child
        pid_t p2_child = fork();
        if (p2_child == 0)
        {
            printf("\nI am the Child of P1 child's with PID %d", getpid());
            printf("\nMy Parent PID is : %d\n", getppid());
        }
        else
        {
            // wait until your child is finish executing
            wait(NULL);
        }
    }
    // Parent Process
    else
    {
        // wait until your child is finish executing
        wait(NULL);
        pid_t p1_child2 = fork();
        // Second clild of Process P1
        if (p1_child2 == 0)
        {
            printf("\nI am the Child of P1 with PID %d", getpid());
            printf("\nMy Parent PID is : %d\n", getppid());
        }
        else
        {
            // wait until your child is finish executing
            wait(NULL);
        }
    }

    return 0;
}