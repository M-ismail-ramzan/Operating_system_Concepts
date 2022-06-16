#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char * argv[]){
    int subling_status=0;
    int child_status=0;
    printf("\nParent PID: %d\n",getpid());
    // creating a child process
    pid_t pid_child1=fork();
    /// inside the child Process
    if(pid_child1==0){  
        printf("\nChild1 PID: %d \nParent PID: %d\n",getpid(),getppid());
        // creating another child
        pid_t pid_child2=fork();
        // child process of this process
        if(pid_child2==0){
            printf("\nChild1 PID: %d \nParent PID: %d\n",getpid(),getppid());
            // here we need to list the directies
            // showing the parent directory
            char * argument[]={"ls","../","-l",NULL};
            if(execvp("ls",argument)==-1){
                printf("Error");
                exit(1);
            }
        }else{
            // wait until your child has done the task
            wait(&subling_status);
            // getting the exact value
            subling_status=subling_status/255;
            // now transfer the result to it's parnet
            exit(subling_status);
        }

    }else{
        // parent process
        //get the result from it's child
        wait(&child_status);
        // now exact value
        child_status=child_status/255;
        // checking if the status is valid or not
        if(child_status==0){
            printf("\nChild Successful \n");
        }else{
            printf("\nChild Failed\n");
        }
    }


    return 0;
}