#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc,char * argv[],char* env[]){
// Simply Displaying the Envirnmental variable
char *path = "PATH=/";
char *user = "USER=";
char *term = "TERM=x";
// There is nothing like that but still checking as a requriment
char *OS2022="OS2022";

//char *pch = strstr(sent, word);
// a Loop to print the variables if they exist
    while(*env){
        if(strstr(*env,path))
        path = *env++;
        else if(strstr(*env,user))
        user = *env++;
        else if(strstr(*env,term))
        term = *env++;
        else if(strstr(*env,OS2022))
        term = *env++;
        else
        *env++;
    }
// prinint statements
    printf("%s",path);
    printf("%s",user);
    printf("%s",term);

    // file path to be executed
    char cmd[]={"./script.sh"};
    // THese are for the execve
    char *argVec[]={"./script.sh",user,term,path,NULL};
    char *envVec[]={"OS2022=5ma32zw","TERM=screen", NULL};   
    // Shoot the command :)
    execve(cmd,argVec,envVec);
    return 0;
}