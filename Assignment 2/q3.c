#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{

    int parent_pipe = mkfifo("meeting", 0777);
    int child_pipe = mkfifo("answer", 0777);
    char question[500] = "\nOwner:Are u coming at specified time at 9:00 AM? Y/N\n";
    char buffer_read[500];
    char buffer_write[500];

    // making a child
    pid_t emp1 = fork();
    if (emp1 == 0)
    {

        for (int i = 0; i < 10; i++)
        {

            parent_pipe = open("meeting", O_RDONLY);
            if (read(parent_pipe, buffer_read, sizeof(buffer_read)) == -1)
            {
                printf("Eror REading emp1");
            }
            printf("%s", buffer_read);
            close(parent_pipe);

            // writing on my pipe
            printf("\nEmployee No %d: ", i + 1);
            gets(buffer_write);
            // printf("string is %s", buffer_write);
            child_pipe = open("answer", O_WRONLY);
            if (write(child_pipe, buffer_write, sizeof(buffer_write)) == -1)
            {
                printf("Error writing emp1");
            };
            close(child_pipe);
            /* code */
        }
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            
            
            // wriing on my pipe
            parent_pipe = open("meeting", O_WRONLY);
            // writing to the pipe
            if (write(parent_pipe, question, sizeof(question)) == -1)
            {
                printf("ERROR WRITING");
            }
            close(parent_pipe);

            child_pipe = open("answer", O_RDONLY);
            if (read(child_pipe, buffer_read, sizeof(buffer_read)) == -1)
            {
                printf("ERROR READINg");
            };
            printf("\nEmployee %d Replied:%s",i+1,buffer_read);
            close(child_pipe);
        }
    }
    return 0;
}