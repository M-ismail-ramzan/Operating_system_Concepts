#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    // pipe for input
    int file_des = open("input.txt", O_WRONLY, 0777);
    char str[2000];
    // taking the input
    printf("Please Enter the input: ");
    gets(str);
    dup2(file_des, STDOUT_FILENO);
    close(file_des);
    pid_t child1 = fork();
    if (child1 == 0)
    {
        // child process
        system("g++ q2_1.cpp -o q2_1");
        if (execl("./q2_1", str, NULL) == -1)
        {
            exit(1);
        }
    }
    else
    {
        // parent process
        int wstatus;
        wait(&wstatus);
        // JUst doing some Error Handling
        if (WIFEXITED(wstatus))
        {
            int code = WEXITSTATUS(wstatus);
            if (code == 0)
            {
                printf("Vowel Count Successful\n");
            }
            else
            {
                printf("Some Errors in ls Vowel Count\n");
            }
        }

        // second child for reverse
        pid_t child2 = fork();

        if (child2 == 0)
        {
            // child
            // child process
            system("g++ q2_2.cpp -o q2_2");
            if (execl("./q2_2", str, NULL) == -1)
            {
                exit(1);
            }
        }
        else
        {
            // parent
            int wstatus;
            wait(&wstatus);
            // JUst doing some Error Handling
            if (WIFEXITED(wstatus))
            {
                int code = WEXITSTATUS(wstatus);
                if (code == 0)
                {
                    printf("reverse Count Successful\n");
                }
                else
                {
                    printf("Some Errors in ls REverse\n");
                }
            }
        }

        // child3

        pid_t child3 = fork();
        if (child3 == 0)
        {
                        // child process
            system("g++ q2_3.cpp -o q2_3");
            if (execl("./q2_3", str, NULL) == -1)
            {
                exit(1);
            }

        }
        else
        {
                        // parent
            int wstatus;
            wait(&wstatus);
            // JUst doing some Error Handling
            if (WIFEXITED(wstatus))
            {
                int code = WEXITSTATUS(wstatus);
                if (code == 0)
                {
                    printf("Capital Count Successful\n");
                }
                else
                {
                    printf("Some Errors in ls Captical\n");
                }
            }

        }
    }

    return 0;
}