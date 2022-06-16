#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;
int main()
{

    static int copy = dup(STDOUT_FILENO);
    static int copy2 = dup(STDIN_FILENO);
    static int i = 0;
    pid_t wpid;
    int status;

    int fd[2];
    pipe(fd);
    int fd1[2];
    pipe(fd1);
    int fd2[2];
    pipe(fd2);
    int fd3[2];
    pipe(fd3);
    int fd4[2];
    pipe(fd4);
    int fd5[2];
    pipe(fd5);
    char data[200] = "";
again:
    i++;
    pid_t child1 = fork();
    // making a child process
    if (child1 == 0)
    {
        // creating the child2
        pid_t child2 = fork();
        if (child2 == 0)
        {
            // creaginf the third child
            pid_t child3 = fork();
            if (child3 == 0)
            {
                // child4
                pid_t child4 = fork();
                if (child4 == 0)
                {
                    pid_t child5 = fork();
                    if (child5 == 0)
                    {

                        // read from the pipe
                        dup2(fd4[0], STDIN_FILENO);
                        cin >> data;
                 //       close(fd4[0]);
                 //       close(fd4[1]);
                        if (strcmp(data, "Quit") == 0) {
                            //close all the pipes
                            for (int i = 0; i < 2; i++)
                            {
                                close(fd[i]);
                                close(fd1[i]);
                                close(fd2[i]);
                                close(fd3[i]);
                                close(fd4[i]);
                            }
                            //we need to end the process
                            //kill(child1, SIGKILL);
                            exit(0);
                        }

                        // now writing to the pipe
                        dup2(fd5[1], STDOUT_FILENO);
                        cout << data << ":" << getpid() << endl;
                  //      close(fd5[1]);
                  //      close(fd5[0]);
                        // bring back the original cout
                        dup2(copy, STDOUT_FILENO);
                        close(copy);
                       // cout << "\n CHild 5 read this \n";
                        //cout << data;
                        //cout << "\n child 5 written this \n";
                        cout << data << ":" << getpid() << endl;
                        //bring back the original stdin
                        dup2(copy2, STDIN_FILENO);
                        close(copy2);

                    }
                    else
                    {

                        // read from the pipe
                        dup2(fd3[0], STDIN_FILENO);
                        cin >> data;
                        if (strcmp(data, "Quit") == 0) {
                            //close all the pipes
                            for (int i = 0; i < 2; i++)
                            {
                                close(fd[i]);
                                close(fd1[i]);
                                close(fd2[i]);
                                close(fd3[i]);
                                close(fd4[i]);
                            }
                            //we need to end the process
                            kill(child5, SIGKILL);
                            exit(0);
                        }
                   //     close(fd3[0]);
                    //    close(fd3[1]);
                        // now writing to the pipe
                        dup2(fd4[1], STDOUT_FILENO);
                        cout << data << ":" << getpid() << endl;
                   //     close(fd4[1]);
                    //    close(fd4[0]);
                        // bring back the original cout
                        dup2(copy, STDOUT_FILENO);
                        close(copy);
                        //cout << "\n CHild 4 read this \n";
                        //cout << data;
                       // cout << "\n child 4 written this \n";
                        cout << data << ":" << getpid() << endl;
                        //bring back the original stdin
                        dup2(copy2, STDIN_FILENO);
                        close(copy2);
                    }
                }
                else
                {

                    // read from the pipe
                    dup2(fd2[0], STDIN_FILENO);
                    cin >> data;

                    if (strcmp(data, "Quit") == 0) {
                        //close all the pipes
                        for (int i = 0; i < 2; i++)
                        {
                            close(fd[i]);
                            close(fd1[i]);
                            close(fd2[i]);
                            close(fd3[i]);
                            close(fd4[i]);
                        }
                        //we need to end the process
                        kill(child4, SIGKILL);
                        exit(0);
                    }
                 //   close(fd2[0]);
                  //  close(fd2[1]);
                    // now writing to the pipe
                    dup2(fd3[1], STDOUT_FILENO);
                    cout << data << ":" << getpid() << endl;
                //    close(fd3[1]);
                 //   close(fd3[0]);
                    // bring back the original cout
                    dup2(copy, STDOUT_FILENO);
                    close(copy);
                    //cout << "\n CHild 3 read this \n";
                    //cout << data;
                   // cout << "\n child 3 written this \n";
                    cout << data << ":" << getpid() << endl;
                    //bring back the original stdin
                    dup2(copy2, STDIN_FILENO);
                    close(copy2);

                }
            }
            else
            {


                // now reading  the descriptor
                dup2(fd1[0], STDIN_FILENO);
                cin >> data;
                if (strcmp(data, "Quit") == 0) {
                    //close all the pipes
                    for (int i = 0; i < 2; i++)
                    {
                        close(fd[i]);
                        close(fd1[i]);
                        close(fd2[i]);
                        close(fd3[i]);
                        close(fd4[i]);
                    }
                    //we need to end the process
                    kill(child3, SIGKILL);
                    exit(0);
                }
             //   close(fd1[0]);
              //  close(fd1[1]);
                // writing to the pipe
                dup2(fd2[1], STDOUT_FILENO);
                cout << data << ":" << getpid() << endl;
             //   close(fd2[1]);
             //   close(fd2[0]);
                // now bring back the stdout
                dup2(copy, STDOUT_FILENO);
                close(copy);
                //cout << "\n Data read from the pipe from child2\n";
               // cout << data;
              //  cout << "\n Data written by child2 \n";
                cout << data << ":" << getpid() << endl;
                //bring back the original stdin
                dup2(copy2, STDIN_FILENO);
                close(copy2);
            }
        }
        else
        {

            // Now Read the data from the Pipe
            dup2(fd[0], STDIN_FILENO);
            cin >> data;

            if (strcmp(data, "Quit") == 0) {
                //close all the pipes
                for (int i = 0; i < 2; i++)
                {
                    close(fd[i]);
                    close(fd1[i]);
                    close(fd2[i]);
                    close(fd3[i]);
                    close(fd4[i]);
                }
                //we need to end the process
                kill(child2, SIGKILL);
                exit(0);
            }
       //     close(fd[0]);
        //    close(fd[1]);
            // sendind the data to the pipe
            dup2(fd1[1], STDOUT_FILENO);
            cout << data << ":" << getpid() << endl;
       //     close(fd1[0]);
        //    close(fd1[1]);
            // Now Bring back the original stdout
            dup2(copy, STDOUT_FILENO);
            close(copy);
           // cout << "\nChild 1 read from the file\n";
          //  cout << data;
         //  cout << "\n Data written to pipe by child1\n";
            cout << data << ":" << getpid() << endl;
            //bring back the original stdin
            dup2(copy2, STDIN_FILENO);
            close(copy2);
        }
    }
    else
    {
        if (i == 2) {
       //     dup2(copy, STDOUT_FILENO);
        //    close(copy);

        }
        cout << "\nPlease enter something boy: " << endl;
        cout.flush();
        
        cin.clear();
        cin.sync();
        cin.ignore();
        cin.getline(data, 200);
       
        if (strcmp(data, "Quit") == 0) {
            //close all the pipes
            for (int i = 0; i < 2; i++)
            {
                close(fd[i]);
                close(fd1[i]);
                close(fd2[i]);
                close(fd3[i]);
                close(fd4[i]);
            }
            //we need to end the process
            kill(child1, SIGKILL);
            exit(0);
        }

        // sending the stdout to the fd descriptor
        dup2(fd[1], STDOUT_FILENO);
        // put this onto the pipe
        cout << data << ":" << getpid() << endl;
        // close the stuff
     //   close(fd[1]);
      //  close(fd[0]);

        // bring back the original stdout
        dup2(copy, STDOUT_FILENO);
       // close(copy);
        cout << "Written to pipe" << endl;
        cout << data << ":" << getpid() << endl;





        dup2(fd5[0], STDIN_FILENO);
        // put this onto the pipe
        cin >> data;
        // close the stuff
      //  close(fd5[1]);
       // close(fd5[0]);




        sleep(1);
        while ((wpid = wait(&status)) > 0);

       // cout << "\n Parent has read this \n";
        //cout << data << endl;


        // bring back the original cin
        dup2(copy2, STDIN_FILENO);
        close(copy2);

 
        /*
        cout << "\nPLease enter something\n";
        cin.clear();
        cin.sync();
        cin.ignore();
        cin.getline(data, 200);
        strcat(data,"\n");
        cout << "\nAlright \n";
        cout << "\nAhme\n";*/
        goto again;
    }


    return 0;
}