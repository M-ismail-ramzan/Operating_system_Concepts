#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <pthread.h>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <math.h>
#include <queue>
using namespace std;
// a mutex
pthread_mutex_t mutex_queue;

const int MAX_ROOMS = 4;
struct task;
// crreat the queue
queue<task> queue_task;

const int S = 5000;
// Structure for the Data from the file
struct task
{
    int id;           // first col
    int task_value;   // second
    int arrival_time; // need to calculate it
    int unit_count;   // 3rd col
    int *unitIdList;  // remaming columns if exist
    // make empty
    void make_empty()
    {
        id = 0;
        task_value = 0;
        arrival_time = 0;
        unit_count = 0;
        unitIdList = new int[5];
        // initlize with minus -1
        for (int i = 0; i < 5; i++)
        {
            unitIdList[i] = -1;
        }
    }
    // default constructor
    task()
    {
        id = 0;
        task_value = 0;
        arrival_time = 0;
        unit_count = 0;
        unitIdList = new int[5];
        // initlize with minus -1
        for (int i = 0; i < 5; i++)
        {
            unitIdList[i] = -1;
        }
    }
    // deep copy constructor
    task(const task &D)
    {
        id = D.id;
        task_value = D.task_value;
        arrival_time = D.arrival_time;
        unit_count = D.unit_count;
        unitIdList = new int[5];
        for (int i = 0; i < 5; i++)
        {
            unitIdList[i] = D.unitIdList[i];
        }
    }
    void store_file_data_to_struct(string data, int arr_time)
    {
        // putting the arrival time
        this->arrival_time = arr_time;
        // braking the string
        stringstream S(data);
        int index = 0;
        while (getline(S, data, ' '))
        {
            // if string is not empty
            if (data != "")
            {
                if (index == 0)
                {
                    // first col
                    this->id = stoi(data);
                }
                else if (index == 1)
                {
                    // second col
                    this->task_value = stoi(data);
                }
                else if (index == 2)
                {
                    // third col
                    this->unit_count = stoi(data);
                }
                else
                {
                    // everyother col
                    // count the length for dynamic array
                    for (int i = 0; i < 5; i++)
                    {
                        if (unitIdList[i] == -1)
                        {
                            unitIdList[i] = stoi(data);
                            break;
                        }
                    }
                }
                index++;
            }
        }
        // putting intot the Qeue
        queue_task.push(*this);
        // cout << "\n\n\n\n\n*******************************************\n\n\n";
    }
    void show_struct_information()
    {
        cout << endl
             << this->id << "\n";
        cout << endl
             << this->task_value << "\n";
        cout << endl
             << this->arrival_time << "\n";
        cout << endl
             << this->unit_count << "\n";
        for (int i = 0; i < 5; i++)
        {
            cout << endl
                 << this->unitIdList[i] << "\n";
        }
    }
};
// A struct to print
struct print_result
{
    task task_info;
    int completion_time;
    string unit_id;
};
task temp;
print_result obj;
void print_room(int ans, int unit_id_ans)
{

    cout << "\n";
    cout << obj.task_info.id << "\t" << setw(10) << obj.completion_time <<"\t" << setw(10) << obj.unit_id << setw(10);
    //  cout << obj.task_info.unit_count << "\n";
    for (int i = 0; i < obj.task_info.unit_count; i++)
    {
        cout << setw(10) << obj.task_info.unitIdList[i] << "\t";
    }

    // << "\tREsult:" << ans;
    cout << endl;
}

void *Processer(void *arg)
{
    static int unit_id_asn = 0;
    sleep(1);
    pthread_mutex_lock(&mutex_queue);
    // cout << "";
    int argument = (*((int *)arg));
    int temp_value = temp.task_value;
    switch (argument)
    {
    case 0:
    {
        // add 5 and modulus
        temp_value = (temp.task_value + 5) % S;
        break;
    }
    case 1:
    {
        // mul 7 and modulus
        temp_value = (temp.task_value * 7) % S;

        break;
    }
    case 2:
    {
        // power and modulus
        temp_value = (pow(temp_value, 5));
        temp_value = temp_value % S;
        break;
    }
    case 3:
    {
        // sub 100
        temp_value = (temp.task_value - 100);
        break;
    }
    case 4:
    {
        // add 5 and modulus
        temp_value = pow(temp_value, 2);
        break;
    }

    default:
        break;
    }

    // Here we can call the Print..
    // cout << argument;
    obj.task_info.unit_count = temp.unit_count;
    obj.unit_id = obj.unit_id + to_string(argument) + ',';
    obj.task_info.unitIdList[unit_id_asn] = temp_value;
    unit_id_asn++;
    pthread_mutex_unlock(&mutex_queue);
    // cout << " \tTesting: "<< unit_id_asn;
    if (unit_id_asn == temp.unit_count)
    {
        struct timeval current_time;
        gettimeofday(&current_time, NULL);
        // completion time 
        obj.task_info.id=temp.id;
        obj.completion_time=current_time.tv_usec-temp.arrival_time;
        print_room(temp_value, argument);
        unit_id_asn = 0;
        temp.make_empty();
        obj.task_info = temp;
        obj.unit_id = "";
        sleep(1);
    }
    // Here we are going to add condition according to argument received.

    return NULL;
}
task tasks[5];

