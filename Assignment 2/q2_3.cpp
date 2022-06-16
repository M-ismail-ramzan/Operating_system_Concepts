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

 
    int count=0;
    // loop
    for (int i = 0; data[i] != '\0'; i++)
    {
        if(data[i] >= 'A' && data[i] <= 'Z'){
            count++;
        }
    }
    cout << "\nCaptital letters are " << count << "\n";
    return 0;
}