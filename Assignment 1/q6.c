#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // x=(a*b)+(c/d)+(e-f)
    int a = 4;
    int b = 5;
    int c = 25;
    int d = 5;
    int e = 5;
    int f = 2;
    // taking the input from the user
    printf("Please enter the value of a: ");
    scanf("%d", &a);
    printf("Please enter the value of b: ");
    scanf("%d", &b);
    printf("Please enter the value of c: ");
    scanf("%d", &c);
    printf("Please enter the value of d: ");
    scanf("%d", &d);
    // i don't think so validation is needed but added for no reason :)
    while (1)
    {
        if (d == 0)
        {
            // check if the user enters the 0 or not
            printf("\nDivide BY 0 is not Possible\n");
            printf("Please enter the value of d: ");
            scanf("%d", &d);
        }else{
            break;
        }
    }
    printf("Please enter the value of e: ");
    scanf("%d", &e);
    printf("Please enter the value of f: ");
    scanf("%d", &f);

    // variables common to each process for the result storage
    int child1_result = 1;
    int child2_result = 1;
    int child3_result = 1;
    printf("\nParent PID : %d\n", getpid());
    // creating the first child
    pid_t pid_child1 = fork();
    if (pid_child1 == 0)
    {
        // display messages
        printf("\nChild 1 PID: %d \nChild 1 Parent PID: %d", getpid(), getppid());
        printf("\nCalculating (a*b)");
        // pass the value to parent
        exit(a * b);
    }
    else
    {
        // WAIT FOR the child 1 calculation
        wait(&child1_result);
        // make the exact Value
        child1_result = child1_result / 255;
        // DIsplay the result
        printf("\na*b = %d\n", child1_result);

        // parent creating the second child
        pid_t pid_child2 = fork();
        // child 2 process
        if (pid_child2 == 0)
        {
            // calculate c/d
            printf("\nChild 2 Pid: %d \nChild 2 Parend PID: %d", getpid(), getppid());
            printf("\nCalculating c/d \n");
            // passing the result to parnet
            exit(c / d);
        }
        else
        {
            // wait for prcess 2
            wait(&child2_result);
            // get the exact value
            child2_result = child2_result / 255;
            // dusplay the result
            printf("c/d: %d\n", child2_result);

            // parent creating the second child
            pid_t pid_child3 = fork();
            // child 2 process
            if (pid_child3 == 0)
            {
                // calculate c/d
                printf("\nChild 3 Pid: %d \nChild 3 Parend PID: %d", getpid(), getppid());
                printf("\nCalculating e-f \n");
                // passing the result to parnet
                exit(e - f);
            }
            else
            {
                // wait for prcess 3
                wait(&child3_result);
                // get the exact value
                child3_result = child3_result / 255;
                // dusplay the result
                printf("e-f: %d\n", child3_result);

                // Calculatinf the Final result
                printf("\nFinal Result: %d\n", child1_result + child2_result + child3_result);
            }
        }
    }

    return 0;
}