#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <iomanip>
#include <time.h>
#include <math.h>
using namespace std;
// rows and ccolumns
const int row_weight_arr = 3;
const int col_weight_arr = 4;
const int row_feature_arr = 4;
const int col_feature_arr = 1;

// weight array
float weight_arr[row_weight_arr][col_weight_arr] = {{0.2, -0.5, 0.1, 2.0}, {1.5, 1.3, 2.1, 0.}, {0, 0.25, 0.2, -0.3}};
// feature arr
float feature_arr[row_feature_arr][col_feature_arr] = {{56}, {231}, {24}, {2}};
// biases arr
float biases_arr[row_weight_arr][col_feature_arr] = {{1.1}, {3.2}, {-1.2}};
// resultant arr
float resultant[row_weight_arr][col_feature_arr] = {0};
void show_weight_arr()
{
    // Displaying the matrix's
    cout << "\n[+] Wight Matix [+]";
    cout << "\n----------------------------------\n";
    for (int i = 0; i < row_weight_arr; i++)
    {
        for (int j = 0; j < col_weight_arr; j++)
        {
            cout << setw(8) << weight_arr[i][j] << "";
        }

        cout << "\n";
    }
    cout << "\n----------------------------------\n";
}

void show_feature_arr()
{
    // Displaying the matrix's
    cout << "\n[+] Feature Matix [+]";
    cout << "\n----------------------------------\n";
    for (int i = 0; i < row_feature_arr; i++)
    {
        for (int j = 0; j < col_feature_arr; j++)
        {
            cout << setw(8) << weight_arr[i][j] << "";
        }

        cout << "\n";
    }
    cout << "\n----------------------------------\n";
}
void show_resultant_arr()
{
    // Displaying the matrix's
    cout << "\n[+] Resultant Matix [+]";
    cout << "\n----------------------------------\n";
    for (int i = 0; i < row_weight_arr; i++)
    {
        for (int j = 0; j < col_feature_arr; j++)
        {
            cout << setw(8) << resultant[i][j] << "";
        }

        cout << "\n";
    }
    cout << "\n----------------------------------\n";
}

int step_i = 0;
void *multi(void *arg)
{
    // just assign what thread is going to solve the what matrix
    int i = step_i++;
    for (int j = 0; j < col_feature_arr; j++)
        for (int k = 0; k < col_weight_arr; k++)
            resultant[i][j] += weight_arr[i][k] * feature_arr[k][j];

    return NULL;
}
int step_i_add = 0;
void *add(void *arg)
{

    int i = step_i_add++;
    cout << "\nThread no " << i << "\n";
    for (int j = 0; j < col_feature_arr; j++)
    {
        resultant[i][j] = resultant[i][j] + biases_arr[i][j];
        cout << resultant[i][j] << " ";
    }

    return NULL;
}

int step_i_sig = 0;
void *sig_fun(void *arg)
{

    int i = step_i_sig++;
    cout << "\nThread no " << i << "\n";
    for (int j = 0; j < col_feature_arr; j++)
    {
        resultant[i][j] = (1 / (1 + pow(2.71828182, (-resultant[i][j]))));
        if(resultant[i][j] != 1){
            resultant[i][j] = 0;
        }
        //  cout << resultant[i][j] << " ";
    }

    return NULL;
}
int main()
{
    int pipefd1[2];
    pipe(pipefd1);
    show_weight_arr();
    show_feature_arr();

    // process Now 1
    pid_t child1 = fork();
    if (child1 == 0)
    {
        // child Process of P1
        pid_t child2 = fork();
        if (child2 == 0)
        {
            cout << "\n[+] Process 1\n";
            /*// NOw we need to MUltiplay the BOth Matrix
            for (int i = 0; i < row_weight_arr; ++i)
                for (int j = 0; j < col_feature_arr; ++j)
                    for (int k = 0; k < col_weight_arr; ++k)
                    {
                        resultant[i][j] += weight_arr[i][k] * feature_arr[k][j];
                    }*/

            // make the threads
            pthread_t threads[row_weight_arr];

            // thread for each row
            for (int i = 0; i < row_weight_arr; i++)
            {
                pthread_create(&threads[i], NULL, multi, NULL);
            }
            // JOin them once they are done
            for (int i = 0; i < row_weight_arr; i++)
                pthread_join(threads[i], NULL);

            // writing to the pipe
            write(pipefd1[1], resultant, sizeof(resultant));
            // DIsplaying the OUtput
            show_resultant_arr();
        }
        else
        {
            wait(NULL);
            cout << "\n[+] Process 2\n";
            // reading from the pipe
            read(pipefd1[0], resultant, sizeof(resultant));
            // make the threads
            pthread_t threads[row_weight_arr];

            // thread for each row
            for (int i = 0; i < row_weight_arr; i++)
            {
                pthread_create(&threads[i], NULL, add, NULL);
            }
            // JOin them once they are done
            for (int i = 0; i < row_weight_arr; i++)
                pthread_join(threads[i], NULL);

            // writng tothe pipe
            write(pipefd1[1], resultant, sizeof(resultant));
            // DIsplaying the OUtput
            show_resultant_arr();
        }
    }
    else
    {
        wait(NULL);
        cout << "\n[+] Process 3\n";
        // reading from the pipe
        read(pipefd1[0], resultant, sizeof(resultant));
        // make the threads
        pthread_t threads[row_weight_arr];

        // thread for each row
        for (int i = 0; i < row_weight_arr; i++)
        {
            pthread_create(&threads[i], NULL, sig_fun, NULL);
        }
        // JOin them once they are done
        for (int i = 0; i < row_weight_arr; i++)
            pthread_join(threads[i], NULL);
        // DIsplaying the OUtput
        show_resultant_arr();
    }
    return 0;
}