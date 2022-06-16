#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
using namespace std;
int main()
{
    cout << "\n Note: Type No to say No. And Anything else for Yes!";
Again:
    char buffer_read[200] = "Dummy time";
    char buffer_write[200] = "Dummy time";
    int fd[20][2];
    for (int i = 0; i < 20; i++)
    {
        pipe(fd[i]);
    }
    int parent_write[2];
    pipe(parent_write);
    int parent_read[2];
    pipe(parent_read);
    
    cout << "\n Please Enter the Time String \n";
    cin.getline(buffer_write, 200);
    
    // Now creating the child1
    pid_t child1 = fork();
    if (child1 == 0) {
        //closeing the pipes
        close(fd[1][0]);
        close(fd[0][1]);
        //child will read from the pipe
        read(fd[0][0], buffer_read,sizeof(buffer_read));
        cout << "Message Received From Owner to Emp1 :" << buffer_read << "\n Enter Response:";
        
        // Taking the Employee Input
        cin.clear();
        cin.getline(buffer_write,200);
        //write to the pipe
        write(fd[1][1], buffer_write, sizeof(buffer_write));
        cout << "\n Written to the Pipe :" << buffer_write;
    }
    else {
        
        close(fd[0][0]);
        close(fd[1][1]);
        // parent will write to the pipe
        write(fd[0][1], buffer_write, sizeof(buffer_write));
        // read the response from the child
        read(fd[1][0], buffer_read, sizeof(buffer_read));
        cout << "\nResponse Received from Employee:" << buffer_read << endl;
        cout << " \nWritten\n ";
        if (strcmp(buffer_read, "No") == 0) {
            // if the response received is No
            goto Again;
        }
        else {
            cout << "\nTime to Create New Emp2 \n";
            pid_t child2 = fork();
            if (child2 == 0) {
                //closeing the pipes
                close(fd[3][0]);
                close(fd[2][1]);
                //child will read from the pipe
                read(fd[2][0], buffer_read, sizeof(buffer_read));
                cout << "Message Received From Owner to Emp2 :" << buffer_read << "\n Enter Response:";

                // Taking the Employee Input
                cin.clear();
                cin.getline(buffer_write, 200);
                //write to the pipe
                write(fd[3][1], buffer_write, sizeof(buffer_write));
                cout << "\n Written to the Pipe :" << buffer_write;

            }
            else {
                close(fd[2][0]);
                close(fd[3][1]);
                // parent will write to the pipe
                write(fd[2][1], buffer_write, sizeof(buffer_write));
                // read the response from the child
                read(fd[3][0], buffer_read, sizeof(buffer_read));
                cout << "\nResponse Received from Employee:" << buffer_read << endl;
                cout << " \nWritten\n ";
                if (strcmp(buffer_read, "No") == 0) {
                    // if the response received is No
                    goto Again;
                }
                else {
                    cout << "\nTime to Create New Emp3 \n";
                    pid_t child3 = fork();
                    if (child3 == 0) {
                        //child process
                                        //closeing the pipes
                        close(fd[5][0]);
                        close(fd[4][1]);
                        //child will read from the pipe
                        read(fd[4][0], buffer_read, sizeof(buffer_read));
                        cout << "\nMessage Received From Owner to Emp3 :" << buffer_read << "\n Enter Response:";

                        // Taking the Employee Input
                        cin.clear();
                        cin.getline(buffer_write, 200);
                        //write to the pipe
                        write(fd[5][1], buffer_write, sizeof(buffer_write));
                        cout << "\n Written to the Pipe :" << buffer_write;

                    }
                    else {
                        //parent process
                        close(fd[4][0]);
                        close(fd[5][1]);
                        // parent will write to the pipe
                        write(fd[4][1], buffer_write, sizeof(buffer_write));
                        // read the response from the child
                        read(fd[5][0], buffer_read, sizeof(buffer_read));
                        cout << "\nResponse Received from Employee:" << buffer_read << endl;
                        cout << " \nWritten\n ";
                        if (strcmp(buffer_read, "No") == 0) {
                            // if the response received is No
                            goto Again;
                        }
                        else {
                            cout << "\nTime to Create New Emp4 \n";
                            pid_t child4 = fork();
                            if (child4 == 0) {
                                //child process
                                                //closeing the pipes
                                close(fd[7][0]);
                                close(fd[6][1]);
                                //child will read from the pipe
                                read(fd[6][0], buffer_read, sizeof(buffer_read));
                                cout << "\nMessage Received From Owner to Emp4 :" << buffer_read << "\n Enter Response:";

                                // Taking the Employee Input
                                cin.clear();
                                cin.getline(buffer_write, 200);
                                //write to the pipe
                                write(fd[7][1], buffer_write, sizeof(buffer_write));
                                cout << "\n Written to the Pipe :" << buffer_write;

                            }
                            else {
                                //parent process
                                close(fd[6][0]);
                                close(fd[7][1]);
                                // parent will write to the pipe
                                write(fd[6][1], buffer_write, sizeof(buffer_write));
                                // read the response from the child
                                read(fd[7][0], buffer_read, sizeof(buffer_read));
                                cout << "\nResponse Received from Employee:" << buffer_read << endl;
                                cout << " \nWritten\n ";
                                if (strcmp(buffer_read, "No") == 0) {
                                    // if the response received is No
                                    goto Again;
                                }
                                else {
                                    cout << "\n Time to create Emp 5 \n";
                                    pid_t child5 = fork();
                                    if (child5 == 0) {
                                        //child process
                                                        //closeing the pipes
                                        close(fd[9][0]);
                                        close(fd[8][1]);
                                        //child will read from the pipe
                                        read(fd[8][0], buffer_read, sizeof(buffer_read));
                                        cout << "\nMessage Received From Owner to Emp5 :" << buffer_read << "\n Enter Response:";

                                        // Taking the Employee Input
                                        cin.clear();
                                        cin.getline(buffer_write, 200);
                                        //write to the pipe
                                        write(fd[9][1], buffer_write, sizeof(buffer_write));
                                        cout << "\n Written to the Pipe :" << buffer_write;

                                    }
                                    else {
                                        //parent process
                                        close(fd[8][0]);
                                        close(fd[9][1]);
                                        // parent will write to the pipe
                                        write(fd[8][1], buffer_write, sizeof(buffer_write));
                                        // read the response from the child
                                        read(fd[9][0], buffer_read, sizeof(buffer_read));
                                        cout << "\nResponse Received from Employee:" << buffer_read << endl;
                                        cout << " \nWritten\n ";
                                        if (strcmp(buffer_read, "No") == 0) {
                                            // if the response received is No
                                            goto Again;
                                        }
                                        else {
                                            cout << "\nTime to create Emp6 \n";
                                            pid_t child6 = fork();
                                            if (child6 == 0) {
                                                //child process
                                                                //closeing the pipes
                                                close(fd[11][0]);
                                                close(fd[10][1]);
                                                //child will read from the pipe
                                                read(fd[10][0], buffer_read, sizeof(buffer_read));
                                                cout << "\nMessage Received From Owner to Emp6 :" << buffer_read << "\n Enter Response:";

                                                // Taking the Employee Input
                                                cin.clear();
                                                cin.getline(buffer_write, 200);
                                                //write to the pipe
                                                write(fd[11][1], buffer_write, sizeof(buffer_write));
                                                cout << "\n Written to the Pipe :" << buffer_write;

                                            }
                                            else {
                                                //parent process
                                                close(fd[10][0]);
                                                close(fd[11][1]);
                                                // parent will write to the pipe
                                                write(fd[10][1], buffer_write, sizeof(buffer_write));
                                                // read the response from the child
                                                read(fd[11][0], buffer_read, sizeof(buffer_read));
                                                cout << "\nResponse Received from Employee:" << buffer_read << endl;
                                                cout << " \nWritten\n ";
                                                if (strcmp(buffer_read, "No") == 0) {
                                                    // if the response received is No
                                                    goto Again;
                                                }
                                                else {
                                                    cout << "\n Time to create Emp7 \n";
                                                    pid_t child7 = fork();
                                                    if (child7 == 0) {
                                                        //child process
                                                                        //closeing the pipes
                                                        close(fd[13][0]);
                                                        close(fd[12][1]);
                                                        //child will read from the pipe
                                                        read(fd[12][0], buffer_read, sizeof(buffer_read));
                                                        cout << "\nMessage Received From Owner to Emp7 :" << buffer_read << "\n Enter Response:";

                                                        // Taking the Employee Input
                                                        cin.clear();
                                                        cin.getline(buffer_write, 200);
                                                        //write to the pipe
                                                        write(fd[13][1], buffer_write, sizeof(buffer_write));
                                                        cout << "\n Written to the Pipe :" << buffer_write;

                                                    }
                                                    else {
                                                        //parent process
                                                        close(fd[12][0]);
                                                        close(fd[13][1]);
                                                        // parent will write to the pipe
                                                        write(fd[12][1], buffer_write, sizeof(buffer_write));
                                                        // read the response from the child
                                                        read(fd[13][0], buffer_read, sizeof(buffer_read));
                                                        cout << "\nResponse Received from Employee:" << buffer_read << endl;
                                                        cout << " \nWritten\n ";
                                                        if (strcmp(buffer_read, "No") == 0) {
                                                            // if the response received is No
                                                            goto Again;
                                                        }
                                                        else {
                                                            cout << "\n Time for emp 8 \n";
                                                            pid_t child8 = fork();
                                                            if (child8 == 0) {
                                                                //child process
                                                                                //closeing the pipes
                                                                close(fd[15][0]);
                                                                close(fd[14][1]);
                                                                //child will read from the pipe
                                                                read(fd[14][0], buffer_read, sizeof(buffer_read));
                                                                cout << "\nMessage Received From Owner to Emp8 :" << buffer_read << "\n Enter Response:";

                                                                // Taking the Employee Input
                                                                cin.clear();
                                                                cin.getline(buffer_write, 200);
                                                                //write to the pipe
                                                                write(fd[15][1], buffer_write, sizeof(buffer_write));
                                                                cout << "\n Written to the Pipe :" << buffer_write;

                                                            }
                                                            else {
                                                                //parent process
                                                                close(fd[14][0]);
                                                                close(fd[15][1]);
                                                                // parent will write to the pipe
                                                                write(fd[14][1], buffer_write, sizeof(buffer_write));
                                                                // read the response from the child
                                                                read(fd[15][0], buffer_read, sizeof(buffer_read));
                                                                cout << "\nResponse Received from Employee:" << buffer_read << endl;
                                                                cout << " \nWritten\n ";
                                                                if (strcmp(buffer_read, "No") == 0) {
                                                                    // if the response received is No
                                                                    goto Again;
                                                                }
                                                                else {
                                                                    cout << "\n Time to create Emp 9 \n";
                                                                    pid_t child9 = fork();
                                                                    if (child9 == 0) {
                                                                        //child process
                                                                                        //closeing the pipes
                                                                        close(fd[17][0]);
                                                                        close(fd[16][1]);
                                                                        //child will read from the pipe
                                                                        read(fd[16][0], buffer_read, sizeof(buffer_read));
                                                                        cout << "\nMessage Received From Owner to Emp9 :" << buffer_read << "\n Enter Response:";

                                                                        // Taking the Employee Input
                                                                        cin.clear();
                                                                        cin.getline(buffer_write, 200);
                                                                        //write to the pipe
                                                                        write(fd[17][1], buffer_write, sizeof(buffer_write));
                                                                        cout << "\n Written to the Pipe :" << buffer_write;

                                                                    }
                                                                    else {
                                                                        //parent process
                                                                        close(fd[16][0]);
                                                                        close(fd[17][1]);
                                                                        // parent will write to the pipe
                                                                        write(fd[16][1], buffer_write, sizeof(buffer_write));
                                                                        // read the response from the child
                                                                        read(fd[17][0], buffer_read, sizeof(buffer_read));
                                                                        cout << "\nResponse Received from Employee:" << buffer_read << endl;
                                                                        cout << " \nWritten\n ";
                                                                        if (strcmp(buffer_read, "No") == 0) {
                                                                            // if the response received is No
                                                                            goto Again;
                                                                        }
                                                                        else {
                                                                            cout << "\n Time to crate emp 10 \n";
                                                                            pid_t child10 = fork();
                                                                            if (child10 == 0) {
                                                                                //child process
                                                                                                //closeing the pipes
                                                                                close(fd[19][0]);
                                                                                close(fd[18][1]);
                                                                                //child will read from the pipe
                                                                                read(fd[18][0], buffer_read, sizeof(buffer_read));
                                                                                cout << "\nMessage Received From Owner to Emp10 :" << buffer_read << "\n Enter Response:";

                                                                                // Taking the Employee Input
                                                                                cin.clear();
                                                                                cin.getline(buffer_write, 200);
                                                                                //write to the pipe
                                                                                write(fd[19][1], buffer_write, sizeof(buffer_write));
                                                                                cout << "\n Written to the Pipe :" << buffer_write;

                                                                            }
                                                                            else {
                                                                                //parent process
                                                                                close(fd[18][0]);
                                                                                close(fd[19][1]);
                                                                                // parent will write to the pipe
                                                                                write(fd[18][1], buffer_write, sizeof(buffer_write));
                                                                                // read the response from the child
                                                                                read(fd[19][0], buffer_read, sizeof(buffer_read));
                                                                                cout << "\nResponse Received from Employee:" << buffer_read << endl;
                                                                                cout << " \nWritten\n ";
                                                                                if (strcmp(buffer_read, "No") == 0) {
                                                                                    // if the response received is No
                                                                                    goto Again;
                                                                                }
                                                                                else {
                                                                                    cout << "\n Meeting is Fixed !! \n";
                                                                                }
                                                                            }

                                                                        }
                                                                    }
                                                                }
                                                            }

                                                        }

                                                    }

                                                    
                                                }
                                            }

                                        }
                                    }


                                }

                            }

                        }

                    }
                    
                }
            }


        }
        

    }

    return 0;
}