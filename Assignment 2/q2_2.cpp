#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string>
#include<iostream>
#include <sys/wait.h>

using namespace std;
int main(int argc,char* argv[]){
    // reading the inpit
    string data = *argv;
    cout << "\n Data is " << data << "\n";

 
    string reversed;
    // loop
    for (int i = 0,j=data.length()-1; data[i] != '\0'; i++,j--)
    {
        reversed += data[j];
    }
    cout << "\nREvse string is " << reversed << "\n";
    return 0;
}