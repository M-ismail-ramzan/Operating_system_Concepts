#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
// Main Program Starts Here..
int main()
{
    // unnamed pipe

    // for the first child
    int fd[2];
    pipe(fd);
    // for the second child
    int fd1[2];
    pipe(fd1);
    // for the third child
    int fd2[2];
    pipe(fd2);

    // creating a child
    pid_t child1 = fork();
    if (child1 == -1)
    {
        printf("Error created the child\n");
        return 0;
    }

    // child program
    if (child1 == 0)
    {
        // redirect output to the child_1 descriptor
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        // here we are going to do exec
        if (execlp("ls", "ls", "-l", "/", NULL) == -1)
        {
            exit(1);
        };
    }
    else
    {
        // Parent Process
        int wstatus;
        wait(&wstatus);
        // JUst doing some Error Handling
        if (WIFEXITED(wstatus))
        {
            int code = WEXITSTATUS(wstatus);
            if (code == 0)
            {
                printf("Command Executed Successfully\n");
            }
            else
            {
                printf("Some Errors in ls Command\n");
            }
        }

        // another file descriptor
        pid_t child2 = fork();

        if (child2 == 0)
        {

            // CHILD Process
            // output to fd1 and take input from fd
            dup2(fd1[1], STDOUT_FILENO);
            dup2(fd[0], STDIN_FILENO);
            // closeing all
            close(fd[1]);
            close(fd[0]);
            close(fd1[0]);
            close(fd1[1]);

            // here we are going to do exec
            if (execlp("grep", "grep", "a", NULL) == -1)
            {
                exit(1);
            };
        }
        else
        {
            // closing the file descriptors
            close(fd[0]);
            close(fd[1]);
            // Parent Process
            int wstatus;
            wait(&wstatus);
            // JUst doing some Error Handling
            if (WIFEXITED(wstatus))
            {
                int code = WEXITSTATUS(wstatus);
                if (code == 0)
                {
                    printf("grep Command Executed Successfully\n");
                }
                else
                {
                    printf("Some Errors in grep Command\n");
                }
            }

            // now time for the third command.
            pid_t child3 = fork();
            if (child3 == 0)
            {
                // child process
                dup2(fd2[1], STDOUT_FILENO);
                dup2(fd1[0], STDIN_FILENO);
                close(fd2[0]);
                close(fd2[1]);
                close(fd1[0]);
                close(fd1[1]);
                // execution of command
                if (execlp("sort", "sort", "-r", NULL) == -1)
                {
                    exit(1);
                }
            }
            else
            {
                // parent process
                close(fd1[0]);
                close(fd1[1]);

                // Parent Process
                int wstatus;
                wait(&wstatus);
                // JUst doing some Error Handling
                if (WIFEXITED(wstatus))
                {
                    int code = WEXITSTATUS(wstatus);
                    if (code == 0)
                    {
                        printf("sort Command Executed Successfully\n");
                    }
                    else
                    {
                        printf("Some Errors in sort Command\n");
                    }
                }
            }

            // for the fourth command
            int final_fd;
            pid_t child4 = fork();
            if (child4 == 0)
            {

                // child process
                final_fd = open("count.txt", O_WRONLY | O_CREAT, 0777);
                dup2(final_fd, STDOUT_FILENO);
                dup2(fd2[0], STDIN_FILENO);
                close(final_fd);
                close(fd2[0]);
                close(fd2[1]);
                // now executing the commnad
                if (execlp("wc", "wc", NULL) == -1)
                {
                    exit(1);
                }
            }
            else
            {
                // parent Process
                //  parent process
                close(fd2[0]);
                close(fd2[1]);

                // Parent Process
                int wstatus;
                wait(&wstatus);
                // JUst doing some Error Handling
                if (WIFEXITED(wstatus))
                {
                    int code = WEXITSTATUS(wstatus);
                    if (code == 0)
                    {
                        printf("WC Command Executed Successfully\n");
                    }
                    else
                    {
                        printf("Some Errors in WC Command\n");
                    }
                }
            }
        }
        return 0;
    }
}