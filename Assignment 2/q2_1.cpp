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

        // Create a counter
    int count = 0;
  
    // loop
    for (int i = 0; data[i] != '\0'; i++)
    {
  
    
        if (data[i] == 'a' || data[i] == 'e' || data[i] == 'i'
            || data[i] == 'o' || data[i] == 'u') {
  
            // If vowel found increment the count
            count++;
        }
  
    }
    cout << "\nNUmber of VOwel is " << count << "\n";
    return 0;
}