#pragma comment(linker, "/STACK:1600000000000") //to increase the amount of stack


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>


/************************************
               name                /
               date                /
               class               /
************************************/


using namespace std;


void sort(int* A, int n) 
{

    int max = A[0];
    int last;

    for (int i = 1; i < n; i++)
    {
        if (A[i] > max)
            max = A[i];
    }


    for (int shift = 0; (max >> shift) > 0; shift += 4)
    {
        int count[16] = { 0 };
        int* output = new int[n];

        for (int i = 0; i < n; i++)
            ++count[(A[i] >> shift) & 15];

        for (int i = last = 0; i < 16; i++)
        {
            last += count[i];
            count[i] = last - count[i];
        }

        for (int i = 0; i < n; i++)
            output[count[(A[i] >> shift) & 15]++] = A[i];


        for (int i = 0; i < n; i++)
            A[i] = output[i];
        delete[] output;
    }
}



int  main()
{
    int i, offset, j;
    int B[10000000];
    time_t t;
    srand((unsigned)time(&t));
    offset = rand() % 10000000;
    for (i = 0; i < 10000000; i++)
    {
        B[i] = ((91 * i) % 10000000) + offset;
    }
  
    {
        printf("Prepared array of 10 million integers; calling sort\n");
        clock_t start = clock();

        sort(B, 10000000);

        double duration = (clock() - static_cast<double>(start)) / static_cast<double>(CLOCKS_PER_SEC);
        cout << "Time spent for sorting: " << duration << " seconds" << endl;
    }

    printf("finished sort, now check result\n");
    for (i = 0, j = 0; i < 10000000; i++)
        if (B[i] != i + offset) j++;
    if (j == 0)
        printf("Passed Test\n");
    else
        printf("Failed Test. %d numbers wrong.\n", j);



    return 1;
}
