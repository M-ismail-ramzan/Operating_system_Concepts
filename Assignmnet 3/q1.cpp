#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
using namespace std;
// keep track how many total items have user bought
short ans = 0;
// Array of Items and Prices
string item_arr[3] = {"Eggs", "Bread", "Chocholate"};
int price_arr[3] = {45, 60, 250};
// Array to know How many EACH item user Bought
int each_item_number[3] = {0};
// Global Price Variable
float price = 0;
float ori_price = 0;
// create mutex to lock
pthread_mutex_t mutex_price;

// FIrst THread Function
void *calculate_sum(void *arr)
{
    cout << "\n[+] Thread NO 1 [+]\n";
    // Display the Items in Here with Their Prices
    cout << "\nTotal Eggs: " << each_item_number[0] << " ---- Price: " << price_arr[0] * each_item_number[0] << "\n";
    cout << "\nTotal Breads: " << each_item_number[1] << " ---- Price: " << price_arr[1] * each_item_number[1] << "\n";
    cout << "\nTotal Chocholate: " << each_item_number[2] << "---- Price: " << price_arr[2] * each_item_number[2] << "\n";
    // Now Let's do the Sum and Add to total Price
    pthread_mutex_lock(&mutex_price);
    // calculating the sum
    int *sum = new int;
    for (int i = 0; i < 3; i++)
    {
        *sum = *sum + price_arr[i] * each_item_number[i];
    }
    cout << "\n[+] Total Sum: " << *sum << endl;
    price = *sum;
    // unlock the critical area
    pthread_mutex_unlock(&mutex_price);

    // we are said to display not to return
    return (void *)sum;
}

// Thread 2
void *calculate_tax(void *arr)
{
    cout << "\n[+] THread 2 In Action [+]\n";
    sleep(1);
    pthread_mutex_lock(&mutex_price);
    // Add the tax baby
    float tax = (price / (1 + 0.8));
    ori_price = price;
    price = price + tax;
    cout << "\n[-] Tax: " << tax << "\n";

    cout << "\n[+] Taxed SUm: " << price << "\n";
    pthread_mutex_unlock(&mutex_price);
    return NULL;
}

// Thread 3
void *calculate_sale(void *arr)
{
    cout << "\n[+] THread 3 In Action [+]\n";
    sleep(2);
    pthread_mutex_lock(&mutex_price);
    if (ori_price >= 250)
    {
        float sale = 0.1 * ori_price;
        ori_price = ori_price - sale;
        price = price;
        cout << "\n[-] Price After Sale: " << ori_price << "\n";
    }
    else
    {
        price = price;
        cout << "\n No Sale \n";
    }
    pthread_mutex_unlock(&mutex_price);
    return NULL;
}

// Thread 4
void *sorting(void *arr)
{
    sleep(2.5);
    cout << "\n[+] THread 4 In Action [+]\n";
    // I have hardcoded the items...
    int min = 0;
    for (int i = 0; i < 2; i++)
    {
        min = i;
        for (int j = 1; j < 3; j++)
        {
            if (price_arr[j] < price_arr[min])
            {
                min = j;
                int temp = price_arr[i];
                price_arr[i] = price_arr[min];
                price_arr[min] = temp;

                string temp3=item_arr[i];
                item_arr[i] = item_arr[min];
                item_arr[min] = temp3;

            }
        }
    }
    //  Dispaying
    for (int i = 0; i < 3; i++)
    {
        cout << item_arr[i] << " -- " << price_arr[i] << endl;
    }
    return NULL;
}

int main()
{
    // iinit the Mutex
    pthread_mutex_init(&mutex_price, NULL);
    // First let's Randomly Buy Items
    cout << "\n[+] How many Items You want to Buy (1-8): ";
    cin >> ans;
    // Randomly BUying the items
    cout << "\n [+] Items Selected [+]\n";
    for (int i = 0; i < ans; i++)
    {
        // random creating the items
        int item = rand() % 3;
        // Adding to Cart
        cout << item_arr[item] << endl;
        // Keep Track of Per Item
        each_item_number[item]++;
    }

    // creating the threads
    pthread_t threads[4];
    // creating the threads to do their jobs
    pthread_create(&threads[0], NULL, calculate_sum, NULL);
    pthread_create(&threads[1], NULL, calculate_tax, NULL);
    pthread_create(&threads[2], NULL, calculate_sale, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);

    pthread_create(&threads[3], NULL, sorting, NULL);
    pthread_join(threads[3], NULL);
    // Destroying the Mutex
    pthread_mutex_destroy(&mutex_price);
    return 0;
}