void *room_dispatcher(void *arr)
{

    // cout << "\nThread No 2 - Dispatcher Room\n";
    //  Getting the First Element from the Queue
    temp = queue_task.front();
    // Once i get the front element. REmove it from the Queue
    queue_task.pop();
    // Get how many threads i need to create
    // cout << "\nThreads Needes to be created: " << temp.unit_count << "\n";
    int threads_size = temp.unit_count;
    // Create the Threads as Specified.
    pthread_t threading[threads_size];
    for (int i = 0; i < threads_size; i++)
    {
        int *arg = &temp.unitIdList[i];
        pthread_create(&threading[i], NULL, Processer, (void *)arg);
    }
    // closing the threads
    for (int i = 0; i < threads_size; i++)
    {

        pthread_join(threading[i], NULL);
    }

    // cout << "\nThread 2 FInished\n";
    return NULL;
}
// This is the Thread 1
void *room_reception(void *arr)
{
    cout << "\nThread No 1 - Reception Room\n";
    fstream newfile;
    // open for reading
    newfile.open("file.txt", ios::in);
    if (newfile.is_open())
    { // checking whether the file is open
        string tp;
        // keep track of the line no
        int i = 0;
        // read line by line from the string
        while (getline(newfile, tp))
        {
            if (i != 0 && i != 6)
            {
                // here we need to send the data to the structure
                // cout << tp << "\n";
                struct timeval current_time;
                gettimeofday(&current_time, NULL);
                tasks[i - 1].store_file_data_to_struct(tp, current_time.tv_usec);

                //  cout << endl << current_time.tv_usec << " sec \n";
            }
            i++;
        }
        newfile.close(); // close the file object.
    }
    cout << "\nThread 1 FInished\n";
    return NULL;
}
// Function to see the Queue
// Print the queue
void showq(queue<task> gq)
{
    queue<task> g = gq;
    while (!g.empty())
    {

        cout << "\t" << g.front().id;
        g.pop();
    }
    cout << '\n';
}
int main()
{
    // iinit the Mutex
    pthread_mutex_init(&mutex_queue, NULL);
    // make the threads
    pthread_t threads[MAX_ROOMS];

    // thread for each row
    // for (int i = 0; i < MAX_ROOMS; i++)
    {
        pthread_create(&threads[0], NULL, room_reception, NULL);
    }
    // JOin them once they are done
    // for (int i = 0; i < MAX_ROOMS; i++)
    cout << "Task id"
         << "\t" << setw(10) << "Unit ID's" << setw(10);
    for (int i = 0; i < obj.task_info.unit_count; i++)
    {
        cout << setw(10) << "Unit Id" << i << "\t";
    }
    pthread_join(threads[0], NULL);
    cout << "\n ---------Reception ROom and PRint Room-----------\n";
    cout << "Task id"<<" COm time" << setw(10)
         << "\t" << setw(10) << "Unit ID's" << setw(10);
    for (int i = 0; i < 5; i++)
    {
        cout << setw(10) << "Unit Id" << i << "\t";
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&threads[i], NULL, room_dispatcher, NULL);
        pthread_join(threads[i], NULL);
    }

    

    /*
        cout << "\n Testing \n";
        for (int i = 0; i < 5; i++)
        {
            tasks[i].show_struct_information();
            cout << "------------------";
        }
        cout << "\nSeeing the Queue\n";
        showq(queue_task);

        task test=queue_task.back();
        test.show_struct_information();
        */
    pthread_mutex_destroy(&mutex_queue);
    return 0;
}